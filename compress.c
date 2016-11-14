#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]){

	if(argc != 3){
		printf("incorrect arguments");
		return;
	}

	if(atoi(argv[2]) < 1){
		printf("Must specify 1 or more parts.");
		return;
	}

	char * filename = argv[1];
	int parts = atoi(argv[2]);
	int filesize, partsize;

	FILE *file = fopen(filename, "r");

	if(file == NULL){
		printf("File error");
		return 0;
	}

	fseek(file, 0, SEEK_END);

	filesize = ftell(file);
	partsize = filesize / parts;

	//todo: distribute the remainder

	printf("total size of file is %d\n", filesize);

	rewind(file);

	//todo: strip file extension from filename string

	int i;
	for(i = 0; i < parts; i++){
		int cursor = i * partsize;
		compress(file, "hello", i, cursor, partsize);
	}

	fclose(file);

} 

void compress(FILE * input, char * filename, int partno, int cursor, int size){

	char new_filename [100];

	snprintf(new_filename, 100, "%s_txt_LOLS%d", filename, partno);

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