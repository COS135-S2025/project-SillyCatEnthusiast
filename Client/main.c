#include "chat.h"
#include "server.h"
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
int main(int argc, char *argv[]) {
    bool stop = true;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //Server init
    const char *server_ip = argv[1];
    int port = 8080;
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    //Server error handling
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid IP address");
        exit(EXIT_FAILURE);
    }
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    //Window parameters
    initscr();
    cbreak();
    noecho();
    int rows, cols;
    getmaxyx(stdscr, rows, cols); // finds the dimensions of this individual device's terminal
    WINDOW *top = newwin(rows - 3, cols, 0, 0); // dedicated the top x-3 rows to the top window
    WINDOW *bottom = newwin(3, cols, rows - 3, 0); // dedicates the bottom 3 rows to the bottom window
    scrollok(top, TRUE);
    box(bottom, 0, 0);
    wrefresh(top);
    wrefresh(bottom);
    nodelay(bottom, FALSE); 
    wmove(bottom, 1, 2);
    wmove(top, 0, 0);
    //Window init
    wprintw(bottom, "Enter Username:");
    wrefresh(bottom);
    char user[1024] = {0};
    getMessage(user, bottom);
    trim(user);
    wprintw(top, "Connected to %s:%d\n", server_ip, port);
    wrefresh(top);
    wmove(bottom, 1, 2);
    wprintw(bottom, "> ");


    //Storage structs
    Storage *outgoing = createStorage();
    Storage *incoming = createStorage();

    //MultiThreading
    pthread_t serverThread;
    ThreadArgs *args = malloc(sizeof(ThreadArgs));
    //too many args, made a struct for them
    args->sock = sock;
    args->storage = incoming;
    args->win = top;
    //creates a thread for managing the server stuff while the input handling still runs
    pthread_create(&serverThread, NULL, handleServerIO, args);
    pthread_detach(serverThread); 

    while (stop){
        stop = input(outgoing, bottom); // stops once input returns false (when the input is /exit)
        output(outgoing, top);
        outgoing -> msgArray[outgoing -> msgCount - 1] -> user = user;
        sendText(sock, outgoing -> msgArray[outgoing -> msgCount - 1]);
    }

    // clean up
    freeStorage(outgoing);
    freeStorage(incoming);

    close(sock);
    endwin();
    return 0;
}