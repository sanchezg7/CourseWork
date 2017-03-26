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

//./blockSize swim.trace 64

int main(int argc, char** argv){
	
	cpu_set_t cpuSet; //library-defined structure
	CPU_ZERO(&cpuSet); //clear the current cpuSet on the process
	CPU_SET(0, &cpuSet); //force process to run on core 0
	sched_setaffinity(0, sizeof(cpu_set_t), &cpuSet); //commit the changes

	uint64_t begin = 0;
	uint64_t end = 0;
	assert(argc == 2);
	
	char* fileName = argv[1];
	unsigned long offset = 1e2; 
	int blockSize = 1024;
	char* buffer = (char*) malloc(sizeof(char) * 8+1);
	assert (buffer);
	int iterations = 0;
	int fileDes;
	fileDes = open(fileName, O_RDONLY);
		
	assert(fileDes > 2);	

	//avoid prefetching and move the file pointer "offset" bytes away
	lseek(fileDes, offset, SEEK_CUR);
	while(blockSize != 20480)
	{	
		while(iterations != 20)
		{
			lseek(fileDes, blockSize, SEEK_CUR); //change pointer to a new spot in the file "blockSize" bytes away
			begin = rdtscSample();
			read(fileDes, buffer, 8); //perform elementatry read, disk will force load from disk if the blocksize is bigger
			end = rdtscSample();
			printf("%f\n", getTime(begin, end)); //fset);
			++iterations;
		}
		blockSize +=1024;
		iterations = 0;
	}
	return 0;
}

