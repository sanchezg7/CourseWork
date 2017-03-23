CC=gcc

linkFlags = -lreadline -lhistory -lncurses -lpthread

compileFlags = -Wall -c -g


compile: cube.o 
	$(CC) $(linkFlags)  cube.o wizard.o -o cube
	rm *.o
cube.o:
	$(CC) $(compileFlags) cube.c wizard.c 
clean:
	rm *.o

