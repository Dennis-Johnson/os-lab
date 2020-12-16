#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>

#define FIFO_NAME "/tmp/pcp_fifo"

int main()
{
	int pipe_fd, res;
	int n = 0;

	printf("Process %d opening FIFO to read\n", getpid());
	pipe_fd = open(FIFO_NAME, O_RDONLY);
	printf("Process %d result %d\n", getpid(), pipe_fd);

	if (pipe_fd == -1)
	{
		perror(" ");
		exit(EXIT_FAILURE);
	}

	do
	{
		res = read(pipe_fd, &n, sizeof(int));
		printf("Read int %d from FIFO_Q\n", n);
	} while (res > 0);

	close(pipe_fd);
	printf("Process %d is done.\n", getpid());

	return 0;
}
