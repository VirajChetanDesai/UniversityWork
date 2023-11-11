#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h> // For fork
#define bufsize 1000

struct shared_memory {
    volatile long int written_by_you;
    char text[bufsize];
};

int main() {
    void* shared_mem;
    struct shared_memory* shm;
    int shmid = shmget((key_t)1234, sizeof(struct shared_memory), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }
    shared_mem = shmat(shmid, (void*)0, 0);
    if (shared_mem == (void*)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }
    shm = (struct shared_memory*)shared_mem;
    shm->written_by_you = 0;
    int running = 1;
    int pid = fork();
    if (pid == 0) { // Child process
        while (running) {
            if (shm->written_by_you) {
                char alphabet = shm->text[0];
                if (alphabet == 'z') {
                    printf("a\n");
                } else if (alphabet == 'Z') {
                    printf("A\n");
                } else if ((alphabet >= 'a' && alphabet < 'z') || (alphabet >= 'A' && alphabet < 'Z')) {
                    printf("%c\n", alphabet + 1);
                } else {
                    printf("%c\n", alphabet); // If it's not a letter, just print it as is.
                }
                shm->written_by_you = 0; // Reset the flag after reading

                if (strncmp(shm->text, "end", 3) == 0) {
                    running = 0;
                }
            }
        }
        printf("Child process completed\n");
    } else if (pid > 0) { // Parent process
        while (running) {
            while (shm->written_by_you); // Busy wait for the child to read
            printf("Enter text to send: ");
            fgets(shm->text, bufsize, stdin);
            shm->written_by_you = 1; // Set the flag to indicate data is written

            if (strncmp(shm->text, "end", 3) == 0) {
                running = 0;
                while (shm->written_by_you); // Wait for the child to finish reading
            }
        }
        printf("Parent process completed\n");
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    shmdt(shared_mem);
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
