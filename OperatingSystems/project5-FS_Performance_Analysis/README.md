# File System Measurements

Included source files:
timing.h
timing.c
blockSize.c
seqRead.c
fileCache.c
directPointers.c
makefile

Timing.c is shared among the source files and contains all the timing resources used to obtain time samples
blockSize.c - exercises the block size of the file system
seqRead.c - used to determine the amount of data prefetched by the system
fileCache.c - used to determine the size of the file cache 
directPointers.c - used to find the number of direct pointers for a file


All source code simply prints to stdout and only contain timing samples, no other information is printed
All source code runs for a fixed number of iteration for each test, the programs are not interactive
The test text file is not included (not part of the requirements), but it can be provided upon request

To compile, extract all source files (including makefile) and type 'make'
This will compile ALL the source files and link them to the timing.c source

[sanchezg@c4lab17 project5]$ make
gcc -Wall -c -g timing.c
gcc -Wall -c -g blockSize.c
gcc -Wall -c -g seqRead.c
gcc -Wall -c -g fileCache.c
gcc -Wall -c -g directPointers.c
gcc -o blockSize blockSize.o timing.o
gcc -o seqRead seqRead.o timing.o
gcc -o fileCache fileCache.o timing.o
gcc -o directPointers directPointers.o timing.o
rm *.o

****************************************************************
blockSize.c | seqRead.c | fileCache.c requires an input file, generally a text file.
Examples:

./blockSize inputfile 

./blockSize /tmp/Trace >> bsResults.txt
./seqRead /tmp/Trace >> seqResults.txt
./fileCache /tmp/Trace >> fcResults.txt

This will use /tmp/Trace as the input file and the output will be redirected to a text file
****************************************************************

directPointers.c requires the path to a NEW text file
NOTE: the file created must be deleted before running the exact command again, or it will skew the results!
Example:

./directPointers /tmp/test.txt

This will run directPointers and it will create a file in the /tmp/ directory for testing
/tmp/ is known to leverage local storage and not access network storage as a means to provide a more realistic measurement of file system performance. 