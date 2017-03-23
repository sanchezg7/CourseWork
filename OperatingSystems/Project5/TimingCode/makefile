CC=gcc
#linkFlags = -lreadline -lhistory -lncurses -lpthread
compileFlags = -Wall -c -g

compile: objects 
	$(CC) -o rdtsc rdtsc.o
	rm *.o	
objects:
	$(CC) $(compileFlags) rdtsc.c 
clean:
	rm *.o
