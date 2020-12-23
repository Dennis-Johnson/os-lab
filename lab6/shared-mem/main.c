#include "common.h"
// Using shared memory when theres a single reader and writer. Writer goes first.
// This doesn't make sense. Don't need shared mem here at all.

key_t key;
char *ptr;
int result;
sem_t mutex;

void *writer_routine(void *arg)
{
    char *str = "This is another string\n";
    printf("Writing to shared memory: %s\n", str);
    strcpy(ptr, str);
    sem_post(&mutex);
    pthread_exit(NULL);
}

void *reader_routine(void *arg)
{
    sem_wait(&mutex);
    printf("\nReading from shared memory:\n");
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        int ch = ptr[i];
        if (ch == EOF)
            break;

        printf("%c", ch);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t reader, writer;

    if ((key = ftok(FILE_NAME, 0)) == -1)
    {
        perror("Cant get key: ");
        exit(EXIT_FAILURE);
    }

    int shm_id = shmget(key, BLOCK_SIZE, 0666 | IPC_CREAT);

    printf("Attaching shared memory\n");
    if ((ptr = shmat(shm_id, NULL, 0)) == NULL)
        perror("Attach error: ");

    sem_init(&mutex, 0, 0);
    pthread_create(&reader, NULL, reader_routine, NULL);
    pthread_create(&writer, NULL, writer_routine, NULL);
    pthread_join(reader, NULL);
    pthread_join(writer, NULL);

    printf("\nDetaching shared memory\n");
    if ((result = shmdt(ptr)) == -1)
        perror("Detach error: ");

    printf("Deleting shared memory\n");
    result = shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}
