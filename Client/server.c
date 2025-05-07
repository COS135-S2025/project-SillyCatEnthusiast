#include "server.h"
void sendText(int sock, Message *m){
    int msgLen;
    msgLen = strlen(m -> text)+ 1;
    send(sock, &msgLen, sizeof(msgLen), 0);
    send(sock, m -> text, msgLen, 0);
}
void* handleServerIO(void *arg) {
    ThreadArgs *args = (ThreadArgs*)arg; // threading related typecast
    //Struct unpacking
    int sock = args->sock;
    Storage *s = args->storage;
    WINDOW *win = args->win;
    //Message recieving
    Message *m = createMessage();
    char *buffer = malloc(sizeof(char) * 280);
    int mLen;
    while (1){
    //Error catching
    if (read(sock, &mLen, sizeof(mLen)) <= 0) {
        free(buffer);
        free(m->text);
        free(m->user);
        free(m);
        free(args);
        return NULL;
    }
    if (read(sock, buffer, mLen) <= 0) {
        free(buffer);
        free(m->text);
        free(m->user);
        free(m);
        free(args);
        return NULL;
    }
    //Transfer recieved message to internal storage
    trim(buffer);
    strcpy(m->text, buffer);
    s->msgArray[s->msgCount] = m;
    s->msgCount++;
    //Prints
    wprintw(win, "Server: %s\n", m->text);
    wrefresh(win);
    }
    //Cleanup
    free(buffer);
    free(args);
    return NULL;
}