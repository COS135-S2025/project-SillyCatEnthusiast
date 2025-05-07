#ifndef CHAT
#define CHAT

typedef struct {
    int sock;
    Storage *storage;
    WINDOW *win;
} ThreadArgs;
void sendText(int sock, Message *m);
void* handleServerIO(void *arg);
#endif