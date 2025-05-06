#include "memory.h"
#include "chat.h"
#include <unistd.h>
#include <pthread.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int rows, cols;

    const char *server_ip = argv[1];
    int port = 8080;

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
    nodelay(bottom, FALSE); 
    //Window parameters and init

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid IP address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }


    Storage *outgoing = createStorage();
    Storage *incoming = createStorage();
    wmove(bottom, 1, 2);
    wmove(top, 0, 0);
    wprintw(top, "Connected to %s:%d\n", server_ip, port);
    wrefresh(top);
    
    wprintw(bottom, "> "); // inital setup because the current method moves it after
    pthread_t serverThread;
    ThreadArgs *args = malloc(sizeof(ThreadArgs));
    args->sock = sock;
    args->storage = incoming;
    args->win = top;
    
    pthread_create(&serverThread, NULL, handleServerIO, args);
    pthread_detach(serverThread); 
    while (1){
        input(outgoing, bottom);
        output(outgoing, top);
        sendText(sock, outgoing -> msgArray[outgoing -> msgCount - 1]);
    }
    close(sock);
    endwin();

    return 0;
}