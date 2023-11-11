#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<limits.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/stat.h>
#include<string.h>
 
#define FIFO_NAME "my_fifo"
#define BUFFER_SIZE 1000
 
int main(int argc, char *argv[])
{
    int pipe_fd;
    int res;
    int open_mode=O_RDONLY;
    int shelf_count = 0;

    printf("Process %d opening FIFO O_RDONLY\n",getpid());
    pipe_fd=open(FIFO_NAME,open_mode);
    printf("Process %d result %d\n",getpid(),pipe_fd);
    
    if (pipe_fd!=-1)
    {
        while (1) {
            if (shelf_count <= 0) {//?
                res=read(pipe_fd, &shelf_count, sizeof(int));
                printf("%d",shelf_count);
                sleep(1);
                continue;
            }else{
                shelf_count--;
                printf("Consumer removed one item from the shelf. Shelf count: %d\n", shelf_count);
            }
    }
        (void)close(pipe_fd);
    }
    
    else
        exit(EXIT_FAILURE);
    
    // printf("Process %d Finished, %d bytes read\n",getpid(),n );
    exit(EXIT_SUCCESS);
}