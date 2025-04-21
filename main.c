#include "chat.h"



int main(){
    char *ptr; // string ptr. ptr -> char
    char **pptr; // array ptr. pptr -> ptr -> char
    char ptrMax = 5;
    char **msgArray = malloc(sizeof(ptr)* ptrMax);
    for (int i = 0; i < ptrMax; i++) {
        msgArray[i] = malloc(CHAR_COUNT * sizeof(int));  // allocate each string
    }
    ptr = msgArray[0];
    pptr = msgArray;
    int ptrCount = 0;
    int i = 0;
    int rows, cols;
    //Variables

    initscr();
    getmaxyx(stdscr, rows, cols); // finds the dimensions of this individual device's terminal
    WINDOW *top = newwin(rows - 3, cols, 0, 0); // dedicated the top 3 rows to the top window
    WINDOW *bottom = newwin(3, cols, rows - 3, 0); // dedicates the bottom 3 rows to the bottom window
    //Creates the windows

    scrollok(top, TRUE);
    box(bottom, 0, 0);
    wrefresh(top);
    wrefresh(bottom);
    // nodelay(bottom, TRUE); 
    //Window parameters

    while (1) {

        mvwprintw(top, i++, 1, "Update line %d", i);
        wrefresh(top);
        // Update top window with other chat
        if (ptrCount >= ptrMax){
            msgArray = realloc(msgArray, sizeof(msgArray) * 2);
            ptrMax = ptrMax * 2;
        }
        getMessage(ptr, bottom);
        ptrCount++;

        mvwprintw(bottom, 1, 2, "> %s", ptr);
        wclrtoeol(bottom);
        wrefresh(bottom);
        // Show current message

        mvwprintw(top, i++, 1, "You entered: %s", ptr);
        pptr++;
        ptr = *pptr;
    }

    endwin();
    free(msgArray);
    return 0;
}