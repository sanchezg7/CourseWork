#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

void spin(int howlong);
double getTime();

int main(int argc, char* argv[]){
	
	double beginTime = getTime();
	char dataRead[128]; //temporary buffer
	int fileDes; //holds file descriptor for thisFilei
	int numLoops = 1e8; //loop 100 million times
	FILE *thisFile; //file pointer
	
	thisFile = fopen("samplefile.txt", "r"); //open sample file
	assert(thisFile != NULL); //ensure file is open
	//obtain integer file descriptor for the sample file
	fileDes = fileno(thisFile); 
	
	int i = 0;
	for(i = 0; i<numLoops; ++i){
		//system call for read I/O
		read (fileDes, dataRead, 0);//read 0 bytes from the file 
	}
	
	printf("Time Elapsed: %f\n", getTime() - beginTime);
	fclose(thisFile);
	return 0;
}

double getTime(){
    struct timespec t;
    int result = clock_gettime(CLOCK_REALTIME, &t);
    assert(result == 0);
    return (double)t.tv_sec + (double)t.tv_nsec/ 1000000000L; //convert tv_nsec to seconds
}
