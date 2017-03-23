#include <stdio.h>

int main (void)
{
	double x;
	for (x = .000001; x <= .0001; x += .00001 ){
		printf( "%.7f\n", x);
	}
}
