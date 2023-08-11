// Compiler Design lab 2
//Q2) WAP to discard preprocessor directives from the given input ‘C’ file.
#include<stdio.h>
#include<stdlib.h>
int main(){
	FILE *srcFile,*tgtFile;
	char fileName[100];
	char fileName2[100];
	printf("Enter the name of file to open : \n");
	scanf("%s",fileName);
	srcFile = fopen(fileName,"r");
	if(srcFile == NULL){
		printf("File cannot be opened\n");
		exit(1);
	}
	printf("Enter the name of file to copy into : \n");
	scanf("%s",fileName2);
	tgtFile = fopen(fileName2,"w+");
	if(tgtFile == NULL){
		printf("File cannot be opened\n");
		exit(1);
	}
	char c = fgetc(srcFile);
	int flag = 0;
	while(c!=EOF){
		if(c == '#'){
			flag = 1;
		}
		if(flag == 1){
			c = fgetc(srcFile);
			if(c == '\n') {
				flag = 0;
				c = fgetc(srcFile);
			}
			continue;
		}
		fputc(c,tgtFile);
		c = fgetc(srcFile);
	}
	fclose(srcFile);
	fclose(tgtFile);
}