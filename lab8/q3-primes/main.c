#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define MAX_SIZE 256

int arr[MAX_SIZE];
int arr_ind = 0;

typedef struct PrimeArgs
{
    int low;
    int high;
} PrimeArgs;

void *genPrimes(void *param)
{
    PrimeArgs pa = *(PrimeArgs *)param;

    for (int i = pa.low; i <= pa.high; i++)
    {
        if (i < 2)
            continue;

        int flag = 0;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                flag = 1;
                break;
            }
        }

        if (!flag)
        {
            // Add prime number to list
            arr[arr_ind++] = i;
        }
    }

    pthread_exit(NULL);
}
int main()
{
    pthread_t prime_thread;
    int low, high;

    printf("Enter range for primes : ");
    scanf("%d %d", &low, &high);

    PrimeArgs pa = {low, high};

    pthread_create(&prime_thread, NULL, genPrimes, &pa);
    pthread_join(prime_thread, NULL);

    for (int i = 0; i < arr_ind; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
