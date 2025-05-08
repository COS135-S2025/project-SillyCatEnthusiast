#include "connector.h"
#include "linked.h"
extern pthread_mutex_t list_lock;
extern Node* head;
// void recieveText(int sock, Message *m){
//     int msg_len = 0;
//     read(sock, &msg_len, sizeof(msg_len)); // read connection[sock] and store (msg_len) bytes to msg_len
//     m->text = malloc(sizeof(char) * msg_len); // mallocs the required space
//     read(sock, m->text, msg_len); // reads the actual text into the malloced area
// }
// void servSendText(int sock, Message *m){
//     int mLen;
//     mLen = strlen(m->text) + 1;
//     send(sock, &mLen, sizeof(mLen), 0);
//     send(sock, m->text, mLen, 0);
// }
void* clientHandler(void *arg) {
    Node *client = (Node*)arg; //typecast
    Message *msg = malloc(sizeof(Message));
    msg->text = malloc(1024);
    msg->user = malloc(1024);

    while (1) {
        int len;
        int n = recv(client->client_fd, &len, sizeof(int), 0); // recieves message 1 (string length)
        if (n <= 0) break;

        msg->text = realloc(msg->text, len);
        recv(client->client_fd, msg->text, len, 0); // recieves message 2
////////////////////////////////////////////////////////////////////////////////////////////////////////
        int uLen;
        int o = recv(client->client_fd, &uLen, sizeof(int), 0); // recieves message 3 (user length)
        if (o <= 0) break;

        msg->user = realloc(msg->user, uLen);
        recv(client->client_fd, msg->user, uLen, 0); // recieves message 4
///////////////////////////////////////////////////////////////////////////////////////////////////////
        printf("Received from %s: %s\n", msg->user, msg->text);


        pthread_mutex_lock(&list_lock);
        Node *curr = head;
        while (curr != NULL) {
            if (curr->client_fd != client->client_fd) {
                send(curr->client_fd, &len, sizeof(int), 0);
                send(curr->client_fd, msg->text, len, 0);
                send(curr->client_fd, &uLen, sizeof(int), 0);
                send(curr->client_fd, msg->user, uLen, 0);
            }
            curr = curr->next;
        }
        pthread_mutex_unlock(&list_lock);
    }

    pthread_mutex_lock(&list_lock);
    close(client->client_fd);
    head = popNode(head, client);
    pthread_mutex_unlock(&list_lock);
    free(msg->text);
    free(msg->user);
    free(msg);
    return NULL;
}
