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
    wprintw(bottom, "> %s", m -> text);
    wrefresh(bottom);
    if (s->msgCount == s->msgMax) {
        expand(s);
    }
    s -> msgArray[s -> msgCount] = m;
    s -> msgCount++;
}
void output(Storage *s, WINDOW *top){
    wprintw(top, "You: %s\n", s -> msgArray[s -> msgCount]);  // use newline to scroll
    wrefresh(top);
}
void servInput(int sock, Storage *s){
    char buffer[1024] = {0};
    int textLen;
    read(sock, textLen, sizeof(textLen));
    read(sock, buffer, sizeof(textLen));
    trim(buffer);
    s -> msgArray[s -> msgCount] = buffer;

}
void servOutput(Storage *s, WINDOW *win){
    wprintw(top, 0, 0, "Server: %s\n", s -> msgArray[s -> msgCount]); 
    s -> msgCount++;

}
