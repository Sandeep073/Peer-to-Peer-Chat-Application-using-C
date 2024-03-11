#ifndef CHAT_H
#define CHAT_H

#include <stdbool.h>
#include <pthread.h>
#include <netinet/in.h>

#define MAX_PEERS 10
#define MESSAGE_LENGTH 256

typedef struct peer {
    int socket;
    struct sockaddr_in addr;
} Peer;

extern Peer connected_peers[MAX_PEERS];
extern pthread_mutex_t connected_peers_mutex;
extern bool is_connected;

void *send_handler(void *arg);
void *receive_handler(void *arg);
void *accept_handler(void *arg);
void process_message(char *message);
void broadcast_message(const char *message);

#endif
