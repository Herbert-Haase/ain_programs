#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 10
#define BUF_SIZE 256

int main(void)
{
  int listen_fd, new_fd, fd;
  struct sockaddr_in server_addr;
  fd_set master_set, read_set;
  int max_fd;

  /* Create listening socket */
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

  /* Initialize fd sets */
  FD_ZERO(&master_set);
  FD_SET(listen_fd, &master_set);
  max_fd = listen_fd;

  printf("select() server listening on port %d\n", PORT);

  while (1)
  {
    read_set = master_set; /* select modifies the set */

    int ready = select(max_fd + 1, &read_set, NULL, NULL, NULL);
    if (ready < 0)
    {
      perror("select");
      exit(EXIT_FAILURE);
    }

    for (fd = 0; fd <= max_fd; fd++)
    {
      if (!FD_ISSET(fd, &read_set))
        continue;

      /* New incoming connection */
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
        /* Data from client */
        char buf[BUF_SIZE];
        ssize_t n = recv(fd, buf, sizeof(buf), 0);

        if (n <= 0)
        {
          /* Client closed or error */
          close(fd);
          FD_CLR(fd, &master_set);
        }
        else
        {
          /* Respond with time */
          time_t now = time(NULL);
          char response[BUF_SIZE];
          snprintf(response, sizeof(response), "Current time: %s", ctime(&now));

          send(fd, response, strlen(response), 0);

          close(fd);
          FD_CLR(fd, &master_set);
        }
      }
    }
  }

  close(listen_fd);
  return 0;
}
