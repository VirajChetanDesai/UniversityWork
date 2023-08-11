// Compiler Design lab 2
//Q1) WAP That takes a file as input and replaces blank spaces and tabs by single space and writes the output to a file.
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
	char prev = c;
	while(c!=EOF){
		if((prev == ' ' && c == prev)||(c == '\t' && prev == ' ')){
			continue;
		}else if(prev != ' ' && c == ' '){
			fputc(c,tgtFile);
		}else if(c == '\t'){
			fputc(' ',tgtFile);
		}else{
			fputc(c,tgtFile);
		}
		prev = c;
		c = fgetc(srcFile);
	}
	fclose(srcFile);
	fclose(tgtFile);
}