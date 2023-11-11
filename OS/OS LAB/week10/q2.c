#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 3

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
pthread_mutex_t mutex;

int isSafe(int customer_num, int request[]) {
  int i;
  for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
    if (request[i] > available[i]) {
      return 0;
    }
  }
  for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
    available[i] -= request[i];
    allocation[customer_num][i] += request[i];
    need[customer_num][i] -= request[i];
  }
  int work[NUMBER_OF_RESOURCES];
  for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
    work[i] = available[i];
  }
  int finish[NUMBER_OF_CUSTOMERS];
  for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    finish[i] = 0;
  }
  int count = 0;
  while (count < NUMBER_OF_CUSTOMERS) {
    int found = 0;
    for (i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
      if (finish[i] == 0) {
        int j;
        for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
          if (need[i][j] > work[j]) {
            break;
          }
        }
        if (j == NUMBER_OF_RESOURCES) {
          for (j = 0; j < NUMBER_OF_RESOURCES; j++) {
            work[j] += allocation[i][j];
          }
          finish[i] = 1;
          found = 1;
          count++;
        }
      }
    }
    if (found == 0) {
      for (i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] += request[i];
        allocation[customer_num][i] -= request[i];
        need[customer_num][i] += request[i];
      }
      return 0;
    }
  }
  return 1;
}

void * customer(void * arg) {
  int customer_num = *((int *)arg);
  int request[NUMBER_OF_RESOURCES];
  int requests = 5;
  while (requests > 0) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
      request[i] = rand() % (maximum[customer_num][i] - allocation[customer_num][i] + 1);
    }
    pthread_mutex_lock(&mutex);
    printf("Customer %d requesting resources: ", customer_num);
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
      printf("%d ", request[i]);
    }
    printf("\n");
    if (isSafe(customer_num, request)) {
      printf("Customer %d request granted\n", customer_num);
    } else {
      printf("Customer %d request denied\n", customer_num);
    }
    pthread_mutex_unlock(&mutex);
    sleep(1);
    requests--;
  }
  pthread_exit(0);
}

int main() {
  pthread_t threads[NUMBER_OF_CUSTOMERS];
  int thread_args[NUMBER_OF_CUSTOMERS];
  pthread_mutex_init(&mutex, NULL);
  for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
    printf("Enter the number of available instances of resource %d: ", i);
    scanf("%d", &available[i]);
  }
  for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
      printf("Enter the maximum instances of resource %d Customer %d may request: ", j, i);
      scanf("%d", &maximum[i][j]);
      allocation[i][j] = 0;
      need[i][j] = maximum[i][j];
    }
  }
  for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    thread_args[i] = i;
    pthread_create(&threads[i], NULL, customer, &thread_args[i]);
  }
  for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
    pthread_join(threads[i], NULL);
  }
  pthread_mutex_destroy(&mutex);
  return 0;
}
