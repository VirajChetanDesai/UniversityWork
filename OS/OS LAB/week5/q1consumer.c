#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo" // NAME OF FILLE
#define BUFFER_SIZE PIPE_BUF //SIZE OF BUFFER
int main()
{
	int pipe_fd;
	int res;
	int count=0;
	char buffer[BUFFER_SIZE + 1];
	int bytes_read = 0;
	memset(buffer, '\0', sizeof(buffer)); // INIT THE BUFFER TO EMPTY STRING
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, O_RDONLY);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) {
		do {
			res = read(pipe_fd, buffer, BUFFER_SIZE);//READ BUF
			printf("%s ",buffer);
			count++;
		} while (count<4);
		(void)close(pipe_fd); //CLOSE AFTER READING
	}
	else {
		exit(EXIT_FAILURE);
	}
	printf("\nConsumer finished");
	exit(EXIT_SUCCESS);
}