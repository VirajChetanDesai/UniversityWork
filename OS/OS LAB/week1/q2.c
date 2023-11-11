#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
    int in, index=0, k=0;
    char temp[100], c;
    int n =argc;

    if(argc == 1){
        printf("\nNo file names entered\n");
        exit(0);
    }
    for(int i=1;i<n;i++)
    {
    	in = open(argv[i],O_RDONLY);
	    if(in==-1){
	        printf("File not found\n");
	        exit(0);
	    }
	    while((read(in, &c, 1)) > 0){
	        if(c != '\n'){
	            temp[index++] = c;
	        } else{
	            k++;
	            temp[index] = '\0';
	            index=0;
	            printf(" %s\n", temp);
	            if(k == 20){
	            	printf("press enter");
	                fgetc(stdin);
	                k=0;
	            }
	        }
    	}
    	close(in);
	}
    exit(0);
}