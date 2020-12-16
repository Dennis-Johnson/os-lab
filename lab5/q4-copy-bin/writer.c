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


int main(){
	int pipe_fd, res;
	int ch;

	FILE *fout;
	fout = fopen(OUTPUT_PATH, "wb");

	if(fout == NULL){
		perror("Cant open output file: ");
		exit(EXIT_FAILURE);
	}

	printf("Process %d opening FIFO to read\n", getpid());
	pipe_fd = open(FIFO_NAME, O_RDONLY);
	printf("Process %d result %d\n", getpid(), pipe_fd);

	if(pipe_fd == -1){
		perror(" ");
		exit(EXIT_FAILURE);
	}

	do {
		res = read(pipe_fd, &ch, sizeof(int));
		fputc(ch, fout);
		printf("read\n");
	} while(res > 0);

	fclose(fout);
	close(pipe_fd);
	printf("Writer Process %d is done.\n", getpid());
	
	return 0;
}
