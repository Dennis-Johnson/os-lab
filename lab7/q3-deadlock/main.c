#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

/*
Program to demonstrate deadlocks
*/

sem_t sem1, sem2;
int shared;

void *routineA()
{
  sem_wait(&sem1);
  printf("In function A\n");
  sleep(10);
  printf("Get sem 2. Have sem 1\n");
  sem_wait(&sem2);
  sem_post(&sem2);
  sem_post(&sem1);

  return NULL;
}
void *routineB()
{
  sem_wait(&sem2);
  printf("In function B\n");
  sleep(10);
  printf("Get sem 1. Have sem 2\n");
  sem_wait(&sem1);
  sem_post(&sem1);
  sem_post(&sem2);

  return NULL;
}
int main()
{
  pthread_t thread1, thread2;
  sem_init(&sem1, 0, 1);
  sem_init(&sem2, 0, 1);
  pthread_create(&thread1, NULL, routineA, NULL);
  pthread_create(&thread2, NULL, routineB, NULL);
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}