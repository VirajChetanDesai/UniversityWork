#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
sem_t mutex,full,empty;
int buf [10];
int index = 0;
int r = 0 , f = 0;
void* producer(void* args){
    for(int i = 0 ; i < 20 ; i++){
        sem_wait(&empty);
        sem_wait(&mutex);
        buf[(++r)%10] = 2*i;
        sleep(1);
        sem_post(&mutex);
        sem_post(&full);
        printf("Full");
    }
}

void* consumer(void* argss){
    int numberSent;
    for(int i = 0 ; i < 20 ; i++){
        sem_wait(&full);
        sem_wait(&mutex);
        int value = buf[(++f)%10];
        printf("%d",value);
        sleep(1);
        sem_post(&mutex);
        sem_post(&empty);
        printf("Empty");
    }
}
void main(){
    sem_init(&mutex,0,1);
    sem_init(&empty,0,10);
    sem_init(&full,0,0);
    pthread_t prod,cons;
    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);
    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    exit(0);
}