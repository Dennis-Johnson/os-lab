#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define LEN_BUFFER 256
int recurse(char* path, int depth);

int main(int argc, char* argv[]){
  if(argc != 2){
    fprintf(stderr, "Usage: arg1 - src of directory");
    exit(EXIT_FAILURE);
  }

  recurse(argv[1], 0);
  return 0;  
}

int recurse(char *path, int depth){
  DIR* dp;
  if((dp = opendir(path)) == NULL){
    //Invalid dir or path specified is not of a dir
    return -1;
  }
  
  struct dirent* entry;
  struct stat stat_buff;

  while((entry = readdir(dp)) != NULL){
    if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;
    
    int temp = depth * 2;
    while(temp--) printf("--");
    printf("%s\n", entry->d_name);
    
    lstat(entry->d_name, &stat_buff);
    if (S_ISDIR(stat_buff.st_mode) == 0){
      //Found a nested directory
      char new_path [LEN_BUFFER];
      strcat(new_path, path);
      strcat(new_path, "/");
      strcat(new_path, entry->d_name);
      
      recurse(new_path, depth + 1);
      memset(new_path, '\0', sizeof(new_path));
    }
  }
  
  printf("\n");
  closedir(dp);
  return 0;
}
