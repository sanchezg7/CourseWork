#include <stdio.h>

int main ( void )
{
	int i;
	for (i = 0; i <= 3; i++)
	{
	
		printf("%d mod 3: %d\n", i, i%3);
	}
}
