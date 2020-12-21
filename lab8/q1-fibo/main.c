#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *generateFibonacci(void *param)
{
  int *arr = (int *)param;
  int n = arr[0];
  arr[1] = 0;
  arr[2] = 1;
  for (int i = 3; i <= n; i++)
    arr[i] = arr[i - 1] + arr[i - 2];

  return NULL;
}

int main(int argc, char const *argv[])
{
  int n;
  printf("Enter no of Fibonacci numbers to generate : \n");
  scanf("%d", &n);

  int *arr = (int *)malloc((n + 1) * sizeof(int));
  arr[0] = n;

  pthread_t generator;
  pthread_create(&generator, NULL, &generateFibonacci, (void *)arr);
  pthread_join(generator, NULL);

  printf("Display array: \n");
  for (int i = 1; i <= n; i++)
    printf("%d\n", arr[i]);

  return 0;
}