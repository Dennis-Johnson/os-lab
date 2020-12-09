#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define LEN_BUFFER 256
/*
 * Similar to Lab1/Q1 grep tool
   Here we look for Packages in /var/lib/dpkg/status file
 * */
int main(){
  int in;
  char ch, buffer[LEN_BUFFER];
  
  char *path = "/var/lib/dpkg/status";
  char *key  = "Package";

  if((in = open(path, O_RDONLY)) < 0){
    fprintf(stderr, "Error opening file %s", path);
    perror(" ");
    exit(EXIT_FAILURE);
  }
  
  size_t len_read, char_count = 0;
  while((len_read = read(in, &ch, sizeof(char))) > 0){
    if (ch == '\n'){
      buffer[char_count] = '\0';
      
      if(strstr(buffer, key) != NULL)
        printf("Found '%s': line --> %s\n", key, buffer);
      
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
