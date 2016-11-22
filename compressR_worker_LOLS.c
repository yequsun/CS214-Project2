#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* create_output_filename(char * filename, int len, int i){

	//make string of length: [filename] + [_LOLS] + [max allowed digits in partlength]
	char * new_filename;
	new_filename = (char *)malloc(len + strlen("_LOLS") + 2);

	int dot_pos = len - 4;

	sprintf(new_filename, "%s_LOLS%d", filename, i);
	new_filename[dot_pos] = '_';

	return new_filename;
}

void compress(char * filename, int partno, int cursor, int size){

	char * new_filename = create_output_filename(filename, strlen(filename), partno);

	FILE* input = fopen(filename,"r");

	FILE * output = fopen(new_filename, "w");

	if(output == NULL){
		printf("File error");
		exit(0);
	}

	int seq_length = 1,
		i;
	char prev,
		 curr;

	fseek(input, cursor, SEEK_SET);
	prev = fgetc(input);

	for(i = cursor + 1; i < size+cursor; i++){
		fseek(input, i, SEEK_SET);
		curr = fgetc(input);

		if(curr == prev){
			seq_length++;
		}

		else{
			writeLOLS(output, seq_length, prev);
			seq_length = 1;
		}

		prev = curr;
	}	

	writeLOLS(output, seq_length, prev);

	fclose(output);
}

void writeLOLS(FILE * output, int seq_length, char prev){
	if(seq_length > 2){
		fprintf(output, "%d%c", seq_length, prev);
	}
	else if(seq_length == 2){
		fprintf(output, "%c%c", prev, prev);
	}
	else if(seq_length == 1){
		fprintf(output, "%c", prev);
	}

}



int main(int argc, char const *argv[])
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


	compress(argv[1],atoi(argv[3]),atoi(argv[2]),atoi(argv[4]));




	return 0;
}