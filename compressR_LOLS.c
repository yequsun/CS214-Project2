#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "compress.h"

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("incorrect arguments\n");
		return 0;
	}

	if(atoi(argv[2]) < 1){
		printf("Must specify 1 or more parts.\n");
		return 0;
	}

	char * filename = argv[1];
	int parts = atoi(argv[2]);

	compressR_LOLS(filename, parts);

	return 0;
}

void compressR_LOLS(char * filename, int parts){

	int filesize, partsize, partsize_first;

	FILE *file = fopen(filename, "r");

	if(file == NULL){
		printf("File error.\n");
		return;
	}

	fseek(file, 0, SEEK_END);

	filesize = ftell(file);
	partsize = filesize / parts;
	partsize_first = partsize + filesize%parts;

	rewind(file);

	if(filesize<parts){
		printf("Too many parts.\n");
		return;
	}

	pid_t pid = 1;
	int i;

	for(i=0; i<parts; ++i){
		if((pid = fork()) <0){
			printf("Fork failed\n");
			abort();
		}else if(pid == 0){
			//do child work
			int offset;
			//calculate offset, the start point for this process in the file
			if(i==0){
				offset = 0;
			}else{
				offset = partsize_first + (i-1)*partsize;
			}
			char offset_char[10];
			sprintf(offset_char, "%d", offset);
			//printf("%s\n", offset_char);

			char i_char[10];
			sprintf(i_char, "%d", i);

			char partsize_char[10];
			if(i==0){
				sprintf(partsize_char, "%d", partsize_first);
			}else{
				sprintf(partsize_char, "%d", partsize);
			}

			char* params[6];
			params[0] = "./compressR_worker_LOLS";
			params[1] = filename;
			params[2] = offset_char;
			params[3] = i_char;
			params[4] = partsize_char;
			params[5] = (char*)NULL;

			execv(params[0],params);
		}
	}

	int j = parts;

	while(j > 0){
		wait(NULL);
		printf("child complete\n");
		--j;
	}

	printf("complete\n");

	return;
}