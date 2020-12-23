#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
/*
Demonstrate use of mmap to share memory between processes.
*/

void displayFile(char *ptr, off_t size);

int main(){
  int fd = open("input.txt", O_RDWR);
  if(fd == -1){
    perror("Open error: ");
    exit(EXIT_FAILURE);
  }

  struct stat st;
  if(fstat(fd, &st) == -1){
    perror("Fstat error: ");
    exit(EXIT_FAILURE);
  }
  
  char *ptr = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );

  pid_t pid = fork();

  if(pid == -1){
    perror("Fork error: ");
    exit(EXIT_FAILURE);
  }

  else if(pid == 0){
    printf("Child modified file in memory\n");
    for(int i = 0; i < st.st_size ; i++){
      if(isalpha(ptr[i]) && i % 2 == 0)
        ptr[i] = toupper(ptr[i]);
    }
  }
  
  else {
    sleep(2);
    printf("Parent display file after child modified in memory\n");
    displayFile(ptr, st.st_size);
  }
 
  return 0;
}

void displayFile(char *ptr, off_t size){
  for(int i = 0; i < size; i++){
    printf("%c", ptr[i]);
  }
}
