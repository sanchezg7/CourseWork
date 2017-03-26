#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>

void spin (int howlong);
double getTime();

int main(){
	
	cpu_set_t cpuSet; //library-defined structure
	CPU_ZERO(&cpuSet); //clear the current cpuSet on the process
	CPU_SET(0, &cpuSet); //force process to run on core 0
	sched_setaffinity(0, sizeof(cpu_set_t), &cpuSet); //commit the changes

	int cPid; //current process id
	int pipeFd[2]; //pipe file descriptor for reading (0) and writing (1)
	char tempBuffer[8];
	double iterations = 1e8; //loop 100 million times
	double beginTime;
	int i = 0;

	pipe(pipeFd); //declare a pipe and input the file descriptors inside integer array
	cPid = fork();
	beginTime = getTime(); //sample time moments before the context switches happen
	for(i = 0; i<iterations; ++i){
		if(cPid == 0){ //child process here

			//read empty data from the parent
			read(pipeFd[0], tempBuffer, 0);
		}else{
			//write nothing to the child process
			write(pipeFd[1], "", 0);
		}
	}
	
	if(cPid != 0){ //parent process
		//takes the difference of current time and beginning time	
		printf("Time Elapsed: %f\n", getTime() - beginTime); //reduces side-effects and overhead
		//close the pipe
		close(pipeFd[0]);
		close(pipeFd[1]);
	}
	return 0;

}

void spin(int howlong) {
	double t = getTime();
	while((getTime() - t) < (double)howlong);
}

double getTime(){
    struct timespec t;
    int rc = clock_gettime(CLOCK_REALTIME, &t);
    assert(rc == 0);
    return (double)t.tv_sec + (double)t.tv_nsec/ 1000000000L; //convert tv_nsec to nano seconds
}
