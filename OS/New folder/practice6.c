#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msg {
    long int msg_type;
    char text[1000];
}; 

//sender
int main() { 
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    struct msg message; // No need for dynamic allocation
    if (msgid == -1) {
        fprintf(stderr, "Message queue creation failed\n");
        exit(EXIT_FAILURE); // More informative than exit(0)
    }
    int running = 1;
    while (running) {
        printf("Enter some text: \n");
        fgets(message.text, 1000, stdin); // Directly into message.text
        message.msg_type = 1; // msg_type should be set to a positive number
        if (msgsnd(msgid, (void *)&message, sizeof(message.text), 0) == -1) {
            fprintf(stderr, "Message sending failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(message.text, "end", 3) == 0) { // Compare with 0
            running = 0;
        }
    }
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "Message queue removal failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS); // More informative than exit(1)
}

//reciever
int main() {
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    struct msg message; // As defined above
    if (msgid == -1) {
        fprintf(stderr, "Message queue creation failed\n");
        exit(EXIT_FAILURE);
    }
    int running = 1;
    while (running) {
        if (msgrcv(msgid, (void *)&message, sizeof(message.text), 0, 0) == -1) {
            fprintf(stderr, "Message receiving failed\n");
            exit(EXIT_FAILURE);
        }
        printf("You wrote: %s", message.text);
        if (strncmp(message.text, "end", 3) == 0) { 
            running = 0;
        }
    }
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "Message queue removal failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
