#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *genFib(void *param)
{
    int *arr = (int *)param;
    int n = arr[0];

    printf("Size is %d\n", n);

    arr[1] = 0;
    arr[2] = 1;

    if (n <= 2)
    {
        pthread_exit(NULL);
    }

    for (int i = 3; i <= n; i++)
    {
        arr[i] = arr[i - 2] + arr[i - 1];
    }

    pthread_exit(NULL);
}

int main()
{
    int size = 0;
    int *arr;
    pthread_t fib_thread;

    printf("Enter number of numbers to generate: ");
    scanf("%d", &size);

    if (size <= 2)
        return 0;

    arr = calloc(size + 1, sizeof(int));
    arr[0] = size;

    pthread_create(&fib_thread, NULL, genFib, arr);
    pthread_join(fib_thread, NULL);

    for (int i = 1; i <= size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
