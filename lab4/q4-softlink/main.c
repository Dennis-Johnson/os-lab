#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc != 3){
      fprintf(stderr, "Usage: arg1 as src file, arg2 as new path\n");
      exit(EXIT_FAILURE);
    } 

    if(symlink(argv[1], argv[2]) == -1){
      perror("Error linking ");
      exit(EXIT_FAILURE);
    }
    else 
      printf("Symbolic link @ %s created!\n", argv[2]);
    
    if(unlink(argv[1]) == -1){
      perror("Error unlinking ");
      exit(EXIT_FAILURE);
    }
    else 
      printf("Link @ %s deleted!\n", argv[1]);

    return 0;
}
