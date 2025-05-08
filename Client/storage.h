#ifndef MEMORY
#define MEMORY

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <arpa/inet.h>
#define CHAR_MAX 280
#define USER_MAX 20
typedef struct {
    char *text;
    char *user;
    // time_t timestamp;
} Message;

typedef struct {
    Message **msgArray;
    int msgCount;
    int msgMax;
} Storage;

Message* createMessage();

Storage* createStorage();
void freeMessage(Message *msg);

void freeStorage(Storage *s);

void trim(char* msg);

void expand(Storage *s);

#endif