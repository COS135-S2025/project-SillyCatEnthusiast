#ifndef CHAT
#define CHAT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <arpa/inet.h>

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

bool input(Storage *s, WINDOW *bottom);
void output(Storage *s, WINDOW *top);
#endif