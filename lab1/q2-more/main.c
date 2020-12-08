#include<stdio.h>
#include<stdlib.h>

/* List the lines in the files given as arguments
 * Pause for user confimation every STEP number of lines
 * similar to the more cmd line utility
 * */

#define STEP 20
#define LEN_BUFFER 256

int main(int argc, char* argv[]){
  if(argc < 2){
    fprintf(stderr, "Usage: arg1 - file1 src, arg2 - file2 src, ... argn- filen src");
    exit(EXIT_FAILURE);
  }

  FILE *fin;
  char buffer[LEN_BUFFER];

  for(int i = 1; i < argc; i++){
    
    fin = fopen(argv[i], "r");
    if(fin == NULL){
      fprintf(stderr, "Error opening file %s", argv[i]);
      perror(" ");
      continue;
    }
    
    int line_count = 0;

    printf("%s contents:\n", argv[i]);
    while(fgets(buffer, LEN_BUFFER, fin) != NULL){
      line_count++;
      printf("%s", buffer);
      
      //Pause for user prompt to continue
      if(line_count == STEP){
        printf("\n---------------------Press Enter to continue or q to stop--------------------");
        char ch = getchar();

        if(ch == '\r')
          continue;
        else if (ch == 'q')
          break;
      }
    }
    
    printf("End of file\n");
    fclose(fin);
  }
}
