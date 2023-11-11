#include <stdio.h>
#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

void initializeData(int *processes, int *resources, int available[MAX_RESOURCES],
                    int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES]);

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES],
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], int processes, int resources);

int isSafe(int processes, int resources, int available[MAX_RESOURCES],
           int allocation[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES],
           int sequence[MAX_PROCESSES]);

void displayNeedMatrix(int processes, int resources, int need[MAX_PROCESSES][MAX_RESOURCES]);

void displaySafeSequence(int processes, int sequence[MAX_PROCESSES]);

int requestResource(int process, int resources, int request[MAX_RESOURCES], int available[MAX_RESOURCES],
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES]);

int main() {
    int processes, resources;
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int sequence[MAX_PROCESSES];

    initializeData(&processes, &resources, available, max, allocation);
    calculateNeed(need, max, allocation, processes, resources);

    if (isSafe(processes, resources, available, allocation, need, sequence)) {
        printf("System is in a safe state.\n");
        displayNeedMatrix(processes, resources, need);
        displaySafeSequence(processes, sequence);

        int request_p1[MAX_RESOURCES] = {1, 0, 2};
         if (requestResource(1, resources, request_p1, available, allocation, need)) {
             printf("(c) P1's request can be granted immediately.\n");
             displayNeedMatrix(processes, resources, need);
         } else {
             printf("(c) P1's request cannot be granted immediately.\n");
         }

        int request_p4[MAX_RESOURCES] = {3, 3, 0};
        if (requestResource(4, resources, request_p4, available, allocation, need)) {
            printf("(d) P4's request can be granted immediately.\n");
            displayNeedMatrix(processes, resources, need);
        } else {
            printf("(d) P4's request cannot be granted immediately.\n");
        }

        int request_p0[MAX_RESOURCES] = {0, 2, 0};
        if (requestResource(0, resources, request_p0, available, allocation, need)) {
            printf("(e) P0's request can be granted immediately.\n");
            displayNeedMatrix(processes, resources, need);
        } else {
            printf("(e) P0's request cannot be granted immediately.\n");
        }
    } else {
        printf("System is in an unsafe state.\n");
    }

    return 0;
}

// Function to initialize data
void initializeData(int *processes, int *resources, int available[MAX_RESOURCES],
                    int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES]) {
    printf("Enter the number of processes: ");
    scanf("%d", processes);

    printf("Enter the number of resources: ");
    scanf("%d", resources);

    printf("Enter the available resources (A B C): ");
    for (int i = 0; i < *resources; i++) {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < *processes; i++) {
        printf("Enter the maximum demand of process %d (A B C): ", i);
        for (int j = 0; j < *resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    for (int i = 0; i < *processes; i++) {
        printf("Enter the allocation to process %d (A B C): ", i);
        for (int j = 0; j < *resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
}

// Function to calculate the Need matrix
void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES],
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
int isSafe(int processes, int resources, int available[MAX_RESOURCES],
           int allocation[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES],
           int sequence[MAX_PROCESSES]) {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    for (int i = 0; i < processes; i++) {
        finish[i] = 0;
    }

    int count = 0;
    while (count < processes) {
        int found = 0;
        for (int i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                int can_allocate = 1;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    sequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    return count == processes;
}

// Function to display the Need matrix
void displayNeedMatrix(int processes, int resources, int need[MAX_PROCESSES][MAX_RESOURCES]) {
    printf("Content of the Need matrix:\n");
    for (int i = 0; i < processes; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

// Function to display the safe sequence
void displaySafeSequence(int processes, int sequence[MAX_PROCESSES]) {
    printf("Safe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d", sequence[i]);
        if (i < processes - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Function to request resources and check if the system remains in a safe state
int requestResource(int process, int resources, int request[MAX_RESOURCES], int available[MAX_RESOURCES],
                   int allocation[MAX_PROCESSES][MAX_RESOURCES], int need[MAX_PROCESSES][MAX_RESOURCES]) {
    for (int j = 0; j < resources; j++) {
        if (request[j] > need[process][j] || request[j] > available[j]) {
            return 0; // Request cannot be granted
        }
    }

    // Temporarily allocate resources
    for (int j = 0; j < resources; j++) {
        available[j] -= request[j];
        allocation[process][j] += request[j];
        need[process][j] -= request[j];
    }

    // Check if the system remains in a safe state after resource allocation
    int sequence[MAX_PROCESSES];
    if (isSafe(MAX_PROCESSES, resources, available, allocation, need, sequence)) {
        return 1; // Request granted, and the system is in a safe state
    } else {
        // Rollback the resource allocation
        for (int j = 0; j < resources; j++) {
            available[j] += request[j];
            allocation[process][j] -= request[j];
            need[process][j] += request[j];
        }
        return 0; // Request cannot be granted
    }
}
