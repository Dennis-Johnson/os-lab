#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  
  printf("Q1 Parent process started\n");
  pid_t pid = fork();
  

  if(pid == -1){
    perror("Error creating child process ");
  }
  else if(pid == 0){

    printf("Q1 Child process started\n");
    for(int i = 0; i < 3; i++)
      printf("Q1 Child process running %d\n", i);

    exit(EXIT_SUCCESS);
  }
  else {
    int status;
    if(wait(&status) == -1)
      perror(" ");
    else 
      printf("Q1 Child is done\n");
  }
  
  printf("Q1 Parent is done\n");
  return 0;
}
