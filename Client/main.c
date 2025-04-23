#include "memory.h"
#include "chat.h"
#include <unistd.h>
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

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); // typecasts serv_addr (sockaddr_in) to serv_addr (sockaddr)


    
    Storage *s = createStorage(); // object oriented seemed to work best
    wmove(bottom, 1, 2);
    wmove(top, 0, 0);
    wprintw(bottom, "> "); // inital setup because the current method moves it after
    while (1){
        input(s, top, bottom);
        send(sock, &s -> msgArray[s ->msgCount], sizeof(s -> msgArray[s -> msgCount]), 0);
        read(sock, buffer, sizeof(buffer));
        wprintw(top, 0, 0, "Server: %s\n", buffer); 
        wrefresh(top);
    }
    close(sock);
    endwin();

    return 0;
}