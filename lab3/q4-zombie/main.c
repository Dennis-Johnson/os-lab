#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  
  pid_t ret = fork();

  if(ret == -1){
    perror("Error creating child process ");
  }
  else if(ret == 0){
    // Child process shows as defunct by ps call in  parent process
    exit(EXIT_SUCCESS);
  }
  else {
    printf("PID of child  is %d\n", ret);
    printf("PID of parent is %d\n", getpid());

    sleep(5);
    char* args[] = {"ps", NULL};
    execl("/bin/ps", args);
    printf("Parent process done\n");
  }
  
  return 0;
}
