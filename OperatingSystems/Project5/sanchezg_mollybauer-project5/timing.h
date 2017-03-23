
#ifndef _TIMING_H
#define _TIMING_H
#include <stdint.h>


uint64_t rdtscSample();
double getTime(unsigned long begin, unsigned long end);

#endif


