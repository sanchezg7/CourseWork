#include "timing.h"
#include <stdio.h>
unsigned long const FREQ = 3392460e3; //Computer frequency

uint64_t rdtscSample()
{ //return cycle count
	unsigned int low, hi;
	//low order 32 bits in EAX
	//high order 32 in EDX
	__asm__ __volatile__("rdtsc" : "=a" (low), "=d" (hi));
//	printf("in RDTSC: %jd\n", ((uint64_t) hi << 32) | low);
	return ((uint64_t) hi << 32) | low;
}

double getTime(unsigned long begin, unsigned long end)
{ //return the difference in cycles as a time result
	//printf("end %jd begin %jd\n", end, begin);
	return (double)(1E6*(end - begin))/FREQ;
}
