// Compiler Design lab 1
//Q1) To count the number of lines and characters in a file.

#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *srcFile;
	char fileName[100];
	printf("Enter filename to open for reading : \n");
	scanf("%s",fileName);
	srcFile = fopen(fileName,"r");
	if(srcFile == NULL){
		printf("Cannot open file %s \n ",fileName);
		exit(0);
	}else{
		int characters = 0, line = 0;
		char c = fgetc(srcFile);
		if(c != EOF) line++;
		while(c != EOF){
			if(c == '\n') line++;
			else{
				characters++;
			}
			c = fgetc(srcFile);
		}
		printf("Number of lines %d and number of characters %d \n",line,characters);
		fclose(srcFile);
	}
	return 0;
}