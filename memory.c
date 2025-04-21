#include "memory.h"

Storage* createStorage(){
    Storage *s = malloc(sizeof(Storage));
    s -> msgMax = 5;
    s -> msgArray = malloc(sizeof(Message) * s -> msgMax);
    s -> msgCount = 0;

    return s;
}

void freeStorage(Storage *s){
    for (int i = 0; i <= s-> msgCount; i++){
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
    Message** temp = realloc(s -> msgArray, sizeof(s -> msgArray) * s -> msgMax * 2);
    if (temp == NULL) {
        perror("realloc failed");
        exit(1);
    }
    else{
        s -> msgArray = temp;
    }
}
void input(Storage *s, WINDOW *top, WINDOW *bottom){
    int i = 0;
    Message *m = createMessage();
    getMessage(m -> text, bottom);
    trim(m -> text);
    mvwprintw(bottom, 1, 2, "> %s", m -> text);
    wclrtoeol(bottom);
    wrefresh(bottom);
    mvwprintw(top, i++, 1, "You entered: %s", m -> text);
    s -> msgArray[s -> msgCount] = m;
    s -> msgCount++;
}
