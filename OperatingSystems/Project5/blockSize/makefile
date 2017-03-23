CC=gcc
#linkFlags = -lreadline -lhistory -lncurses -lpthread
compileFlags = -Wall -c -g

compile: objects
	$(CC) -o blockSize blockSize.o timing.o
	$(CC) -o seqRead seqRead.o timing.o
	$(CC) -o fileCache fileCache.o timing.o
	$(CC) -o directPointers directPointers.o timing.o
	rm *.o	

	
objects:
	$(CC) $(compileFlags) timing.c
	$(CC) $(compileFlags) blockSize.c 
	$(CC) $(compileFlags) seqRead.c 
	$(CC) $(compileFlags) fileCache.c 
	$(CC) $(compileFlags) directPointers.c
clean:
	rm *.o
