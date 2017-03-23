CC=gcc

compileFlags = -Wall -c
linkFlags = -lrt

files = system_call.o context_switch.o

compile: system_call.o context_switch.o 
	$(CC) $(linkFlags) system_call.o -o system_call
	$(CC) $(linkFlags)  context_switch.o -o context_switch
	rm *.o

system_call.o: system_call.c 
	$(CC) $(compileFlags) $(linkFlags) system_call.c 
	touch samplefile.txt
	
context_switch.o: context_switch.c
	$(CC) $(compileFlags) $(linkFlags) context_switch.c 

runsc: 
	./system_call

runcs: 
	./context_switch

clean:
	rm *.o

