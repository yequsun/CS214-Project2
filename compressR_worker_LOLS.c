#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "compress.h"

void compressR(char * filename, char * new_filename, int cursor, int size){

	FILE* input = fopen(filename,"r");

	//check if output file already exists:
	/*if(access(new_filename, F_OK) != -1){
		printf("Compressed file already exists.\n");
		return;
	}
	*/

	FILE * output = fopen(new_filename, "w");

	if(output == NULL){
		printf("File error.\n");
		exit(0);
	}

	int seq_length = 1,
		i;
	char test,
		 prev,
		 curr;

	fseek(input, cursor, SEEK_SET);
	prev = '\0';

	for(i = cursor; i < size+cursor; i++){
		fseek(input, i, SEEK_SET);
		test = fgetc(input);
		
		if(isalpha(test)){
			curr = test;	
			
			if(curr == prev){
				seq_length++;
			}

			else if(prev != '\0'){
				writeLOLS(output, seq_length, prev);
				seq_length = 1;
			}

			prev = curr;
		}
	}	

	if(isalpha(prev)){
		writeLOLS(output, seq_length, prev);
	}

	fclose(output);
	fclose(input);
}


int main(int argc, char *argv[])
{
	//worker
	//argv[1] file
	//argv[2] offset
	/*int i;
	for(i=0;i<argc;i++){
		printf("%s\n",argv[i]);
	}*/

	/*
			params[0] = "./compressR_worker_LOLS";
			params[1] = filename;
			params[2] = offset_char;
			params[3] = i_char;
			params[4] = partsize_char;
			params[5] = (char*)NULL;*/


	compressR(argv[1], argv[2], atoi(argv[3]),atoi(argv[4]));




	return 0;
}