#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

#define LEN_BUFFER 256
/*
 Program to list all installed Applications
*/

void displayFile(struct dirent* entry, struct stat stat_buff);

int main(){
  //Path to Apps folder, here I'm using OS X
  char* path = "/Applications";
  int appCount = 0;
  DIR* dp;
  struct dirent* entry;

  if((dp = opendir(path)) == NULL){
    fprintf(stderr, "Could not open directory %s", path);
    perror(" ");
    exit(EXIT_FAILURE);
  }
 
  while((entry = readdir(dp)) != NULL){
    appCount ++;
    //Skip printing info of . and .. dirs
    if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    // Print Application names
    printf("Application #%d --> %s\n", appCount, entry->d_name);
  }

  closedir(dp);
  return 0;
}

