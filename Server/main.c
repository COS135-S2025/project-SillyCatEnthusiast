#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>       
#include <arpa/inet.h>    
#include <sys/socket.h>
#include <pthread.h>   
#include "connector.h"
#include "linked.h"

pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
Node* head = NULL;

int main(){


    Message *msg = malloc(sizeof(Message));

    int server_fd; 
    struct sockaddr_in server_addr; // creates a sockaddr_in for handling incoming connections 
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // tells it that its looking for an ipv4 tcp
    server_addr.sin_family = AF_INET; // tells it that it is an ipv4 server
    server_addr.sin_addr.s_addr = INADDR_ANY; // allowed ips: 0.0.0.0 (all)
    server_addr.sin_port = htons(8080);       // port number
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
    // typecasts server_addr into a regular sockaddr and binds the connector to the server file descriptor
    listen(server_fd, 5); // listens for up to 5 queued requests
    
    
    
    

    while (1) {
        
        Node *n = newNode();
        
        n->client_fd = accept(server_fd, (struct sockaddr*)&n->client_addr, &n->addr_size); // fills the struct
        
        pthread_t client;
        pthread_create(&client, NULL, clientHandler, (void*)n);
        pthread_detach(client);
        pthread_mutex_lock(&list_lock);
        addNode(&head, n);
        pthread_mutex_unlock(&list_lock); // locks the list to prevent overwriting from different threads
    

    }


}