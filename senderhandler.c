#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "chat.h"

void *send_handler(void *arg) {
    char message[MESSAGE_LENGTH];
    while (true) {
        fgets(message, MESSAGE_LENGTH, stdin);
        message[strcspn(message, "\n")] = 0;
        broadcast_message(message);
    }
}
