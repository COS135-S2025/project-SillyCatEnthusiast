#include "memory.h"

Storage* createStorage(){
    Storage *s = malloc(sizeof(Storage));
    s -> msgMax = 5;
    s -> msgArray = malloc(sizeof(Message*) * s -> msgMax);
    s -> msgCount = 0;

    return s;
}

void freeStorage(Storage *s){
    for (int i = 0; i < s-> msgCount; i++){
        freeMessage(s -> msgArray[i]);
    }
    free(s);
}

void trim(char *msg){
    int length = strlen(msg);  // get actual string length
    char *ptr = msg + length - 1;  // pointer at last char
    
    while (ptr >= msg && isspace(*ptr)) {
        ptr--;  // trim from end
    }
    *(ptr + 1) = '\0';  // null-terminate just after last non-space char

}

void expand(Storage *s){
    Message** temp = realloc(s -> msgArray, sizeof(Message*) * s -> msgMax * 2);
    if (temp == NULL) {
        perror("realloc failed");
        exit(1);
    }
    else{
        s -> msgArray = temp;
        s -> msgMax *= 2;
    }
}
void input(Storage *s, WINDOW *bottom){

    Message *m = createMessage();
    wmove(bottom, 1, 4);
    wclrtoeol(bottom);
    getMessage(m -> text, bottom); // stores the input into the message obj
    trim(m -> text);
    // wprintw(bottom, "> %s", m -> text);
    wrefresh(bottom);
    if (s->msgCount == s->msgMax) {
        expand(s);
    }
    s -> msgArray[s -> msgCount] = m;
    s -> msgCount++;
}
void output(Storage *s, WINDOW *top){
    wprintw(top, "You: %s\n", s -> msgArray[s -> msgCount - 1] -> text);  // use newline to scroll
    wrefresh(top);
}
void* handleServerIO(void *arg) {
    ThreadArgs *args = (ThreadArgs*)arg;
    int sock = args->sock;
    Storage *s = args->storage;
    WINDOW *win = args->win;

    Message *m = createMessage();
    char *buffer = malloc(sizeof(char) * 280);
    int mLen;
    while (1){
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

    s->msgArray[s->msgCount] = m;
    s->msgCount++;

    wprintw(win, "Server: %s\n", m->text);
    wrefresh(win);
    }
    free(buffer);
    free(args);
    return NULL;
}