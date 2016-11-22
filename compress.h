#ifndef COMPRESS_H_
#define COMPRESS_H_

typedef struct {
	char * filename;
	int partno;
	int start;
	int length;
	int parts;
} Info;

void compressT_LOLS(char *, int);
void compressR_LOLS(char *, int);
void * compress(void *);
void writeLOLS(FILE *, int, char);
char * create_output_filename(char *, int, int, int);
#endif