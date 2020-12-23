#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>

#define LEN_BUFFER 64

int main()
{
    int p_fd[2];
    pid_t pid;

    int recv;
    int num_of_messages = 5;

    if (pipe(p_fd) == -1)
    {
        perror("Can't make pipe: ");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Fork error : ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        //Child writes to pipe
        close(p_fd[0]);
        for (int i = 0; i < num_of_messages; i++)
        {
            size_t len_written = write(p_fd[1], &i, sizeof(int));
            if (len_written == 0)
            {
                perror("Didn't write anything ");
                break;
            }

            printf("Child wrote %d to pipe\n", i);
        }
        close(p_fd[1]);
    }
    else
    {
        // Parent reads from the pipe
        close(p_fd[1]);
        for (int i = 0; i < num_of_messages; i++)
        {
            read(p_fd[0], &recv, sizeof(int));
            printf("Parent read %d from pipe\n", recv);
        }
        close(p_fd[0]);
        wait(NULL);
    }

    return 0;
}
