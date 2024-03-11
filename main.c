#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "chat.h"

Peer connected_peers[MAX_PEERS];
pthread_mutex_t connected_peers_mutex = PTHREAD_MUTEX_INITIALIZER;
bool is_connected = false;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    if (port < 1024 || port > 65535) {
        fprintf(stderr, "Error: Invalid port number.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t send_thread;
    pthread_create(&send_thread, NULL, send_handler, NULL);

    pthread_t receive_thread;
    pthread_create(&receive_thread, NULL, receive_handler, &port);

    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);

    return 0;
}
