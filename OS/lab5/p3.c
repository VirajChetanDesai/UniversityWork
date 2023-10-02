#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *thread_code(void *param) {
	printf("In child thread");
    int *arr = (int *)param;
    int start = arr[0];
    int end = arr[1];
    int *ret = (int *)malloc((end - start) * sizeof(int));
    int index = 0;
    for (int i = start; i < end; i++) {
        if (i < 2) continue;
        else {
            int flag = 0;
            for (int j = 2; j <= sqrt(i); j++) {
                if (i % j == 0) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                ret[index++] = i;
            }
        }
    }
    ret[0] = index;
    return (void *)ret;
    printf("End child thread");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <start> <end>\n", argv[0]);
        return 1;
    }
    pthread_t thread;
    int *arr = (int *)malloc(2 * sizeof(int));
    int s = atoi(argv[1]);
    int e = atoi(argv[2]);
    arr[0] = s;
    arr[1] = e;
    int *res;
    pthread_create(&thread, NULL, thread_code, (void *)arr);
    pthread_join(thread, (void **)&res);
    printf("In parent thread");
    int count = res[0];
    for (int i = 1; i < count; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    free(arr);
    free(res);

    return 0;
}
