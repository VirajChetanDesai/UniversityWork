#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>

void* thread_code( void * param )
{
	int* array = (int*)param;
	int sum=0;
	int size = array[0];
	for(int i=1;i<size+1;i++){
		if(array[i]>0)
			sum+=array[i];
	}
	return (void *)sum;
}

int main()
{
	int size=0;
	printf("Enter size of the array:\n");
	scanf("%d",&size);
	int array[size+1];
	array[0]=size;
	printf("Enter the elements of the array:\n");
	for(int i=1;i<size+1;i++){
		scanf("%d",&array[i]);
	}
	int sum=0;
	pthread_t thread;
	pthread_create(&thread, 0, &thread_code, (void*)array);
	pthread_join(thread,(void**)&sum);
	printf("Total sum is %d",sum);
	return 0;
}