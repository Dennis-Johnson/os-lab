#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LEN_BUFFER 128

int main(int argc, char* argv[]){
  FILE *fin;
  char buffer[LEN_BUFFER];

  if(argc != 3){
    fprintf(stderr, "Usage: arg1 - word, arg2 - file src to search in");  
  }
  
  fin = fopen(argv[2], "r");
  if(fin == NULL){
    fprintf(stderr, "Error opening file %s", argv[2]);
    perror(" ");
  }
  
  while(fgets(buffer, LEN_BUFFER, fin) != NULL){
    if(strstr(buffer, argv[1]) == NULL)
      continue;
    
    printf("Found '%s': line --> %s", argv[1], buffer);
  }

  fclose(fin);
	return 0;
}
