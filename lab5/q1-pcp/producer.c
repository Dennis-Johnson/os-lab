#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>

#define FIFO_NAME "/tmp/pcp_fifo"
#define LEN_ARRAY 4
int array[LEN_ARRAY] = {12,24,36,48};


int main(){
	int pipe_fd, res;
	int arr_index = 0;
	
	if(access(FIFO_NAME,F_OK) == -1){
		res = mkfifo(FIFO_NAME, 0777);
		if( res != 0 ){
			fprintf(stderr, "Could not create FIFO %s\n", FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	printf("Process %d opening FIFO\n", getpid());
	pipe_fd = open(FIFO_NAME, O_WRONLY);
	printf("Process %d opened FIFO with fd %d\n", getpid(), pipe_fd);

	if(pipe_fd == -1){
		perror(" ");
		exit(EXIT_FAILURE);
	}

	while(arr_index < 4){
		res = write(pipe_fd, array + arr_index, sizeof(int));
		if(res == -1){
			perror("Write error on pipe: ");
			exit(EXIT_FAILURE);
		}

		arr_index++;
	}

	close(pipe_fd);
	printf("Process %d is done.\n", getpid());
	
	return 0;
}
