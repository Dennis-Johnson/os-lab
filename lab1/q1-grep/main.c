#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stats.h>
#include<fctnl.h>
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
  
  size_t len_read;
  while((len_read = read(in, &ch, sizeof(char))) > 0){
    if (ch == '\n'){
      //Do stuff
    }
    buffer[char_count++] = ch;
    if(strstr(buffer, argv[1]) == NULL)
      continue;
    
    printf("Found '%s': line --> %s", argv[1], buffer);
  }

  fclose(fin);
	return 0;
}
