#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc != 2){
      fprintf(stderr, "Usage: arg1 as src of existing file\n");
      exit(EXIT_FAILURE);
    } 

    struct stat f_stat;
    if(lstat(argv[1], &f_stat) == -1){
      perror(" ");
      exit(EXIT_FAILURE);
    } 

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
    __darwin_time_t atim = f_stat.st_atimespec.tv_sec;
    __darwin_time_t mtim = f_stat.st_mtimespec.tv_sec;
    __darwin_time_t ctim = f_stat.st_ctimespec.tv_sec;

    printf("%-12s %li\n", "Device ID", dev_id);
    printf("%-12s %li\n", "Inode", inode);
    printf("%-12s %li\n", "Links", nlinks);
    printf("%-12s %i\n", "Protections", protections);
    printf("%-12s %i\n", "UserID", user_id);
    printf("%-12s %i\n", "GroupID", group_id);
    printf("%-12s %li\n", "DeviceID(s)", rdev_id);
    printf("%-12s %li\n", "Size", size);
    printf("%-12s %li\n", "BlockSize", blksize);
    printf("%-12s %li\n", "BlockCount", blcnt);
    printf("%-12s %s\n", "Time accessed", ctime(&atim));
    printf("%-12s %s\n", "Time modified", ctime(&mtim));
    printf("%-12s %s\n", "Time changed", ctime(&ctim));
    
    return 0;
}
