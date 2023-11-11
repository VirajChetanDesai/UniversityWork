#include <pthread.h>
#include <stdio.h>
void* child_thread1( void * param )
{
	int *arr = (int*)param;
	int num = arr[0];
	int evensum;
	for(int i=1;i<num+1;i++)
	{
		if(arr[i]%2==0)
		{
			evensum+=arr[i];
		}
	}
	printf("Even sum is : %d\n", evensum);
}
void* child_thread2( void * param )
{
	int *arr = (int*)param;
	int num = arr[0];
	int oddsum;
	for(int i=1;i<num+1;i++)
	{
		if(arr[i]%2!=0)
		{
			oddsum+=arr[i];
		}
	}
	printf("Odd sum is : %d\n", oddsum);
}
int main()
{
	pthread_t thread1;
	pthread_t thread2;
	int oddsum,evensum;
	int num;
	printf("Enter size of array: ");
	scanf("%d", &num);
	int arr[num+1];
	arr[0]=num;
	printf("Enter elements of the array: ");
	for(int i=1;i<num+1;i++)
	{
		scanf("%d", &arr[i]);
	}
	
	pthread_create(&thread1,0,&child_thread1,(void*)arr);
	pthread_create(&thread2,0,&child_thread2,(void*)arr);
	pthread_join(thread1,0);
	pthread_join(thread2,0);
}