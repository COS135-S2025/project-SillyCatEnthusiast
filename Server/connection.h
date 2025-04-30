#ifndef CONNECTION
#define CONNECTION

typedef struct {
    char *text;
    char *user;
    time_t timestamp;
} Message;

void recieveText(int sock, Message m);


#endif
