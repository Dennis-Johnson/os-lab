#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct P_Args
{
  int a, b;
} P_Args;

void *computeSum(void *param)
{
  P_Args *pa = param;
  int sum = pa->a + pa->b;
  return (void *)sum;
}

int main()
{
  P_Args args;
  int ret_val = 0;

  printf("Enter two non-negative integers: ");
  scanf("%d %d", &(args.a), &(args.b));

  pthread_t adder;
  pthread_create(&adder, 0, &computeSum, (void *)&args);

  pthread_join(adder, (void **)&ret_val);
  printf("\nAdder thread computed the sum: %d\n", ret_val);

  return 0;
}
