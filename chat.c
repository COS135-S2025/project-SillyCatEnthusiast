#include "chat.h"

<<<<<<< Updated upstream
void* getMessage(void* buffer){
    char* inpBuffer = (char*) buffer;
    if (fgets(inpBuffer, BUFFER_SIZE, stdin) != NULL) {
        char *ptr = inpBuffer + strlen(inpBuffer) - 1;
        while(isspace(*ptr)) {ptr --;};
        *(ptr+1) = '\0';   
    }
}
=======
void getMessage(char *ptr, WINDOW* window){

    *ptr = wgetch(window);
    // gets the input and stores it in a string
}
>>>>>>> Stashed changes
