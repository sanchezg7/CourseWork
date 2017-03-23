/*The switch statement can take in a aritmetic and match it to that for example it is able to do division and multiplication as well as addition to the variable. Take a look at the switch statement below*/

#include <stdio.h>

int main (void)
{
	int a = 10;
	
	switch (a/2) {
	
		case 10:
		    printf("%d\n", a);
		    break;
		case 5:
		    printf("5\n");
		    break;
	}

	printf("this is a-1: %d\t This is a-2: %d\t", a-1, a-2);
	printf("\nThis is a:%d", a);
return 0;
}
