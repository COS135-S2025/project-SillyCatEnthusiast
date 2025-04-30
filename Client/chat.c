#include "chat.h"

Message* createMessage(){
    Message *m = malloc(sizeof(Message));
    m->text = malloc(sizeof(char) * CHAR_MAX);
    m->user = malloc(sizeof(char) * USER_MAX);
    return m;
}

void getMessage(char *ptr, WINDOW* win){
    int ch;
    int i = 0;

    while ((ch = wgetch(win)) != '\n' && i < 279) {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (i > 0) {
                i--;
                mvwdelch(win, getcury(win), getcurx(win) - 1);
            }
        } else if (isprint(ch)){
            ptr[i++] = ch;
            waddch(win, ch);
        }
        wrefresh(win);
    }
    ptr[i] = '\0';
    // gets the input and stores it in a string
}

void freeMessage(Message *msg){
    free(msg -> text);
    free(msg -> user);
    free(msg);

}
void sendText(int sock, Message *m){
    int msgLen = strlen(m -> text + 1);
    send(sock, &msgLen, sizeof(msgLen), 0);
    send(sock, m -> text, sizeof(m -> text), 0);
}