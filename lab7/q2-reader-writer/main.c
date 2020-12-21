#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

#define LEN_ARRAY 10

volatile int count = 1;
int numReaders = 0;
sem_t wrt;
pthread_mutex_t mutex;

void *writer(void *wno)
{
  sem_wait(&wrt);
  count = count * 2;
  printf("Writer %d: %d\n", *((int *)wno), count);
  sem_post(&wrt);

  return NULL;
}

void *reader(void *rno)
{
  pthread_mutex_lock(&mutex);
  numReaders++;
  if (numReaders == 1)
  {
    sem_wait(&wrt);
  }
  pthread_mutex_unlock(&mutex);
  printf("Reader %d: %d\n", *((int *)rno), count);
  numReaders--;
  if (numReaders == 0)
  {
    sem_post(&wrt);
  }
  pthread_mutex_unlock(&mutex);
  return NULL;
}

int main()
{
  int arr[LEN_ARRAY] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  pthread_t readers[10], writers[5];

  pthread_mutex_init(&mutex, NULL);
  sem_init(&wrt, 0, 1);
  for (int i = 0; i < 10; i++)

    pthread_create(&readers[i], NULL, (void *)reader, (void *)&arr[i]);

  for (int i = 0; i < 5; i++)
    pthread_create(&writers[i], NULL, (void *)writer, (void *)&arr[i]);

  for (int i = 0; i < 10; i++)
    pthread_join(readers[i], NULL);

  for (int i = 0; i < 5; i++)
    pthread_join(writers[i], NULL);

  pthread_mutex_destroy(&mutex);
  sem_destroy(&wrt);

  return 0;
}