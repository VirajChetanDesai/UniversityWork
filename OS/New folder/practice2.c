#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100

typedef struct Process{
    int process_id;
    int timeReqd;
}Process;

Process queue[MAX_SIZE];

void multilevelfeedbackqueue(int processes){
    int netTime = 0;
    int* quantums = {4,8,16};
    for(int queueNumber = 0 ;  queueNumber <3 ; queueNumber++){
        for(int i = 0 ; i < processes ; i++){
            Process p = queue[i];
            if(p.process_id == 0) continue;
            if(quantums[queueNumber] <= p.timeReqd){
                p.timeReqd -= quantums[queueNumber];
                netTime += quantums[queueNumber];
            }else{
                printf("Process %d has been executed at %d ms in RR",p.process_id,netTime);
                p.process_id = 0;
            }
        }
    }
    for(int i = 0 ; i < processes ; i++){
        Process p = queue[i];
        if(p.process_id != 0){
            netTime += p.timeReqd;
            printf("Process %d has been executed at %d ms in FCFS",p.process_id,netTime);
            p.process_id = 0;
        }
    }
}

int main(){
    int processes;
    printf("Enter number of processes:");
    scanf("%d",&processes);
    for(int i = 0 ; i < processes ; i++){
        Process *p = (Process*)calloc(1,sizeof(Process));
        printf("Enter time reqd: \n");
        scanf("%d",&p->timeReqd);
        p->process_id = i+1;
    }
    multilevelfeedbackqueue(processes);
    return 0;
}