#include "memory.h"
#include "chat.h"
int main(){
    
    int rows, cols;
    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr, rows, cols); // finds the dimensions of this individual device's terminal
    WINDOW *top = newwin(rows - 3, cols, 0, 0); // dedicated the top x-3 rows to the top window
    WINDOW *bottom = newwin(3, cols, rows - 3, 0); // dedicates the bottom 3 rows to the bottom window
    scrollok(top, TRUE);
    box(bottom, 0, 0);
    wrefresh(top);
    wrefresh(bottom);
    nodelay(bottom, TRUE); 
    //Window parameters and init
    
    
    Storage *s = createStorage(); // object oriented seemed to work best
    wmove(bottom, 1, 2);
    wprintw(bottom, "> "); // inital setup because the current method moves it after
    while (1){
        input(s, top, bottom);
    }

    endwin();

    return 0;
}