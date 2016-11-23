#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include "compress.h"

int main(int argc, char * argv[]){
	if(argc != 3){
		printf("Error: incorrect number of arguments.\nPlease enter <filename> <number of parts>\n");
		return 0;
	}

	if(atoi(argv[2]) < 1){
		printf("Error: must specify 1 or more parts.\n");
		return 0;
	}

	char * filename = argv[1];
	int parts = atoi(argv[2]);

	compressT_LOLS(filename, parts);

	return 0;
}

void compressT_LOLS(char * filename, int parts){

	//TODO: a lot of error checking needed throughout
	//TODO: there's an off by one error with how it divides up the parts

	int filesize,
		partsize,
		partsize_1st;

	if(access(filename, R_OK) != 0){
		if(errno == ENOENT){
			printf("Error: file doesn't exist.\n");
		}
		else if(errno == EACCES){
			printf("Error: permission denied.\n");
		}
		else{
			printf("File error.");
		}
		return;
	}

	FILE * input = fopen(filename, "r");

	if(input == NULL){
		printf("File error.\n");
		return;
	}

	fseek(input, 0, SEEK_END);

	filesize = ftell(input) - 1;
	partsize = filesize / parts; //split the filesize into parts
	partsize_1st = partsize + (filesize % parts);  //calculate the size of part 1

	rewind(input);
	fclose(input);

	if(parts > filesize){
		printf("Error: You asked for %d parts. There are only %d characters in the file.\n", parts, filesize);
		return;
	}

	//create an array to hold the thread id's
	pthread_t * thread_array;
	thread_array = malloc(sizeof(pthread_t) * parts);
	
	int i,
		start = 0;

	for(i = 0; i < parts; i++){

		//create a struct with info about the current section of file
		Info * t_info = malloc(sizeof(t_info));
		t_info->filename = filename;
		t_info->partno = i;
		t_info->start = start;
		t_info->parts = parts;

		if(i == 0){
			t_info->length = partsize_1st;
		}
		else{
			t_info->length = partsize;
		}

		start += t_info->length;

		pthread_create(&thread_array[i], NULL, compress, t_info);
		
	}

	for(i = 0; i < parts; i++){
		pthread_join(thread_array[i], NULL);
	}
}

//this method accepts a struct containing 1) the input filename, 2) where to start 
//scanning, and 3) how many characters to scan. It creates an output file and writes 
//a compressed version of the scanned characters to file
void * compress(void * ptr){
	Info * t_info = (Info *)ptr;

	char * filename = t_info->filename;
	int partno = t_info->partno;
	int start = t_info->start;
	int end = start + (t_info->length);
	int parts = t_info->parts;

	char * new_filename = create_output_filename(filename, strlen(filename), partno, parts);

	//check if output file already exists:
	if(access(new_filename, F_OK) != -1){
		printf("Compressed file already exists.\n");
		return NULL;
	}

	FILE * input = fopen(filename, "r");
	FILE * output = fopen(new_filename, "w");

	int seq_length = 1,
		i;
	char test,
		 prev,
		 curr;

	fseek(input, start, SEEK_SET);
	prev = '\0';

	for(i = start; i < end; i++){
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
	free(new_filename);

	return NULL;
}