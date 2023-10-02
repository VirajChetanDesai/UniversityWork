#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_code(void *param) {
	printf("In child thread");
    int *arr = (int *)param;
    int n = arr[0];
    int res = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > 0)
            res += arr[i];
    }
    return (void *)res;
    printf("End child thread");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }
    pthread_t thread;
    int n = atoi(argv[1]);
    int *arr = (int *)malloc((n + 1) * sizeof(int));
    arr[0] = n + 1;
    for (int i = 1; i < n + 1; i++) {
        scanf("%d", &arr[i]);
    }
    int *res;
    pthread_create(&thread, NULL, thread_code, (void *)arr);
    pthread_join(thread, (void **)&res);
    printf("In parent thread");
    printf("Resulting sum = %d\n", (int)res);
    free(arr);
    return 0;
}
