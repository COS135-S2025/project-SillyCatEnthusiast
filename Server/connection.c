#include "connection.h"

void recievePtrs(int sock, Message m){
    int msg_len; // declaring msg_len
    read(sock, &msg_len, sizeof(msg_len)); // read connection[sock] and store (msg_len) bytes to msg_len
    m.text = malloc(msg_len); // mallocs the required space
    read(sock, m.text, msg_len); // reads the actual text into the malloced area
}