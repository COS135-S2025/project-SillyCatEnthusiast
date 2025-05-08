#ifndef SERVER
#define SERVER
#include "chat.h"
typedef struct {
    int sock;
    Storage *storage;
    WINDOW *win;
} ThreadArgs;
void sendText(int sock, Message *m);
void* handleServerIO(void *arg);
#endif