//Server program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

int main(){
    int sd, nd, len, n;
    struct sockaddr_in seraddress, cliaddr;
    int arr[20];
    int arr_size = 0;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    seraddress.sin_family = AF_INET;
    seraddress.sin_addr.s_addr = INADDR_ANY;
    seraddress.sin_port = htons(10200);
    bind(sd, (struct sockaddr *)&seraddress, sizeof(seraddress));
    listen(sd, 5);
    len = sizeof(cliaddr);
    while (1){
        nd = accept(sd, (struct sockaddr *)&cliaddr, &len);
        printf("Connected to client");
        if (fork() == 0){
            close(sd);
            int pid = getpid();
            n = read(nd, &arr_size, sizeof(int));
            n = read(nd, arr, arr_size * sizeof(int));
            
            // Selection Sort
            for (int i = 0; i < arr_size - 1; ++i) {
                int min_idx = i;
                for (int j = i + 1; j < arr_size; ++j) {
                    if (arr[j] < arr[min_idx]) {
                        min_idx = j;
                    }
                }
                int temp = arr[i];
                arr[i] = arr[min_idx];
                arr[min_idx] = temp;
            }
            
            n = write(nd, &pid, sizeof(int));
            n = write(nd, arr, arr_size * sizeof(int));
            getchar();
            close(nd);
        }
    }
}
