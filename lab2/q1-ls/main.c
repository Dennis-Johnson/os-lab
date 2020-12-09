#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#define LEN_BUFFER 256
/*
 Program to emulate behaviour of ls -l command 
*/

long int displayFile(struct dirent* entry, struct stat stat_buff);
void formatID(const mode_t permissions, char *buffer);

int main(){
  char cwd[LEN_BUFFER];

  getcwd(cwd, sizeof(cwd));
  printf("CWD: %s\n\n", cwd);

  DIR* dp;
  struct dirent* entry;

  if((dp = opendir(cwd)) == NULL){
    fprintf(stderr, "Could not open directory %s", cwd);
    perror(" ");
    exit(EXIT_FAILURE);
  }
  
  struct stat stat_buff;
  long int totalSize = 0;

  while((entry = readdir(dp)) != NULL){
    //Skip printing info of . and .. dirs
    if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;
    
    lstat(entry->d_name, &stat_buff);
    totalSize += displayFile(entry, stat_buff);    
  }
  
  closedir(dp);
  printf("Total size: %li\n", totalSize);
  return 0;
}

long int displayFile(struct dirent* entry, struct stat stat_buff){
  mode_t permissions = stat_buff.st_mode;
  nlink_t numLinks = stat_buff.st_nlink;
  uid_t userID = stat_buff.st_uid;
  gid_t groupID = stat_buff.st_gid;
  off_t size = stat_buff.st_size;
  
  char username[LEN_BUFFER], groupname[LEN_BUFFER], perm_formatted[32];
  memset(username, '\0', sizeof(username));
  memset(groupname, '\0', sizeof(groupname));

  struct passwd* uid = getpwuid(userID); 
  struct group* gid = getgrgid(groupID);
  
  strcpy(username, uid->pw_name);
  strcpy(groupname, gid->gr_name);
  formatID(permissions, perm_formatted);
  
  printf("%s %3lu %s %s %4li %10s\n", perm_formatted, numLinks, username, groupname, size, entry->d_name);

  return size;
}

#define sc(ch) strcat(buffer,(ch))
void formatID(const mode_t permissions, char *buffer){
  memset(buffer, '\0', 32 * sizeof(char));
  if(permissions & S_IRUSR) sc("r"); else sc("-");
  if(permissions & S_IWUSR) sc("w"); else sc("-");
  if(permissions & S_IXUSR) sc("x"); else sc("-");
  if(permissions & S_IRGRP) sc("r"); else sc("-");
  if(permissions & S_IWGRP) sc("w"); else sc("-");
  if(permissions & S_IXGRP) sc("x"); else sc("-");
  if(permissions & S_IROTH) sc("r"); else sc("-");
  if(permissions & S_IWOTH) sc("w"); else sc("-");
  if(permissions & S_IXOTH) sc("x"); else sc("-");
}

