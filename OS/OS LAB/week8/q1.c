#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>

void* thread_code( void * param )
{
	int size = (int)param;
	int* array = (int*)calloc(size,sizeof(int));
	array[0]=0;
	array[1]=1;
	for(int i=2;i<size;i++){
		array[i]=array[i-1]+array[i-2];
	}
	return (void *)array;
}

int main(int argc, char* argv[])
{
	if(argc < 2){
        printf("Not enough arguments\n");
        exit(0);
    }
	int size = atoi(argv[1]);
	int* array = (int*)calloc(size,sizeof(int));
	array[0]=size;
	pthread_t thread;
	pthread_create(&thread, 0, &thread_code, (void*)size);
	pthread_join(thread,(void**)&array);
	for(int i=0;i<size;i++){
		printf("%d ",array[i]);
	}
	return 0;
}