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
    int open_mode=O_WRONLY;
    // int n=0;
    // char buffer[BUFFER_SIZE+1];
    int shelf_count = 5;
   
    if(access(FIFO_NAME,F_OK)==-1)
    {
        res=mkfifo(FIFO_NAME,0777);
        if(res!=0)
        {
            fprintf(stderr, "Could not create file%s\n",FIFO_NAME );
            exit(EXIT_FAILURE);    
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n",getpid());
    pipe_fd=open(FIFO_NAME,open_mode);
    printf("Process %d result %d\n",getpid(),pipe_fd);

    printf("Producer stocked the shelf with 5 items. Shelf count: %d\n", shelf_count);
    if (pipe_fd!=-1)
    {

        while (1) {
            // sleep(1);
            res=write(pipe_fd, &shelf_count, sizeof(int));
            if(res==-1)
            {
                fprintf(stderr, "Write Error on Pipe\n");
                exit(EXIT_FAILURE);
            } else if (shelf_count >= 5) {
                printf("Producer: Shelf is full. Waiting for consumer...\n");
                continue;
            }
            else {
                shelf_count++;
                printf("Producer added one item to the shelf. Shelf count: %d\n", shelf_count);
            }
    }
    }
    else
        exit(EXIT_FAILURE);
    (void)close(pipe_fd);
    
    printf("Process %d Finished\n",getpid() );
    exit(EXIT_SUCCESS);
 
}