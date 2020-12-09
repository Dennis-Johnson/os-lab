#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define LEN_BUFFER 256
/*
 * Search for a word in file given as cmd line ard
 * Similar to grep for a single file
 * */

int main(int argc, char* argv[]){
  int in;
  char ch, buffer[LEN_BUFFER];

  if(argc != 3){
    fprintf(stderr, "Usage: arg1 - word, arg2 - file src to search in");  
  }
  
  if((in = open(argv[2], O_RDONLY)) < 0){
    fprintf(stderr, "Error opening file %s", argv[2]);
    perror(" ");
    exit(EXIT_FAILURE);
  }
  
  size_t len_read, char_count = 0;
  while((len_read = read(in, &ch, sizeof(char))) > 0){
    if (ch == '\n'){
      buffer[char_count] = '\0';
      
      if(strstr(buffer, argv[1]) != NULL)
        printf("Found '%s': line --> %s", argv[1], buffer);
      
      char_count = 0;
      memset(buffer, '\0', sizeof(buffer));
    } 

    else {
      buffer[char_count++] = ch;
    }
  }

  close(in);
	return 0;
}
