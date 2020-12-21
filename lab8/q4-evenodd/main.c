#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARR_LEN 6
static int arr[ARR_LEN];

void *sum_even(void *param){
  int sum = 0;
  for(int i = 0; i < ARR_LEN; i++){
    if(arr[i] % 2 == 0)
      sum += arr[i];
  }

  return (void *) sum;
}

void *sum_odd(void *param){
  int sum = 0;
  for(int i = 0; i < ARR_LEN; i++){
    if(arr[i] % 2 != 0)
      sum += arr[i];
  }
  
  return (void*) sum;
}

int main(){
  int even_sum = 0, odd_sum = 0;
  
  printf("Enter six integers: ");
  for(int i = 0; i < ARR_LEN; i++){
    scanf("%d", &arr[i]);
  }

  pthread_t even_adder, odd_adder;
  pthread_create(&even_adder, 0, &sum_even, NULL);
  pthread_create(&odd_adder, 0, &sum_odd, NULL);

  pthread_join(even_adder, (void **)&even_sum);
  pthread_join(odd_adder, (void **)&odd_sum);

  printf("\nEven sum: %d\nOdd Sum: %d\n Total: %d\n",even_sum, odd_sum, even_sum+odd_sum );

  return 0;
}

