#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) {
	int sfd;
	int file_counter = 1;
	int line_no = 0;
	while(file_counter != argc)
	{	
		int file_line = 0;
		sfd = open(argv[file_counter], O_RDONLY);
		if(sfd == -1) {
			printf("Couldn't open file!");
			exit(1);
		}
	
		char line[1024];
		char ch;
		int i = 0;
		
		while(read(sfd, &ch, sizeof(char)) > 0) {
			if(ch != '\n') {
				line[i++] = ch;
			}
			else {
				line[i] = '\0';
				printf("%d:\t%s\n", file_line, line);
	
				i = 0;
				line_no++;
				file_line++;
				char c;
				if(line_no % 20 == 0) {
					printf("Press any key to continue\n");
					do {
        				c = getchar();
					} while (c != '\n' && c != EOF);
				}
				memset(line, '\0', sizeof(line));
			}
		}
		close(sfd);
		file_counter++;
	}
}

