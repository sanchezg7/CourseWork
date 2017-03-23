/* recursive program to compute the gcd of two positive integers*/
#include <stdio.h>

int rgcd(int m, int n); //prototype

int main (void)
{

	int a = 78;
	int b = 42;
	
	printf("%d\n", rgcd(a,b));
		
	return 0;
}

int rgcd( int m, int n)
{
	if (n == 0)
	{
	  return m;
	}
	return rgcd(n, m%n);
}
