#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFFER_SIZE 30

struct mymsg {
    long int message_type;
    char state[BUFFER_SIZE];
    int num;
};

int main() {
    int msgid;
    struct mymsg msg;
    long int msg_to_send = 1;
    int running = 1;
    int decision;
    
    msgid = msgget((key_t)1234, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Prepare the message
    msg.message_type = msg_to_send;
    strncpy(msg.state, "go", BUFFER_SIZE); // Set the state to "go"

    while (running) {
        printf("Enter the number: ");
        scanf("%d", &msg.num);

        if (msgsnd(msgid, (void*)&msg, sizeof(struct mymsg) - sizeof(long int), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        if (msgrcv(msgid, (void*)&msg, sizeof(struct mymsg) - sizeof(long int), msg_to_send, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        if (strncmp(msg.state, "YES", 3) == 0) {
            printf("The number is a palindrome.\n");
            printf("Do you want to continue (1: Yes, 0: No): ");
            scanf("%d", &decision);

            switch (decision) {
                case 1:
                    strncpy(msg.state, "go", BUFFER_SIZE);
                    break;
                default:
                    strncpy(msg.state, "end", BUFFER_SIZE);
                    running = 0;
            }
        } else if (strncmp(msg.state, "NO", 2) == 0) {
            printf("The number is not a palindrome.\n");
            printf("Do you want to continue (1: Yes, 0: No): ");
            scanf("%d", &decision);

            switch (decision) {
                case 1:
                    strncpy(msg.state, "go", BUFFER_SIZE);
                    break;
                default:
                    strncpy(msg.state, "end", BUFFER_SIZE);
                    running = 0;
            }
        } else {
            printf("Invalid response from the server.\n");
        }
    }

    return 0;
}
