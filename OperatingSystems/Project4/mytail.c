#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#define BUFFER_SZ 60

int main( int argc, char** argv){
	int numLines = 10; //by default
	char* fileName;
	char* line;
	int index = 0;
	int fileDes; //holds file descriptor for file
	FILE* file; //file for reading
	assert(argc >= 2);
	if(strcmp("-n", argv[1]) == 0)
	{
		//set the number of lines
		numLines = atoi(argv[2]);
		//printf("Printing %d lines\n", numLines);	
		fileName = malloc(sizeof(char) * strlen(argv[3]));
		assert(fileName);
		strcpy(fileName, argv[3]);
	} else {
		fileName = malloc (sizeof(char) * strlen(argv[1]));
		strcpy(fileName, argv[1]);
	}
	
	line = malloc(sizeof(char) * numLines*BUFFER_SZ); //buffer for reading
	assert(line);
	//printf("Number of lines: %d\n", abs(numLines));
	file = fopen(fileName, "r");
	assert(file);
	fileDes = fileno(file);
	lseek(fileDes, 0 - numLines*BUFFER_SZ, SEEK_END);
	read(fileDes, line, (numLines*BUFFER_SZ - 1));
//	assert(line);
	//printf("Done reading.\n");
	index = 0;
	int newLineCount = 0;

	//count how many \n there are until EOF
	while(line[index] != EOF){
		//printf("line[%d]: %c\n", index, line[index]);
		if(line[index] == '\n') 
		{
			++newLineCount;
		}
		++index;
	}
	
	//discard n number of \n, then print
	index = 0;
	while(line[index] != EOF)
	{
		//printf("line[%d]: %c\n", index, line[index]);
		if(line[index] == '\n')
		{
			--newLineCount;
			//printf("Found new line, decrementing: %d\n", newLineCount);
			if(newLineCount == numLines -1){
				++index;
				break;
			}
		}
		++index;
	}	

	//printf("Adding requested lines in new buffer");
	char* buffer = malloc (sizeof(char) * ((numLines*BUFFER_SZ) - index));
	assert (buffer);
	int bufferIndex = 0;
	while(line[index] != EOF){
		buffer[bufferIndex] = line[index];
		++index;		
		++bufferIndex;
	}

	//printf("\n\nFinal result: ");
	puts(buffer);
	//fclose(file);
	return 0;
}
