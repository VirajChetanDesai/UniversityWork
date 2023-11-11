#include<stdio.h>
#include<stdlib.h>

char fifo[15];
int front=0;
int rear=0;

void write(char c)
{
	if(front>=15)
	{
		printf("FIFO full\n");
		exit(0);
	}
	fifo[front++]=c;
}

void read()
{
	if(rear>=15)
	{
		printf("FIFO empty\n");
		exit(0);
	}
	printf("%c\n",fifo[rear++]);
}

int main()
{
	char c;
	int choice=0;
	while(choice!=3)
	{
		printf("Enter 1 to write to FIFO, 2 to read and 3 to exit:\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("Enter data to be written:\n");
				    scanf(" %c",&c);
				    write(c);
				    break;
			case 2: read();
		    		break;
		    case 3: printf("Exiting\n");
		    		break;
		}
		if(choice==3)
		{
			exit(0);
		}
	}

	return 0;
}