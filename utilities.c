#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compress.h"

char* create_output_filename(char * filename, int len, int i, int parts){
	//make string of length: [filename] + [_LOLS] + [max allowed digits in partlength]
	char * new_filename;
	new_filename = (char *)malloc(len + strlen("_LOLS") + 10);

	if(parts == 1){
		sprintf(new_filename, "%s_LOLS", filename);
	}
	else{
		sprintf(new_filename, "%s_LOLS%d", filename, i);
	}
	
	int j;
	for(j=strlen(new_filename)-1;j>0;j--){
		if(new_filename[j]=='.'){
			new_filename[j] = '_';
			break;
			//replace the last dot with underscore
		}
	}

	return new_filename;
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