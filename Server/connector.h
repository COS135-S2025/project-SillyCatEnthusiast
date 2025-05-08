#ifndef CONNECTION
#define CONNECTION
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>   
#include <pthread.h>
//
typedef struct {
    char *text;
    char *user;
    time_t timestamp;
} Message;

// void recieveText(int sock, Message *m);

// void servSendText(int sock, Message *m);

void* clientHandler(void *arg);
#endif
