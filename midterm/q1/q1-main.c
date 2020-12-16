#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>


char array[20][256];
char buffer[256];
char path[256];
int arr_index = -1;

void print_arr(){
	for(int i = 0; i <= arr_index; i++){
		printf("%s\n", array[i]);
	}
}

void sort_arr(){
	for(int i = 0; i <= arr_index - 1 ; i++){
		for(int j = 0; j<= arr_index - 1; j++){
		printf("compare %s and %s\n", array[j], array[j+1]);

			if(strcmp(array[j], array[j+1]) > 0){
				memset(buffer, '\0', sizeof(buffer));

				strcpy(buffer, array[j]);
				strcpy(array[j], array[j+1]);
				strcpy(array[j+1], buffer);
			}
		}
	}
}

void add_to_arr(char *str){
	if(str == NULL){
		printf("Error: NULL strpointer\n");
		exit(EXIT_FAILURE);
	}

	arr_index++;
	if(arr_index == 20){
		printf("Error: FULL array\n");
		exit(EXIT_FAILURE);
	}

	strcpy(array[arr_index], str);
	printf("Added %s to %s\n", str, array[arr_index]);
}

int main(){
	DIR* dp;
	struct dirent* entry;
	struct stat buf;


	if( (dp = opendir(".")) == NULL ){
		perror(" ");
		exit(EXIT_FAILURE);
	}

	while( (entry = readdir(dp)) != NULL ){
		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue; 

		lstat(entry->d_name, &buf);

		if(S_ISDIR(buf.st_mode)){
			// printf("is dir %s\n", entry->d_name);
			add_to_arr(entry->d_name);
		}
	}
	// sort_arr();
	print_arr();

	printf("\nEnter dir to remove\n");
	scanf("%s", path);


	if(rmdir(path) == 0)
		printf("Deleted dir %s\n", path);

	else printf("Not deleted\n");

	closedir(dp);
	return 0;
}