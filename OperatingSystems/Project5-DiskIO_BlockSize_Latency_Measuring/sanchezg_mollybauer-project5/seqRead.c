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
	//blocksize is 4KB
	//take sample at the beginning before reading the file
	//read blockSizeBYTES from the file repeatedly for the 
	//time each read and plot the time per read
	//run 100 times, move the pointer before each read
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
//	sleep(1);

	int i = 0;

	while( i != 1000)
	{
		//offset to a new "block" of the file
		lseek(fileDes, blockSize*i, SEEK_CUR); 
		begin = rdtscSample();
		//locatlity principle
		read(fileDes, buffer, 256); //read some data 
		spin(100); //spin 10 MILLISECOND
		end = rdtscSample();
		++i;
		printf("%f\n", getTime(begin, end)-100);	
	}
	return 0;
}
