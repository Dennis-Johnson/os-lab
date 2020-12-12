#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc != 2){
      fprintf(stderr, "Usage: arg1 as src of existing file in directory\n");
      exit(EXIT_FAILURE);
    } 

    struct stat f_stat;
    if(lstat(argv[1], &f_stat) == -1){
      perror(" ");
      exit(EXIT_FAILURE);
    } 

    ino_t inode = f_stat.st_ino;
    printf("Inode of %s is %li\n", argv[1], inode);
    
    return 0;
}
