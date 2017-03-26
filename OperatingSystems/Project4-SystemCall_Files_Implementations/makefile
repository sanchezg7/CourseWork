CC=gcc

#linkFlags = -lreadline -lhistory -lncurses -lpthread

compileFlags = -Wall -c -g


compile: objects 
	$(CC) -o myls myls.o
	$(CC) -o mysearch mysearch.o
	$(CC) -o mystat mystat.o
	$(CC) -o mytail mytail.o
	rm *.o
objects:
	$(CC) $(compileFlags) myls.c mysearch.c mystat.c mytail.c 
clean:
	rm *.o

