#include <aio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 10
#define BUF_SIZE 4096

int main(void)
{
  int listen_fd, new_fd, fd;
  struct sockaddr_in server_addr;
  fd_set master_set, read_set;
  int max_fd;

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

  printf("AIO file server listening on port %d\n", PORT);

  while (1)
  {
    read_set = master_set;

    if (select(max_fd + 1, &read_set, NULL, NULL, NULL) < 0)
    {
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
        {
          perror("accept");
          continue;
        }

        FD_SET(new_fd, &master_set);
        if (new_fd > max_fd)
          max_fd = new_fd;
      }
      else
      {
        char filename[256];
        ssize_t n = recv(fd, filename, sizeof(filename) - 1, 0);

        if (n <= 0)
        {
          close(fd);
          FD_CLR(fd, &master_set);
          continue;
        }

        filename[n] = '\0';
        char *newline = strchr(filename, '\n');
        if (newline)
          *newline = '\0';

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

        char buffer[BUF_SIZE];
        struct aiocb cb;
        memset(&cb, 0, sizeof(cb));

        cb.aio_fildes = file_fd;
        cb.aio_buf = buffer;
        cb.aio_nbytes = sizeof(buffer);
        cb.aio_offset = 0;

        if (aio_read(&cb) < 0)
        {
          perror("aio_read");
          close(file_fd);
          close(fd);
          FD_CLR(fd, &master_set);
          continue;
        }

        /* Wait for completion */
        while (aio_error(&cb) == EINPROGRESS)
          ;

        int ret = aio_return(&cb);
        if (ret > 0)
        {
          send(fd, buffer, ret, 0);
        }

        close(file_fd);
        close(fd);
        FD_CLR(fd, &master_set);
      }
    }
  }

  close(listen_fd);
  return 0;
}
