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
	char* buffer = (char*) malloc(sizeof(char) * blockSize);
	assert (buffer);

	int fileDes;
	fileDes = open(fileName, O_RDONLY);	
	assert(fileDes > 2);	
	
	int i = 0;
	int j = 0;

	while( i != 100)
	{
		//printf("%d\n", i*4096);
		for(j = 0; j <5 ; ++j)
		{	
			begin = rdtscSample();
			read(fileDes, buffer, i*4096);
			end = rdtscSample();
			lseek(fileDes, 0, SEEK_SET); //start at the beginning of the file for the next read
			printf("%f\n", getTime(begin, end));
		}
		//printf("\n");
		++i;
				
	}
	return 0;
}
