#include "common.h"

//Reader
int main()
{
	int fd;
	int arr[LEN_ARR];

	if (access(FIFO_PATH, F_OK) == -1)
	{
		// Can't access the pipe
		perror("Can't access the FIFO: ");
		exit(EXIT_FAILURE);
	}

	if ((fd = open(FIFO_PATH, O_RDONLY)) == -1)
	{
		perror("Open for read error: ");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < LEN_ARR; i++)
	{
		ssize_t len_read = read(fd, arr + i, sizeof(int));
		if (len_read == -1)
		{
			perror("Read error: ");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < LEN_ARR; i++)
	{
		printf("Received %d\n", arr[i]);
	}
	close(fd);

	return 0;
}
