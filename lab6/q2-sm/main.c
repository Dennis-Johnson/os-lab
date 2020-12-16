#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct Shared_Use_st
{
    int wby;
    char some_text;
};

int main()
{
    struct Shared_Use_st *shared_obj;
    void *sm = 0;
    int shmid;
    char ch;

    shmid = shmget((key_t)1234, sizeof(struct Shared_Use_st), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget error: ");
        exit(EXIT_FAILURE);
    }

    sm = shmat(shmid, (void *)0, 0);
    if (sm == (void *)-1)
    {
        perror("shmget error: ");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)sm);
    shared_obj = (struct Shared_Use_st *)sm;

    pid_t pid = fork();
    if (pid == -1)
    {
        printf("Error!");
        exit(0);
    }
    else if (pid == 0)
    {
        shared_obj->wby = 0;
        while (!shared_obj->wby)
            ;
        if (shared_obj->wby)
        {
            ch = shared_obj->some_text;
            ch = ch + 1;
            shared_obj->some_text = ch;
            shared_obj->wby = 0;
        }
    }
    else
    {
        while (shared_obj->wby == 1)
        {
            sleep(1);
            printf("Blocking for Client:\n");
        }
        printf("Enter a letter from the alphabet: ");
        scanf("%c", &ch);
        shared_obj->some_text = ch;
        shared_obj->wby = 1;
        while (shared_obj->wby)
            ;

        printf("Child Output:%c\n", shared_obj->some_text);
    }
    exit(EXIT_SUCCESS);
}
