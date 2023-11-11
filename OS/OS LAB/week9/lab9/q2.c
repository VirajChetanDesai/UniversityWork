#include<stdio.h>

struct process
{
    char name;
    int AT,BT,WT,TAT,RT,CT;
}Q1[10],Q2[10],Q3[10];/*Three queues*/

int n;
void sortByArrival()
{
    struct process temp;
    int i,j;
    for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(Q1[i].AT>Q1[j].AT)
                    {
                        temp=Q1[i];
                        Q1[i]=Q1[j];
                        Q1[j]=temp;
                    }
            }
        }
}

int main()
{
    int i,j,k=0,r=0,time=0,tq1=5,tq2=8,flag=0;
    char c;
    printf("Enter no of processes:");
    scanf("%d",&n);
    for(i=0,c='A';i<n;i++,c++)
    {
        Q1[i].name=c;
        printf("\nEnter the arrival time and burst time of process %c: ",Q1[i].name);
        scanf("%d%d",&Q1[i].AT,&Q1[i].BT);
        Q1[i].RT=Q1[i].BT;/*save burst time in remaining time for each process*/

    }
    sortByArrival();
    time=Q1[0].AT;
    printf("Process in first queue following RR with qt=5");
    printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
    for(i=0;i<n;i++)
    {

        if(Q1[i].RT<=tq1)
        {

            time+=Q1[i].RT;/*from arrival time of first process to completion of this process*/
            Q1[i].RT=0;
            Q1[i].WT=time-Q1[i].AT-Q1[i].BT;/*amount of time process has been waiting in the first queue*/
            Q1[i].TAT=time-Q1[i].AT;/*amount of time to execute the process*/
            printf("\n%c\t\t%d\t\t%d\t\t%d",Q1[i].name,Q1[i].BT,Q1[i].WT,Q1[i].TAT);

        }
        else/*process moves to queue 2 with qt=8*/
        {
            Q2[k].WT=time;
            time+=tq1;
            Q1[i].RT-=tq1;
            Q2[k].BT=Q1[i].RT;
            Q2[k].RT=Q2[k].BT;
            Q2[k].name=Q1[i].name;
            k=k+1;
            flag=1;
        }
    }

    if(flag==1)
    {
        printf("\nProcess in second queue following RR with qt=8");
        printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
    }
    
    for(i=0;i<k;i++)
    {
        if(Q2[i].RT<=tq2)
        {
            time+=Q2[i].RT;/*from arrival time of first process +BT of this process*/
            Q2[i].RT=0;
            Q2[i].WT=time-tq1-Q2[i].BT;/*amount of time process has been waiting in the ready queue*/
            Q2[i].TAT=time-Q2[i].AT;/*amount of time to execute the process*/
            printf("\n%c\t\t%d\t\t%d\t\t%d",Q2[i].name,Q2[i].BT,Q2[i].WT,Q2[i].TAT);

        }
        else/*process moves to queue 3 with FCFS*/
        {
            Q3[r].AT=time;
            time+=tq2;
            Q2[i].RT-=tq2;
            Q3[r].BT=Q2[i].RT;
            Q3[r].RT=Q3[r].BT;
            Q3[r].name=Q2[i].name;
            r=r+1;
            flag=2;
        }
    }

    if(flag==2)
    {
        printf("\nProcess in third queue following FCFS ");
    }
    for(i=0;i<r;i++)
    {
        if(i==0)
                Q3[i].CT=Q3[i].BT+time-tq1-tq2;
            else
                Q3[i].CT=Q3[i-1].CT+Q3[i].BT;

    }

    for(i=0;i<r;i++)
    {
        Q3[i].TAT=Q3[i].CT;
        Q3[i].WT=Q3[i].TAT-Q3[i].BT;
        printf("\n%c\t\t%d\t\t%d\t\t%d\t\t",Q3[i].name,Q3[i].BT,Q3[i].WT,Q3[i].TAT);

    }

}













// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>

// typedef struct Queue
// {
//     int queue[10];
//     int front,rear,capacity;
// }Queue;

// int isFull(Queue *pq)
// {
//     if(pq->rear == pq->capacity-1)
//         return 1;
//     return 0;
// }

