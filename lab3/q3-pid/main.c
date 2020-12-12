#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
  
  pid_t ret = fork();
  pid_t parent_pid = getppid();
  pid_t cur_pid = getpid();

  if(ret == -1){
    perror("Error creating child process ");
  }
  else if(ret == 0){
    //Child process
    printf("Child process PID: %d and ParentPID: %d\n", cur_pid, parent_pid);
    exit(EXIT_SUCCESS);
  }
  else {
    printf("Parent process PID: %d and ParentPID: %d\n", cur_pid, parent_pid);

    int status;
    if(wait(&status) == -1)
      perror(" ");
  }
  
  return 0;
}
