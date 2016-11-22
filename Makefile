CC = gcc
CFLAGS = -g -Wall

all: compressR_LOLS compressR_worker_LOLS

compressR_LOLS: compressR_LOLS.c
	$(CC) $(CFLAGS) compressR_LOLS.c -o compressR_LOLS

compressR_worker_LOLS: compressR_worker_LOLS.c
	$(CC) $(CFLAGS) compressR_worker_LOLS.c -o compressR_worker_LOLS

clean:
	rm compressR_LOLS compressR_worker_LOLS