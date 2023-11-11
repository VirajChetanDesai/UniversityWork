#include <pthread.h>
#include <stdio.h>
void* child_thread( void * param )
{
	int start,end,count,i,j;
	printf("Enter starting number: ");
	scanf("%d", &start);
	printf("Enter ending number: ");
	scanf("%d", &end);
	for(i=start; i<=end; i++)
    {
        for(j=2; j<i; j++)
        {
           if(i%j==0)
           {
               count++;
               break;
           }
        }
        if(count==0 && i!=1)
            printf("%d ", i);
        count = 0;
    }

	return 0;
}
int main()
{
	pthread_t thread;
	pthread_create(&thread,0,&child_thread,0);
	pthread_join( thread, 0);
}