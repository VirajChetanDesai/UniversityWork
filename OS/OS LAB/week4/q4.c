#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include<stdlib.h>

int main(){
	char oldPath[100];
	char newPath[100]="newTest.txt";

	printf("Enter old path: \n");
	scanf(" %s",oldPath);
	printf("\nThe old path is: %s", oldPath);
 
	int status = symlink(oldPath, newPath);
	if(status==-1){
		printf("\nError in creating new link");
		exit(0);
	}
	printf("\nThe new path is: %s",newPath);
	status=unlink(newPath);
	if(status==0)
		printf("\nNew path unlinked");
	return 0;
}