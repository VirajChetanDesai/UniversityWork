#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
int buf[10],f,r, num1, num2;
sem_t mutex,full,empty;
void *produce(void *arg)
{
int i;
	for(i=0;i<20;i++)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		sem_getvalue(&full,&num1);
		sem_getvalue(&empty,&num2);
		printf("\nProduced item is %d, full is %d, empty is %d\n",i, num1, num2);
		buf[(++r)%10]=i;
		sleep(1);
		sem_post(&mutex);
		sem_post(&full);
	}
}
void *consume(void *arg)
{
	int item,i;
	for(i=0;i<20;i++)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		item=buf[(++f)%10];
		sem_getvalue(&full,&num1);
		sem_getvalue(&empty,&num2);
		printf("\nConsumed item is %d, full is %d, empty is %d\n",item, num1, num2);
		sleep(1);
		sem_post(&mutex);
		sem_post(&empty);
	}
}
int main()
{
	pthread_t tid1,tid2;
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,10);
	pthread_create(&tid1,NULL,produce,NULL);
	pthread_create(&tid2,NULL,consume,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}