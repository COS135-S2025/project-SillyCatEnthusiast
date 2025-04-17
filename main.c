#include "chat.h"
#include <pthread.h>
#include <unistd.h>

int main(){
    int count = 0;
    pthread_t input;
    char msg[BUFFER_SIZE];
    pthread_create(&input, NULL, getMessage, msg);
    while(count < 10){
    printf("hello world\n");
    sleep(1);
    count++;
    }
    pthread_join(input, NULL);
    return 0;
}