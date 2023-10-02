#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

void* thread_codeE(void* param) {
	printf("In child thread even");
    int* arr = (int*) param;
    int n = arr[0];
    int sumE = 0; // Initialize sumE
    for (int i = 1; i <= n; i++) { 
        if (arr[i] % 2 == 0) {
            sumE += arr[i];
        }
    }
    return (void*)sumE; 
    printf("End child thread even");
}

void* thread_codeO(void* param) {
	printf("In child thread odd");
    int* arr = (int*) param;
    int n = arr[0];
    int sumO = 0; 
    for (int i = 1; i <= n; i++) {
        if (arr[i] % 2 == 1) {
            sumO += arr[i];
        }
    }
    return (void*)sumO; 
    printf("End child thread odd");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <length of array>\n", argv[0]);
        return 1;
    }
    pthread_t thread1, thread2;
    int length = atoi(argv[1]);
    int* arr = (int*) malloc(sizeof(int) * (length + 1)); 
    arr[0] = length; 
    for (int i = 1; i <= length; i++) {
        scanf("%d", &arr[i]);
    }
    int sumEven;
    int sumOdd;
    pthread_create(&thread1, NULL, thread_codeE, (void*)arr);
    pthread_create(&thread2, NULL, thread_codeO, (void*)arr);
    pthread_join(thread1, (void**)&sumEven);
    pthread_join(thread2, (void**)&sumOdd);
    printf("In parent thread");
    printf("Sum of even numbers: %d\nSum of odd numbers: %d\n", sumEven, sumOdd);
    free(arr);
    return 0;
}
