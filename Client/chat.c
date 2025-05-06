#include "chat.h"

Message* createMessage(){
    Message *m = malloc(sizeof(Message));
    m->text = malloc(sizeof(char) * CHAR_MAX);
    m->user = malloc(sizeof(char) * USER_MAX);
    return m;
}

void getMessage(char *ptr, WINDOW* win){
    keypad(win, TRUE);
    wrefresh(win);
    int ch;
    int i = 0;

    while (i < 279) {
        ch = wgetch(win);
        wrefresh(win);
        if (ch != '\n'){
            if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
                wrefresh(win);
                if (i > 0) {
                    i--;
                    int y = getcury(win);
                    int x = getcurx(win);
                    mvwprintw(win, y, x - 1, " ");  // overwrite with space
                    wmove(win, y, x - 1);           // move cursor back
                }
            } else if (isprint(ch)){
                ptr[i++] = ch;
                waddch(win, ch);
            }
            wrefresh(win);
        }
        else{
            break;
        }
    }
    ptr[i] = '\0';
    // gets the input and stores it in a string
    keypad(win, FALSE);
}

void freeMessage(Message *msg){ // frees message
    free(msg -> text);
    free(msg -> user);
    free(msg);
}
void sendText(int sock, Message *m){
    int msgLen;
    msgLen = strlen(m -> text)+ 1;
    send(sock, &msgLen, sizeof(msgLen), 0);
    send(sock, m -> text, msgLen, 0);
}