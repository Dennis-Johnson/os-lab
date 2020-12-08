#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
  if(argc != 3){
    fprintf(stderr, "Usage: arg1 -- file1 src, arg2 -- file2 src");
    exit(EXIT_FAILURE);
  }

  FILE *fin, *fout;
  if ((fin = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "Error opening src file %s", argv[1]);
    perror(" ");
    exit(EXIT_FAILURE);
  }
  
  if ((fout = fopen(argv[2], "w")) == NULL){
    fprintf(stderr, "Error opening dst file %s", argv[2]);
    perror(" ");
    exit(EXIT_FAILURE);
  }
  
  int ch;
  while((ch = fgetc(fin)) != EOF){
    fputc(ch, fout);
  }

  printf("Done copying!\n");
  return 0;
}
