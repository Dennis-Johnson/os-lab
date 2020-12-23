#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include "common.h"

#define FIFO_NAME "/tmp/copy_fifo"

int main()
{
	FILE *fin;
	int pipe_fd, res, ch;

	//Read input file
	fin = fopen(INPUT_PATH, "rb");
	if (fin == NULL)
	{
		perror("Cant open input file: ");
		exit(EXIT_FAILURE);
	}

	if (access(FIFO_NAME, F_OK) == -1)
	{
		res = mkfifo(FIFO_NAME, 0777);
		if (res != 0)
		{
			fprintf(stderr, "Could not create FIFO %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	printf("Process %d opening FIFO\n", getpid());
	pipe_fd = open(FIFO_NAME, O_WRONLY);
	printf("Process %d opened FIFO with fd %d\n", getpid(), pipe_fd);

	if (pipe_fd == -1)
	{
		perror(" ");
		exit(EXIT_FAILURE);
	}

	do
	{
		ch = fgetc(fin);
		res = write(pipe_fd, &ch, sizeof(int));
		if (res == -1)
		{
			perror("Write error on pipe: ");
			exit(EXIT_FAILURE);
		}
	} while (ch != EOF);

	fclose(fin);
	close(pipe_fd);

	printf("Reader Process %d is done.\n", getpid());

	return 0;
}
