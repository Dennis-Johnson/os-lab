#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main(){
  DIR* dir;
  struct dirent* entry;

  if((dir = opendir(".")) == NULL){
    perror("Cant open directory\n");
    exit(EXIT_FAILURE);
  }
  
  while( (entry = readdir(dir)) != NULL ){
    int name_len = strlen(entry->d_name);

    if(strstr(entry->d_name + name_len - 2, ".c") != NULL){
      printf("Found C file: %s, enter y to grant custom perm: ", entry->d_name);
      
      int ch;
      scanf("%d", &ch);
      if(ch == 1){
        mode_t new_perm =  S_IRUSR  | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH;
        if(chmod(entry->d_name, new_perm) != -1)
          printf("Changed permissions!\n");
        else 
          perror(" ");
      }
    }
  }

  return 0;
}
