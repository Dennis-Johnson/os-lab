#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/ipc.h>
#include <semaphore.h>

#define N 5

time_t end_time;
sem_t mutex, customers, barbers;
int count = 0;

void *barber(void *arg)
{
  while (time(NULL) < end_time || count > 0)
  {
    sem_wait(&customers);
    sem_wait(&mutex);
    count--;
    printf("\nBarber: Cut hair\nCurrent count is:%d\n", count);
    sem_post(&mutex);
    sem_post(&barbers);
    sleep(3);
  }

  return NULL;
}

void *customer(void *arg)
{
  while (time(NULL) < end_time)
  {
    sem_wait(&mutex);
    if (count < N)
    {
      count++;
      printf("\nCustomer: Add count\nCurrent count is:%d\n", count);
      sem_post(&mutex);
      sem_post(&customers);
      sem_wait(&barbers);
    }
    else
      sem_post(&mutex);
    sleep(1);
  }

  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t id1, id2;
  int status = 0;
  end_time = time(NULL) + 20;
  sem_init(&mutex, 0, 1);
  sem_init(&customers, 0, 0);
  sem_init(&barbers, 0, 1);
  status = pthread_create(&id1, NULL, (void *)barber, NULL);
  if (status != 0)
    perror("Create barber failed!\n");
  status = pthread_create(&id2, NULL, (void *)customer, NULL);
  if (status != 0)
    perror("Create customer failed!\n");
  pthread_join(id2, NULL);
  pthread_join(id1, NULL);
  exit(0);
}
