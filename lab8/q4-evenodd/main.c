#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARR_LEN 6
int arr[ARR_LEN] = {
    1,
    2,
    3,
    4,
    5,
    6};

void *sum_even(void *param)
{
  int even_sum = 0;
  for (int i = 0; i < ARR_LEN; i++)
  {
    if (arr[i] % 2 == 0)
      even_sum += arr[i];
  }

  printf("\nEven sum: %d\n", even_sum);
  return (void *)even_sum;
}

void *sum_odd(void *param)
{
  int odd_sum = 0;
  for (int j = 0; j < ARR_LEN; j++)
  {
    if (arr[j] % 2 != 0)
      odd_sum += arr[j];
  }

  printf("\nOdd sum: %d\n", odd_sum);
  return (void *)odd_sum;
}

int main()
{
  int even_sum = 0, odd_sum = 0;

  printf("Array contents: ");
  for (int i = 0; i < ARR_LEN; i++)
  {
    printf("%d ", arr[i]);
  }

  pthread_t even_adder, odd_adder;
  pthread_create(&even_adder, NULL, sum_even, NULL);
  pthread_create(&odd_adder, NULL, sum_odd, NULL);

  pthread_join(even_adder, (void **)&even_sum);
  pthread_join(odd_adder, (void **)&odd_sum);

  printf("\n\nEven sum: %d\nOdd Sum: %d\n Total: %d\n", (int)even_sum, (int)odd_sum, even_sum + odd_sum);

  return 0;
}
