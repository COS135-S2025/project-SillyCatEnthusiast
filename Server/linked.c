#include "linked.h"

void addNode(Node** head, Node *newN){
    if (*head == NULL){
        *head = newN;
    }
    else{
        Node* curr = *head;
        while (curr->next != NULL) { // i do not care about time complexity rn
            curr = curr->next;
        }
        curr->next = newN;
    }
    
}

void popNode(Node **head, Node *removed){
    if(*head == removed){
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    else {
        Node *curr = *head;
        while (curr->next != removed) { // i do not care about time complexity rn
            curr = curr->next;
        }
        curr -> next = curr -> next -> next;
        free(curr);
    }
}
Node* newNode(){
    Node *n = malloc(sizeof(Node));
        n -> next;
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