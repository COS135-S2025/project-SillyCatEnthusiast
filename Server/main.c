#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>       
#include <arpa/inet.h>    
#include <sys/socket.h>   
int main(){

    Message msg;
    int server_fd; 
    int client_fd;
    struct sockaddr_in server_addr; // creates a sockaddr_in for handling incoming connections 
    struct sockaddr_in client_addr; // creates a sockaddr_in for maintaining a connection to a specific client
    socklen_t addr_size; // just a fancier int 
    char buffer[1024] = {0}; // basically just calloc
    server_fd = socket(AF_INET, SOCK_STREAM, 0); // tells it that its looking for an ipv4 tcp
    server_addr.sin_family = AF_INET; // tells it that it is an ipv4 server
    server_addr.sin_addr.s_addr = INADDR_ANY; // allowed ips: 0.0.0.0 (all)
    server_addr.sin_port = htons(8080);       // port number
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)); 
    // typecasts server_addr into a regular sockaddr and binds the connector to the server file descriptor
    listen(server_fd, 5); // listens for up to 5 queued requests
    addr_size = sizeof(client_addr);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size); // binds the client

    while (1){
    recieveText(client_fd, msg);
    printf("Received: %s\n", m.text);
    sendText(client_fd, msg);
    }
    close(client_fd);
    close(server_fd); // cleanup

}