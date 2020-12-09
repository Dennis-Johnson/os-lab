#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
	printf("%d \n",0xf);
	printf("%s\n","hello" );
	printf("%e\n",3.14);
	printf("%o\n",12);
	printf("%f\n",0.1 );
	printf("%#x\n",1 );
	open("hel",O_RDONLY);
	fprintf(stderr,"%m\n");
  
  return 0;	
} 
