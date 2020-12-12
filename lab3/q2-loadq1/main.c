#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  
  printf("Q2 Parent process started\n");
  pid_t pid = fork();
  
  if(pid == -1){
    perror("Error creating child process ");
  }

  else if(pid == 0){
    printf("Q2 Child process started\n");

    //Child process that loads Q1 program
    char* args[] = {"main", NULL};
    int ret = execvp("../q1-blockparent/main", args);
    
    if(ret == -1){
      perror(" ");
      exit(EXIT_FAILURE);
    }
    else 
      exit(EXIT_SUCCESS);
  }
  else {
    int status;
    wait(&status);  
    printf("Q2 Child process is done\n");
  }
  
  printf("Q2 Parent is done\n");
  return 0;
}
