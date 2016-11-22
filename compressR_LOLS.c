#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
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
	int filesize, partsize, partsize_first;

	FILE *file = fopen(filename, "r");

	if(file == NULL){
		printf("File error");
		return 0;
	}

	fseek(file, 0, SEEK_END);

	filesize = ftell(file);
	partsize = filesize / parts;
	partsize_first = partsize + filesize%parts;

	rewind(file);

	if(filesize<parts){
		printf("Too many parts\n");
		return;
	}

	pid_t pid = 1;
	int i;

	for(i=0;i<parts;++i){
		if((pid = fork()) <0){
			printf("Fork failed\n");
			abort();
		}else if(pid == 0){
			//do child work
		}
	}

	int j = parts;

	while(j > 0){
		wait(NULL);
		printf("child complete\n");
		--j;
	}

	printf("complete\n");
	


	return 0;
}