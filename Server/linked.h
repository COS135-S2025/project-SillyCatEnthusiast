#ifndef LINKED
#define LINKED
#include <arpa/inet.h>    
#include <sys/socket.h>  
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int client_fd;
    struct Node* next;
    socklen_t addr_size;
    struct sockaddr_in client_addr;
} Node;

void addNode(Node** head, Node *newN);

void popNode(Node *head, Node *removed);

Node* newNode();

void printList(Node* head);





#endif