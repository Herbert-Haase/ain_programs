#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BACKLOG 5
#define BUF_SIZE 128

int main(void)
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    /* Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* Allow quick restart after exit */
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /* Bind */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    /* Listen */
    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        /* Accept one client */
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        /* Get current time */
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        strftime(buffer, BUF_SIZE, "%Y-%m-%d %H:%M:%S\n", tm_info);

        /* Send response */
        send(client_fd, buffer, strlen(buffer), 0);

        /* Close client connection */
        close(client_fd);
    }

    close(server_fd);
    return 0;
}

