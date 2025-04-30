#include "connector.h"

void recieveText(int sock, Message *m){
    int msg_len = 0;
    read(sock, &msg_len, sizeof(msg_len)); // read connection[sock] and store (msg_len) bytes to msg_len
    m->text = malloc(sizeof(char) * msg_len); // mallocs the required space
    read(sock, m->text, msg_len); // reads the actual text into the malloced area
}
void servSendText(int sock, Message *m){
    int mLen;
    mLen = strlen(m->text) + 1;
    send(sock, &mLen, sizeof(mLen), 0);
    send(sock, m->text, mLen, 0);
}
