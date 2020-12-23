#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

int buffer[5], f, r;
sem_t mutex, full, spaces;

void *produce(void *param)
{
    for (int i = 0; i < 12; i++)
    {
        sem_wait(&spaces);
        sem_wait(&mutex);
        buffer[++r % 10] = i % 10;
        printf("Producer wrote %d\n", i);
        sleep(1);
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consume(void *param)
{
    for (int i = 0; i < 12; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        i = buffer[++f % 10];
        printf("Consumer got %d\n", i);
        sleep(1);
        sem_post(&mutex);
        sem_post(&spaces);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t consumer, producer;
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 1);
    sem_init(&spaces, 0, 10);

    pthread_create(&producer, 0, produce, 0);
    pthread_create(&consumer, 0, consume, 0);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&spaces);

    return 0;
}