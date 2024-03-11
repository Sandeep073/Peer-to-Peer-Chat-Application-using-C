#include <unistd.h>
#include <string.h>
#include "chat.h"

void process_message(char *message) {
    pthread_mutex_lock(&connected_peers_mutex);

    for (int i = 0; i < MAX_PEERS; i++) {
        if (connected_peers[i].socket) {
            write(connected_peers[i].socket, message, strlen(message));
        }
    }

    pthread_mutex_unlock(&connected_peers_mutex);
}

void broadcast_message(const char *message) {
    pthread_mutex_lock(&connected_peers_mutex);

    for (int i = 0; i < MAX_PEERS; i++) {
        if (connected_peers[i].socket) {
            write(connected_peers[i].socket, message, strlen(message));
        }
    }

    pthread_mutex_unlock(&connected_peers_mutex);
}
