#ifndef COMPRESS_H_
#define COMPRESS_H_

typedef struct {
	char * filename;
	int partno;
	int start;
	int length;
} Info;

void compressT_LOLS(char *, int);
void * compress(void *);
void writeLOLS(FILE *, int, char);
char * create_output_filename(char *, int, int);
#endif



//load file
//read length
//interger division by number of parts to find part size
//modulo to find length of first part
//create first thread with filename, output filename, start pos, number of chars
//loop to create the rest of the threads
//wait for threads
//--open input file
//--open output file
//--fseek to start pos
//--loop to scan chars
//----if chars change, call writeLOLS
//--call writeLOLS once more at the end
//--close files
//--return thread
//close input file