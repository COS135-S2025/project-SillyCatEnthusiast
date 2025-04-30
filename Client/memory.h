#ifndef MEMORY
#define MEMORY

#include <ncurses.h>
#include <unistd.h>
#include "chat.h"
typedef struct {
    Message **msgArray;
    int msgCount;
    int msgMax;
} Storage;

Storage* createStorage();

void freeStorage(Storage *s);

void trim(char* msg);

void expand(Storage *s);

void freeStorage(Storage *s);

void input(Storage *s, WINDOW *bottom);

void output(Storage *s, WINDOW *top);

void servInput(int sock, Storage *s);

void servOutput(Storage *s, WINDOW *win);
#endif