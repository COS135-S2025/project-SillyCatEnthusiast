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
        //Manually builds the string out of char
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
            } 
            else if (isprint(ch)){
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
    keypad(win, FALSE);
}

void freeMessage(Message *msg){ // frees message
    free(msg -> text);
    free(msg -> user);
    free(msg);
}
bool input(Storage *s, WINDOW *bottom){
    //Setup the window and the storage
    Message *m = createMessage();
    wmove(bottom, 1, 4);
    wclrtoeol(bottom);
    //Store message
    getMessage(m -> text, bottom);
    trim(m -> text);
    wrefresh(bottom);
    if (s->msgCount == s->msgMax) {
        expand(s);
    }
    s -> msgArray[s -> msgCount] = m;
    //Check for exit
    if (strcmp(s -> msgArray[s -> msgCount] -> text,("/exit"))){
        s -> msgCount++;
        return true;
    }
    else{
        s -> msgCount++;
        return false;
    }
}
void output(Storage *s, WINDOW *top){
    wprintw(top, "You: %s\n", s -> msgArray[s -> msgCount - 1] -> text);  // uses newline to scroll
    wrefresh(top);
}