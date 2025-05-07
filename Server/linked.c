#include "linked.h"

Node* addNode(Node* head, Node *newN){
    if (head == NULL){
        head = newN;
    }
    else{
        Node* curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newN;
    }
    return head;
}

Node* popNode(Node *head, Node *removed){
    if(head == removed){
        Node *temp = head;
        head = head->next;
        free(temp);
    }
    else {
        Node *curr = head;
        while (curr->next != removed) { 
            curr = curr->next; 
        }
        curr -> next = removed -> next; 
        free(removed);
    }
    return head;
}
Node* newNode(){
    Node *n = malloc(sizeof(Node));
        n -> next = NULL;
        n -> client_addr;
        n -> addr_size = sizeof(n -> client_addr);

    return n;
}
void printList(Node* head){
    Node* curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->addr_size);
        curr = curr->next;
    }
    printf("NULL\n");
}