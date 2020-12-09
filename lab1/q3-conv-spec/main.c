#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>

int main()
{
	printf("Hex to signed integer %d\n", 0xa);
	printf("char to signed int %d\n", 'b');
	printf("Strings %s\n", "Strings!");
	printf("Floating point (exponential) %e\n", 3.14);
	printf("Unsigned octal %o\n", 12);
	printf("Floating point %f\n", 0.1 );
  return 0;	
} 
