#include "WebServer.h"

#include <stdio.h>
#include <sys/socket.h>

// simple web server
int Server(void) {
    struct sockaddr_in address;
    int server_fd, new_socket, valread;

    int server_fd;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        printf("Error creating socket");
        return -1;
    }

    bind(server_fd, NULL, 0);
}
