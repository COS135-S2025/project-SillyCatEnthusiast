#ifndef CONNECTION
#define CONNECTION

typedef struct {
    char *text;
    char *user;
    time_t timestamp;
} Message;

void recievePtr(int sock, Message m);


#endif
