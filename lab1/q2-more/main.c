#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
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

  int in;
  char buffer[LEN_BUFFER];
  
  for(int i = 1; i < argc; i++){
    
    if((in = open(argv[i], O_RDONLY)) < 0){
      fprintf(stderr, "Error opening file %s", argv[i]);
      perror(" ");
      continue;
    }
    
    int ch, char_count = 0, line_count = 0;
    size_t len_read;

    printf("%s contents:\n", argv[i]);
    while((len_read = read(in, &ch, sizeof(char))) > 0){
      putchar((char)ch)dd;
      /*
      if(ch == '\n'){
        buffer[char_count] = '\0';
        printf("%s\n", buffer);

        //memset(buffer, '\0', LEN_BUFFER);
        char_count = 0;
        line_count++;
        
        //Pause for user prompt to continue
        if(line_count == STEP){
          printf("\n---------------------Press Enter to continue or q to stop--------------------");
          char ch = getchar();

          if(ch == '\n')
            continue;
          else if (ch == 'q')
            break;
        }
      }
      else {
        buffer[char_count++] = ch;  
      }
      */
    }
    
    printf("End of file\n");
  }

  close(in);
}
