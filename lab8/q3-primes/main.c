#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define MAX_SIZE 256
typedef struct PrimeStruct
{
    int m;
    int n;
    int prime_count;
    int primes[MAX_SIZE];
} PrimeStruct;

void *generate_primes(void *param)
{
    PrimeStruct *parameter = (PrimeStruct *)param;
    for (int i = parameter->m; i <= parameter->n; i++)
    {
        int root = sqrt(i);
        int j;
        for (j = 2; j <= root; j++)
        {
            if (i % j == 0)
                break;
        }
        if (j == root + 1)
        {
            parameter->primes[parameter->prime_count] = i;
            parameter->prime_count += 1;
        }
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    PrimeStruct p;
    printf("Enter range : ");
    scanf("%d %d", &(p.m), &(p.n));

    p.prime_count = 0;
    pthread_t thread;
    pthread_create(&thread, 0, &generate_primes, (void *)&p);
    pthread_join(thread, NULL);

    for (int i = 0; i < p.prime_count; i++)
        printf("%d\n", p.primes[i]);

    printf("\n");
    return 0;
}
