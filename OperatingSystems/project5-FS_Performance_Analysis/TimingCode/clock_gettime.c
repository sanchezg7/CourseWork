#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

void spin(int howlong);
double getTime();

int main () {
	printf("begin: %f" , getTime());
	spin(10);
	printf("end: %f", getTime());
	return 0;

}

void spin(int howlong) {
	double t = getTime();
	while((getTime() - t) < (double)howlong);
}

double getTime() {
    struct timespec t;
    int rc = clock_gettime(CLOCK_REALTIME, &t);
    assert(rc == 0);
    return (double)t.tv_sec + (double)t.tv_nsec/ 1000000000L;
}
