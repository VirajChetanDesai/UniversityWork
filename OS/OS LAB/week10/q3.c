#include<stdio.h>
#include<stdlib.h>
struct DSA {
int request_id;
int arrival_time_stamp;
int cylinder;
int address;
int process_id;
};
typedef struct DSA DSA;
void main()
{
int n,i,j,k,seek=0,diff;
float avg;
DSA head;
head.request_id=0;
head.arrival_time_stamp=0;
head.cylinder=0;
head.address=0;
head.process_id=0;
printf("*** FCFS Disk Scheduling Algorithm ***\n");
printf("Enter the size of Queue\t\n");
scanf("%d",&n);
DSA queue[n+1];
printf("Enter the Queue\t\n");
for(i=1;i<=n;i++)
{
	scanf("%d",&queue[i].request_id);
	scanf("%d",&queue[i].arrival_time_stamp);
	scanf("%d",&queue[i].cylinder);
	scanf("%d",&queue[i].address);
	scanf("%d",&queue[i].process_id);
}
printf("Enter the initial head position\t");
scanf("%d",&head.cylinder);
queue[0]=head;
printf("\n");
for(int j=1;j<=n;j++)
{
	DSA temp;
	for(int k=j+1;k+1<=n;k++)
	{
		if(queue[k].arrival_time_stamp>queue[k+1].arrival_time_stamp)
		{
			temp=queue[k];
			queue[k]=queue[k+1];
			queue[k+1]=temp;
		}
	}
}
printf("\nQueue after sorting is:\n");
for(int k=1;k<=n;k++)
{
	printf("%d %d\n",queue[k].cylinder, queue[k].arrival_time_stamp);
}
for(j=0;j<=n-1;j++)
{
diff=abs(queue[j+1].cylinder-queue[j].cylinder);
seek+=diff;
printf("Move from %d to %d with Seek %d\n",queue[j].cylinder,queue[j+1].cylinder,diff);
}
printf("\nTotal Seek Time is %d\t",seek);
avg=seek/(float)n;
printf("\nAverage Seek Time is %f\t",avg);

printf("***\n\nSSTF Disk Scheduling Algorithm ***\n");
int currPosition=head.cylinder;
int diskCovered[n+1];
diskCovered[0]=1;
for(int l=1;l<=n;l++)
{
	diskCovered[l]=0;
}
seek=0;
int currProcess=0;
for(int k=1;k<=n;k++)
{
	int minSeekTime=1000;
	int difference=0;
	int nextProcess=0;
	for(int m=1;m<=n;m++)
	{
		if(diskCovered[m]!=1)
		{
			difference=abs(currPosition-queue[m].cylinder);
			if(difference<minSeekTime)
			{
				minSeekTime=difference;
				nextProcess=m;
			}
		}
	}
	seek+=minSeekTime;
	diskCovered[nextProcess]=1;
	printf("Move from %d to %d with Seek %d\n",queue[currProcess].cylinder,queue[nextProcess].cylinder,minSeekTime);
	currProcess=nextProcess;
	currPosition=queue[currProcess].cylinder;
}
printf("\nTotal Seek Time is %d\t",seek);
avg=seek/(float)n;
printf("\nAverage Seek Time is %f\t",avg);
}