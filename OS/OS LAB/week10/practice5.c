#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *available;

typedef struct {
    int val;
    int *allocated;
    int *need;
} Process;

Process array[100];
int process_index = 0;
pthread_mutex_t mutex;

void *isSafe(void *args) {
    pthread_mutex_lock(&mutex);
    int result = 1;
    int *request = (int *)args;
    int length = request[0]; // The first element of the request array should be the length
    int customer = request[length + 1];
    Process process = array[customer];
    for (int i = 1; i <= length; i++) {
        if (request[i] > available[i - 1]) result = 0;
        if (request[i] > process.need[i - 1]) result = 0;
    }
    if (result == 0) {
        pthread_mutex_unlock(&mutex);
        return (void *)result;
    }
    for (int i = 1; i <= length; i++) {
        available[i - 1] -= request[i];
        process.allocated[i - 1] += request[i];
        process.need[i - 1] -= request[i];
    }
    int *tempAvailable = malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        tempAvailable[i] = available[i];
    }

    // Safe sequence array to keep track of the order of process execution
    int *safeSequence = calloc(process_index, sizeof(int));

    int count = 0; // Number of processes that have finished
    while (count < process_index) {
        int found = 0;
        for (int i = 0; i < process_index; i++) {
            if (array[i].val != -1) {
                int canAllocate = 1;
                for (int j = 0; j < length; j++) {
                    if (array[i].need[j] > tempAvailable[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < length; j++)
                        tempAvailable[j] += array[i].allocated[j];
                    safeSequence[count++] = array[i].val;
                    array[i].val = -1;
                    found = 1;
                }
            }
        }
        // If no process can be allocated, then system is not in safe state
        if (!found) {
            result = 0;
            break;
        }
    }
    free(tempAvailable); // Free the allocated tempAvailable array
    free(safeSequence); // Free the allocated safeSequence array
    pthread_mutex_unlock(&mutex);
    return (void *)result;
}
int main() {
    int resources, processes;
    printf("Enter the number of resources: ");
    scanf("%d", &resources);
    available = (int *)calloc(resources, sizeof(int));
    printf("Enter available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }
    printf("Enter the number of processes: \n");
    scanf("%d", &processes);
    for (int i = 0; i < processes; i++) {
        Process *process = (Process *)calloc(1, sizeof(Process));
        process->val = i;
        process->allocated = (int *)calloc(resources, sizeof(int));
        process->need = (int *)calloc(resources, sizeof(int));
        printf("Enter allocated resources: \n");
        for (int j = 0; j < resources; j++) {
            scanf("%d", &process->allocated[j]);
        }
        printf("Enter max required resources:\n");
        for (int j = 0; j < resources; j++) {
            int max;
            scanf("%d", &max);
            process->need[j] = max - process->allocated[j];
            if (process->need[j] < 0) exit(0);
        }
        array[process_index++] = *process;
    }
    pthread_mutex_init(&mutex, NULL);
    while (1) {
        pthread_t t1;
        int result = 0;
        int *request = calloc(resources + 2, sizeof(int)); // +2 for length and customer
        printf("Enter request: \n");
        request[0] = resources; // Store the length of the request array as the first element
        for (int i = 1; i <= resources; i++) {
            scanf("%d", &request[i]);
        }
        printf("Enter customer to request:\n");
        scanf("%d", &request[resources + 1]);
        pthread_create(&t1, NULL, isSafe, (void *)request);
        pthread_join(t1, (void **)&result);
        if (result == 1) printf("Commited request\n");
        else printf("Request failed\n");
    }
    return 0;
}
