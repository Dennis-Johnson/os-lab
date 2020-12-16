#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

char buffer[256];

int main(int argc, char* argv[]){
    if(argc != 2){
      fprintf(stderr, "Usage: arg1 as path of existing dir\n");
      exit(EXIT_FAILURE);
    } 

    chdir(argv[1]);

    DIR* dp;
    struct stat f_stat;
    struct dirent* entry;

    if( (dp = opendir(argv[1])) == NULL ){
        perror(" ");
        exit(EXIT_FAILURE);
    }

    while( (entry = readdir(dp)) != NULL ){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; 

        lstat(entry->d_name, &f_stat);
        printf("Inode of file %s in dir is: %ld\n",entry->d_name, f_stat.st_ino);
    }
    
    printf("\nEnter name of a dir here\n");
    scanf("%s", buffer);


    if( (dp = opendir(buffer)) == NULL ){
        perror(" ");
        exit(EXIT_FAILURE);
    }

    lstat(buffer, &f_stat);
    dev_t dev_id = f_stat.st_dev;
    ino_t inode = f_stat.st_ino;
    mode_t protections = f_stat.st_mode;
    nlink_t nlinks = f_stat.st_nlink;
    uid_t user_id = f_stat.st_uid;
    gid_t group_id = f_stat.st_gid;
    dev_t rdev_id = f_stat.st_rdev;
    off_t size = f_stat.st_size;
    blksize_t blksize = f_stat.st_blksize;
    blkcnt_t blcnt = f_stat.st_blocks;

    printf("\n%-12s %li\n", "Device ID", dev_id);
    printf("%-12s %li\n", "Inode", inode);
    printf("%-12s %li\n", "Links", nlinks);
    printf("%-12s %i\n", "Protections", protections);
    printf("%-12s %i\n", "UserID", user_id);
    printf("%-12s %i\n", "GroupID", group_id);
    printf("%-12s %li\n", "DeviceID(s)", rdev_id);
    printf("%-12s %li\n", "Size", size);
    printf("%-12s %li\n", "BlockSize", blksize);
    printf("%-12s %li\n", "BlockCount", blcnt);


    while( (entry = readdir(dp)) != NULL ){
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue; 

        lstat(entry->d_name, &f_stat);
        printf("Inode of file %s in dir is: %ld\n",entry->d_name, f_stat.st_ino);
    }
    
    return 0;
}