#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <sched.h>
#include <time.h>
#include "timing.h"


int main(int argc, char** argv)
{
	cpu_set_t cpuSet; //library-defined structure
	CPU_ZERO(&cpuSet); //clear the current cpuSet on the process
	CPU_SET(0, &cpuSet); //force process to run on core 0
	sched_setaffinity(0, sizeof(cpu_set_t), &cpuSet); //commit the changes

	uint64_t begin = 0;
	uint64_t end = 0;
	
	char* fileName = argv[1];
	int blockSize = 4096;
	int numBlocks = 100;
	char* buffer = (char*) malloc(sizeof(char) * numBlocks * blockSize);
	assert (buffer);

	int fileDes;
	fileDes = open(fileName, O_CREAT | O_APPEND);	
	assert(fileDes > 2);	
	int i = 0;
	for (i = 0; i < numBlocks; ++i)
	{
		buffer[i] = 'a';
	}
	//puts(buffer);
	while (numBlocks != 0)
	{	
		begin = rdtscSample();
		write(fileDes, buffer, 4096);
		fsync(fileDes); //request write back to disk
	//	spin(100); //wait to allow for information to be written back
		end = rdtscSample();
		printf("%f\n", getTime(begin, end));
		--numBlocks;
	}	
//	printf("\n");	
	return 0;
}
