#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "chat.h"

void *receive_handler(void *arg) {
    int port = *((int *)arg);
    pthread_t accept_thread;
    pthread_create(&accept_thread, NULL, accept_handler, &port);
    pthread_detach(accept_thread);

    while (1) {
        pthread_mutex_lock(&connected_peers_mutex);

        for (int i = 0; i < MAX_PEERS; i++) {
            if (connected_peers[i].socket) {
                char message[MESSAGE_LENGTH];
                ssize_t n = read(connected_peers[i].socket, message, MESSAGE_LENGTH - 1);
                if (n > 0) {
                    message[n] = 0;
                    printf("%s\n", message);
                    process_message(message);
                }
            }
        }

        pthread_mutex_unlock(&connected_peers_mutex);
    }
}