// int isEmpty(Queue *pq)
// {
//     if(pq->front == -1)
//         return 1;
//     return 0;
// }

// void insert(Queue *pq,int item)
// {
//     if(isFull(pq))
//     {
//         printf("Queue is full!");
//         return;
//     }
//     if(pq->front == -1)
//     {
//         pq->front = 0;
//     }
//     pq->queue[++pq->rear] = item;
// }

// //1 2 3 4
// //2 3 4
// //3 4
// //4



// int delete(Queue *pq)
// {
//     int item;
//     if(isEmpty(pq))
//     {
//         printf("Queue is empty!");
//         return -1;
//     }
//     item = pq->queue[pq->front];
//     if(pq->front == pq->rear)
//     {
//         pq->front = -1;
//         pq->rear = -1;
//     }
//     else
//         pq->front = pq->front+1;
//     return item;
// }

// Queue* createQueue()
// {
//     Queue *pq = (Queue*)malloc(sizeof(Queue));
//     pq->front = -1;
//     pq->rear = -1;
//     pq->capacity = 10;
//     return pq;
// }

// void displayQueue(Queue *pq)
// {
//     if (isEmpty(pq))
//     {
//         printf("Queue is empty\n");
//     }
//     else
//     {
//         printf("Queue contents: ");
//         for (int i = pq->front; i <= pq->rear; i++)
//         {
//             printf("%d ", pq->queue[i]);
//         }
//         printf("\n");
//     }
// }



// int main()
// {

//     Queue *q[3];

//     q[0] = createQueue(); //4ms
//     q[1] = createQueue(); //8ms
//     q[2] = createQueue(); //16ms

//     int processesTimes[4] = {6, 3, 32, 24}; 
//     int processesPriorities[4] = {1, 1, 3, 2}; 
//     int processesCount = 4; 

//     for (int i = 0; i < processesCount; i++)
//     { 
//         if (processesPriorities[i] == 1) 
//             insert(q[0],i+1); 
//         if (processesPriorities[i] == 2) 
//             insert(q[1],i+1); 
//         if (processesPriorities[i] == 3) 
//             insert(q[2],i+1); 
//     } 

//     displayQueue(q[0]);
//     displayQueue(q[1]);
//     displayQueue(q[2]);

//     while(!isEmpty(q[0]) || !isEmpty(q[1]) || !isEmpty(q[2]))
//     {
//         while (!isEmpty(q[0])) 
//         { 
//             int PID = delete(q[0])-1; 
//             if (PID < 0) 
//                 break; 
//             processesTimes[PID] -= 4; 
//             if (processesTimes[PID] <= 0) 
//                 printf("Process %d finished execution in 4ms\n", PID); 
//             else 
//             { 
//                 printf("Process %d was given 4ms to execute.Remaining time: %d.Putting process in queue 2.\n", PID, processesTimes[PID]); 
//                 insert(q[1], PID + 1); 
//             } 
//             sleep(1); 
//         } 

//         while (!isEmpty(q[1]) && isEmpty(q[0])) 
//         { 
//             int PID = delete(q[1])-1; 
//             if (PID < 0) 
//                 break; 
//             processesTimes[PID] -= 8; 
//             if (processesTimes[PID] <= 0) 
//                 printf("Process %d finished execution in 8ms.\n", PID);
//             else 
//             { 
//                 printf("Process %d was given 8ms to execute. Remaining time: %d.Putting process in queue3.\n", PID, processesTimes[PID]); 
//                 insert(q[2], PID + 1); 
//             } 
//             sleep(1); 
//         } 

//         while (!isEmpty(q[2]) && isEmpty(q[0])) 
//         { 
//             int PID = delete(q[2])-1; 
//             if (PID < 0) 
//                 break; 
//             processesTimes[PID] -= 16; 
//             if (processesTimes[PID] <= 0) 
//                 printf("Process %d finished execution in 16ms.\n", PID);
//             else 
//             { 
//                 printf("Process %d was given 16ms to execute. Remaining time: %d.Putting process in queue3.\n", PID, processesTimes[PID]); 
//                 insert(q[2], PID + 1);
//             } 
//             sleep(1); 
//         } 
//     }

// }

