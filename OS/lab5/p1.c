#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

void *thread_code(void *param) {
	printf("In child thread");
    int n = *((int *)param);
    int *arr = malloc(n * sizeof(int)); 
    int i = 0;
    if (n == 1) {
        arr[i] = 0;
    } else {
        int a = 0, b = 1, d = 1;
        arr[i++] = 0;
        arr[i++] = 1;
        n = n - 2;
        while (n--) {
            d = a + b;
            arr[i++] = d;
            a = b;
            b = d;
        }
    }
    return arr;
    printf("End child thread");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    pthread_t thread;
    int *arr;
    int n = atoi(argv[1]);
    pthread_create(&thread, NULL, thread_code, (void *)&n);
    pthread_join(thread, (void **)&arr);
    printf("In parent thread");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
