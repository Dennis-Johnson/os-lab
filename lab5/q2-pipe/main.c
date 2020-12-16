#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEN_ARRAY 4

/*
Demonstrate creation, writing to, and reading from a pipe
*/

int array[LEN_ARRAY] = {1,2,3,4};

int main(){
	int pipe_fd[2];
	pid_t cpid;
	int n;

	if(pipe(pipe_fd) == -1){
		perror("Pipe Error: ");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if(cpid == -1){
		perror("Fork Error: ");
		exit(EXIT_FAILURE);
	}

	if(cpid == 0){
		//Child reads from pipe
		close(pipe_fd[1]);
		while(read(pipe_fd[0], &n, sizeof(int)) > 0){
			printf("Child %d : Read %d from pipe\n", getpid(), n);
		}

		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
	else {
		//Parent writes into pipe
		close(pipe_fd[0]);
		int i = 0;

		while(i < LEN_ARRAY){
			size_t b_wrote = write(pipe_fd[1], array + i, sizeof(int));

			if(b_wrote != 0)
				printf("Parent %d: Wrote %d into pipe\n", getpid(), array[i]);
			i++;
		}

		close(pipe_fd[1]);
		wait(NULL);
	}

	return 0;
}