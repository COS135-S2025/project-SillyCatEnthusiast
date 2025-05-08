#include "server.h"
#include "chat.h"
void sendText(int sock, Message *m){
    int msgLen;
    msgLen = strlen(m -> text)+ 1;
    send(sock, &msgLen, sizeof(msgLen), 0);
    send(sock, m -> text, msgLen, 0);
    int uLen;
    uLen = strlen(m -> user)+ 1;
    send(sock, &uLen, sizeof(uLen), 0);
    send(sock, m -> user, uLen, 0);
}
void* handleServerIO(void *arg) {
    ThreadArgs *args = (ThreadArgs*)arg; // threading related typecast
    //Struct unpacking
    int sock = args->sock;
    Storage *s = args->storage;
    WINDOW *win = args->win;
    //Message recieving
    Message *m = createMessage();
    char *buffer = malloc(sizeof(char) * CHAR_MAX);
    int mLen;
    char *uBuffer = malloc(sizeof(char) * USER_MAX);
    int uLen;
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
    trim(buffer);
    strcpy(m->text, buffer);

    if (read(sock, &uLen, sizeof(uLen)) <= 0) {
        free(buffer);
        free(m->text);
        free(m->user);
        free(m);
        free(args);
        return NULL;
    }
    if (read(sock, uBuffer, uLen) <= 0) {
        free(buffer);
        free(m->text);
        free(m->user);
        free(m);
        free(args);
        return NULL;
    }
    //Transfer recieved message to internal storage

    trim(uBuffer);
    strcpy(m->user, uBuffer);
    s->msgArray[s->msgCount] = m;
    s->msgCount++;
    //Prints
    wprintw(win, "%s: %s\n",m->user, m->text);
    wrefresh(win);
    }
    //Cleanup
    free(buffer);
    free(uBuffer);
    free(args);
    return NULL;
}