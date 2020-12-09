#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
    else printf("\n'%s' contents:\n", argv[i]);
    
    char ch;
    int line_count = 0;
    size_t len_read, char_count = 0;

    
    while((len_read = read(in, &ch, sizeof(char))) > 0){
      if(ch == '\n'){
        buffer[char_count] = '\0';
        printf("%d  %s\n", line_count, buffer);

        char_count = 0;
        line_count++;
        
        //Pause for user prompt to continue
        if(line_count % STEP == 0){
          printf("\n---------------------Press Enter to continue or q to stop--------------------");
          char ch = getchar();

          if(ch == '\r')
            continue;
          else if (ch == 'q')
            break;
        }
        memset(buffer, '\0', sizeof(buffer));
      }
      else {
        buffer[char_count++] = ch;  
      }
    } 

    line_count = 0;
    char_count = 0;
    close(in);
    printf("End of file\n");
  }

}
