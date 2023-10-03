#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define TEXT_SZ 1

struct shared_use_st {
    int written_by_you;
    char some_text[TEXT_SZ];
};

int main() {
    int running = 1;
    void* shared_memory = (void*)0;
    struct shared_use_st* shared_stuff;
    int shmid;
    pid_t child_pid;

    srand((unsigned int)getpid());

    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void*)0, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %p\n", shared_memory);

    shared_stuff = (struct shared_use_st*)shared_memory;
    shared_stuff->written_by_you = 0;

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Child process
        while (running) {
            if (shared_stuff->written_by_you) {
                printf("Child received: %c\n", shared_stuff->some_text[0]);
                char next_char = (char)((int)shared_stuff->some_text[0] + 1);
                if (next_char > 'z')
                    next_char = 'a';
                shared_stuff->some_text[0] = next_char;
                shared_stuff->written_by_you = 0;
            }
            usleep(100000);
        }
        exit(EXIT_SUCCESS);
    } else { // Parent process
        while (running) {
            printf("Enter a character: ");
            char input_char;
            scanf(" %c", &input_char);

            shared_stuff->some_text[0] = input_char;
            shared_stuff->written_by_you = 1;

            // Wait for the child to respond
            while (shared_stuff->written_by_you) {
                usleep(100000);
            }
            printf("Parent received: %c\n", shared_stuff->some_text[0]);
            usleep(100000); // Sleep for 100ms
        }

        // Wait for the child to finish
        waitpid(child_pid, NULL, 0);
        if (shmdt(shared_memory) == -1) {
            perror("shmdt");
            exit(EXIT_FAILURE);
        }
        if (shmctl(shmid, IPC_RMID, 0) == -1) {
            perror("shmctl(IPC_RMID)");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}
