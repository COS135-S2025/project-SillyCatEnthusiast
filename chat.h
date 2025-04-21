#ifndef CHAT
#define CHAT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>

typedef struct {
    char *text;
    char *user;
    time_t timestamp;
} Message;

#define CHAR_MAX 280
#define USER_MAX 20
void getMessage(char *ptr, WINDOW* win);


Message* createMessage();

void freeMessage(Message *msg);
#endif