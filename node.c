#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "chat.h"

void *accept_handler(void *arg) {
    int port = *((int *)arg);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_socket == -1) {
            perror("accept");
            continue;
        }

        pthread_mutex_lock(&connected_peers_mutex);

        for (int i = 0; i < MAX_PEERS; i++) {
            if (!connected_peers[i].socket) {
                connected_peers[i].socket = client_socket;
                connected_peers[i].addr = client_addr;
                is_connected = true;
                break;
            }
        }

        pthread_mutex_unlock(&connected_peers_mutex);
    }

    close(server_socket);
}
