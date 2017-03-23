CC=gcc

linkFlags = -lrt

compileFlags = -Wall -c
linkFlags = -lrt


compile: memsim.o  
	$(CC) $(linkFlags) memsim.o -o memsim
	rm *.o
memsim.o:
	$(CC) $(compileFlags) $(linkFlags) memsim.c
clean:
	rm *.o

