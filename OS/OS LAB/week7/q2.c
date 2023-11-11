#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t wrt;
pthread_mutex_t mutex;
int count = 1;
int readcount = 0;
void *writer(void *arg)
{
    sem_wait(&wrt);
    count = count * 2;
    printf("Writer modified count to: %d\n",count);
    sem_post(&wrt);
}
void *reader(void *arg)
{
    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);
    printf("Reader read count as: %d\n",count);
    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
}
int main()
{
    pthread_t read[5], write[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);
    for (int i = 0; i < 5; i++)
        pthread_create(&read[i], NULL, (void *)reader, 0);
    for (int i = 0; i < 2; i++)
        pthread_create(&write[i], NULL, (void *)writer, 0);
    for (int i = 0; i < 5; i++)
        pthread_join(read[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(write[i], NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}