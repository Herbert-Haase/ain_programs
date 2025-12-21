#include <aio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 10
#define BUF_SIZE 4096
#define CACHE_SIZE 8
#define MAX_FILENAME 256

/* -------- Cache structures -------- */

struct cache_entry
{
  char filename[MAX_FILENAME];
  char *data;
  size_t size;
  int valid;
};

static struct cache_entry cache[CACHE_SIZE];

/* -------- Signal flag -------- */

static volatile sig_atomic_t clear_cache_requested = 0;

/* -------- Signal handler -------- */

void handle_sigusr1(int signo)
{
  (void)signo;
  clear_cache_requested = 1;
}

/* -------- Cache helpers -------- */

void clear_cache(void)
{
  for (int i = 0; i < CACHE_SIZE; i++)
  {
    if (cache[i].valid)
    {
      free(cache[i].data);
      cache[i].data = NULL;
      cache[i].size = 0;
      cache[i].valid = 0;
    }
  }
  printf("Cache cleared\n");
}

struct cache_entry *cache_lookup(const char *filename)
{
  for (int i = 0; i < CACHE_SIZE; i++)
  {
    if (cache[i].valid && strcmp(cache[i].filename, filename) == 0)
      return &cache[i];
  }
  return NULL;
}

void cache_store(const char *filename, char *data, size_t size)
{
  for (int i = 0; i < CACHE_SIZE; i++)
  {
    if (!cache[i].valid)
    {
      strncpy(cache[i].filename, filename, MAX_FILENAME - 1);
      cache[i].filename[MAX_FILENAME - 1] = '\0';
      cache[i].data = data;
      cache[i].size = size;
      cache[i].valid = 1;
      return;
    }
  }

  /* Evict entry 0 (simple policy) */
  free(cache[0].data);
  strncpy(cache[0].filename, filename, MAX_FILENAME - 1);
  cache[0].filename[MAX_FILENAME - 1] = '\0';
  cache[0].data = data;
  cache[0].size = size;
  cache[0].valid = 1;
}

/* -------- Main server -------- */

int main(void)
{
  int listen_fd, new_fd, fd;
  struct sockaddr_in server_addr;
  fd_set master_set, read_set;
  int max_fd;

  signal(SIGUSR1, handle_sigusr1);

  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);

  if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  if (listen(listen_fd, BACKLOG) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  FD_ZERO(&master_set);
  FD_SET(listen_fd, &master_set);
  max_fd = listen_fd;

  printf("AIO file server with cache listening on port %d\n", PORT);

  while (1)
  {
    if (clear_cache_requested)
    {
      clear_cache();
      clear_cache_requested = 0;
    }

    read_set = master_set;

    if (select(max_fd + 1, &read_set, NULL, NULL, NULL) < 0)
    {
      if (errno == EINTR)
        continue;
      perror("select");
      exit(EXIT_FAILURE);
    }

    for (fd = 0; fd <= max_fd; fd++)
    {
      if (!FD_ISSET(fd, &read_set))
        continue;

      if (fd == listen_fd)
      {
        new_fd = accept(listen_fd, NULL, NULL);
        if (new_fd < 0)
          continue;

        FD_SET(new_fd, &master_set);
        if (new_fd > max_fd)
          max_fd = new_fd;
      }
      else
      {
        char filename[MAX_FILENAME];
        ssize_t n = recv(fd, filename, sizeof(filename) - 1, 0);

        if (n <= 0)
        {
          close(fd);
          FD_CLR(fd, &master_set);
          continue;
        }

        filename[n] = '\0';
        char *nl = strchr(filename, '\n');
        if (nl)
          *nl = '\0';

        struct cache_entry *entry = cache_lookup(filename);
        if (entry)
        {
          send(fd, entry->data, entry->size, 0);
          close(fd);
          FD_CLR(fd, &master_set);
          continue;
        }

        int file_fd = open(filename, O_RDONLY);
        if (file_fd < 0)
        {
          char errbuf[256];
          snprintf(errbuf, sizeof(errbuf), "Error opening file: %s\n",
                   strerror(errno));
          send(fd, errbuf, strlen(errbuf), 0);
          close(fd);
          FD_CLR(fd, &master_set);
          continue;
        }

        char *buffer = malloc(BUF_SIZE);
        struct aiocb cb;
        memset(&cb, 0, sizeof(cb));
        cb.aio_fildes = file_fd;
        cb.aio_buf = buffer;
        cb.aio_nbytes = BUF_SIZE;
        cb.aio_offset = 0;

        aio_read(&cb);
        while (aio_error(&cb) == EINPROGRESS)
          ;

        ssize_t bytes = aio_return(&cb);
        if (bytes > 0)
        {
          send(fd, buffer, bytes, 0);
          cache_store(filename, buffer, bytes);
        }
        else
        {
          free(buffer);
        }

        close(file_fd);
        close(fd);
        FD_CLR(fd, &master_set);
      }
    }
  }

  return 0;
}
