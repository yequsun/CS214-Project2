CC = gcc
CFLAGS = -g -Wall

all: compressR_LOLS compressR_worker_LOLS compressT_LOLS

compressR_LOLS: compressR_LOLS.c utilities.c compress.h
	$(CC) $(CFLAGS) compressR_LOLS.c utilities.c -o compressR_LOLS

compressR_worker_LOLS: compressR_worker_LOLS.c utilities.c compress.h
	$(CC) $(CFLAGS) compressR_worker_LOLS.c utilities.c -o compressR_worker_LOLS

compressT_LOLS: compressT_LOLS.c utilities.c compress.h
	$(CC) $(CFLAGS) compressT_LOLS.c utilities.c -o compressT_LOLS -pthread

clean:
	rm compressR_LOLS compressT_LOLS compressR_worker_LOLS
