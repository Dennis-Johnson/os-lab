#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
/*
 * Program to copy char by char from src to dst file
 * */

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "Usage: arg1 -- file1 src, arg2 -- file2 src");
    exit(EXIT_FAILURE);
  }

  int ch, in, out;

  if ((in = open(argv[1], O_RDONLY)) < 0)
  {
    fprintf(stderr, "Error opening src file %s", argv[1]);
    perror(" ");
    exit(EXIT_FAILURE);
  }

  if ((out = open(argv[2], O_WRONLY | O_CREAT, S_IWUSR | S_IXOTH)) < 0)
  {
    fprintf(stderr, "Error opening dst file %s", argv[2]);
    perror(" ");
    exit(EXIT_FAILURE);
  }

  size_t len_read, len_write;
  while ((len_read = read(in, &ch, 1)) > 0)
  {
    if ((len_write = write(out, &ch, 1)) < 0)
    {
      fprintf(stderr, "Error writing to dst file");
      perror(" ");
    }
  }

  printf("Done copying!\n");
  return 0;
}
