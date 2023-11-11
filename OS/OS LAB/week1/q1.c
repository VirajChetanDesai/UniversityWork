#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include<string.h>
#include<stdio.h>

int main(int argc, char const *argv[])
{
	char c;
	char temp[200];
	int in, i=0, flag=0;
	if(argc!=3)
	{
		printf("Insufficient arguments");
		exit(0);
	}

    in = open(argv[2], O_RDONLY);
    if(in==-1)
    {
    	printf("File not found");
    	exit(0);
    }

	while(read(in,&c,1) > 0)
	{
		if(c!='\n')
			temp[i++]=c;
		else
		{
			temp[i]='\0';
			i=0;
			if(strstr(temp,argv[1])!=NULL)
			{
				flag++;
				printf(" %s\n",temp);
			}
		}
	}

	if(flag==0)
	{
		printf("Word not found");
	}
}