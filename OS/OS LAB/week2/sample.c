#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void printdir(char *dir)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) {
	fprintf(stderr,"cannot open directory: %s\n", dir);
	return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) {
	lstat(entry->d_name,&statbuf);
	if(S_ISDIR(statbuf.st_mode)) {
		if(strcmp(".",entry->d_name) == 0 ||
		strcmp("..",entry->d_name) == 0)
		continue;
		printf("%s/\n",entry->d_name);
		printdir(entry->d_name);
	}
	else printf("%s\n",entry->d_name);
	}
	chdir("..");
	closedir(dp);
}

int main()
{
	char directory[100] = "/home/student/Desktop/C1_210905006";
	printdir(directory);
}