#ifndef CHAT
#define CHAT


#include "storage.h"

void getMessage(char *ptr, WINDOW* win);

bool input(Storage *s, WINDOW *bottom);
void output(Storage *s, WINDOW *top);
#endif