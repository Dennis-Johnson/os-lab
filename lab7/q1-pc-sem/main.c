#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[10], buf_index = 0;
sem_t mutex, full, empty;

void *produce(void *param){
  for(int i = 0; i < 10; i++){
    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[buf_index++] = i;
    printf("Produced item %d\n", i);

    sem_post(&mutex);
    sem_post(&full);
  }

  return NULL;
}

void *consume(void *param){
  int item;
  for(int i = 0; i < 10; i++){
   sem_wait(&empty);
   sem_wait(&mutex);
   
   item = buffer[buf_index--];
   printf("Consumed item %d\n", item);

   sem_post(&mutex);
   sem_post(&full);
  }  

  return NULL;
}

int main(){
  pthread_t producer, consumer;
  sem_init(&mutex, 0, 1);
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, 10);

  pthread_create(&producer, 0, produce, 0);
  pthread_create(&consumer, 0, consume, 0);

  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);
  return 0;
}
