#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#define FREQ 3392343E3

//rdtsc - read time stamp counter
//tells how many cycles have run
//we time everything happening in the rdtsc register
//some OS save/restore this value
//__asm__ gcc extension of permitting assembly language statements
//__volatile__ ensures the asm statement is not reordered with other volatile accesses
//#seconds = #cycles/frequency
unsigned long FREQ = 3392343E3;
uint64_t rdtsc();

int main(int argc, char** argv){
	
	unsigned long first = 0;
	unsigned long sec = 0;
	unsigned long diff = 0;
	first = (unsigned long) rdtsc();
	printf("First time: %jd\n", first);
	sleep(3);
	sec = (unsigned long) rdtsc();
	printf("Second time %jd\n", sec);
	diff = sec - first;
	double time = (double)diff/FREQ;
	printf("Difference %jd\nTime: %f\n", diff, time);
	return 0;
}

uint64_t rdtsc()
{ //return cycle count

	unsigned int low, hi;
	//low order 32 bits in EAX
	//high order 32 in EDX
	__asm__ __volatile__("rdtsc" : "=a" (low), "=d" (hi));

	return ((uint64_t) hi << 32) | low;
}
