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
    int running = 1;
    int msgid;
    struct mymsg msg;
    long int msg_to_receive = 1;  // Set the message type to 1

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while (running) {
        if (msgrcv(msgid, (void*)&msg, sizeof(struct mymsg) - sizeof(long int), msg_to_receive, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        if (strncmp(msg.state, "end", 3) == 0) {
            running = 0;
        } else if (strncmp(msg.state, "go", 2) == 0) {
            int num = msg.num;
            int original_num = num;
            int reverse_num = 0;

            while (num > 0) {
                reverse_num = reverse_num * 10 + num % 10;
                num = num / 10;
            }

            if (reverse_num == original_num) {
                strncpy(msg.state, "YES", BUFFER_SIZE);
            } else {
                strncpy(msg.state, "NO", BUFFER_SIZE);
            }

            if (msgsnd(msgid, (void*)&msg, sizeof(struct mymsg) - sizeof(long int), 0) == -1) {
                perror("msgsnd");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Invalid state\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
