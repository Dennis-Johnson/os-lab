#include "common.h"

//Producer
int main()
{
	int fd;
	int arr[LEN_ARR] = {1, 2, 3, 4, 5};

	if (access(FIFO_PATH, F_OK) == -1)
	{
		if (mkfifo(FIFO_PATH, 0777) == -1)
		{
			perror("FIFO creation error: ");
			exit(EXIT_FAILURE);
		}
	}
	else
		printf("Producer started PID: %u\n", getpid());

	if ((fd = open(FIFO_PATH, O_WRONLY)) == -1)
	{
		perror("Open for write error: ");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < LEN_ARR; i++)
	{
		ssize_t len_wr = write(fd, &arr[i], sizeof(int));
		printf("Producer wrote %d\n", arr[i]);

		if (len_wr == -1)
		{
			perror("Write error: ");
			exit(EXIT_FAILURE);
		}
	}

	close(fd);
	return 0;
}
