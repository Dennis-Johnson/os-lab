#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

int buffer[5], f, r;
sem_t mutex, full, empty;

void *produce(void *arg)
{
  int i;
  for (i = 0; i < 10; i++)
  {
    sem_wait(&empty);
    sem_wait(&mutex);
    printf("Produced item %d\n", i);
    buffer[(++r) % 10] = i;
    sleep(1);
    sem_post(&mutex);
    sem_post(&full);
    printf("full %u\n", full);
  }

  return NULL;
}
void *consume(void *arg)
{
  int item, i;
  for (i = 0; i < 10; i++)
  {
    sem_wait(&full);
    printf("full %u\n", full);
    sem_wait(&mutex);
    item = buffer[(++f) % 10];
    printf("Consumed item %d\n", item);
    sleep(1);
    sem_post(&mutex);
    sem_post(&empty);
  }

  return NULL;
}
int main()
{
  pthread_t producer, consumer;
  sem_init(&mutex, 0, 1);
  sem_init(&full, 0, 1);
  sem_init(&empty, 0, 10);

  pthread_create(&producer, NULL, produce, NULL);
  pthread_create(&consumer, NULL, consume, NULL);

  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);

  return 0;
}
