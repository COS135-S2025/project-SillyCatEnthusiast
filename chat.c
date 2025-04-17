#include "chat.h"

void* getMessage(void* buffer){
    char* inpBuffer = (char*) buffer;
    if (fgets(inpBuffer, BUFFER_SIZE, stdin) != NULL) {
        char *ptr = inpBuffer + strlen(inpBuffer) - 1;
        while(isspace(*ptr)) {ptr --;};
        *(ptr+1) = '\0';   
    }
}