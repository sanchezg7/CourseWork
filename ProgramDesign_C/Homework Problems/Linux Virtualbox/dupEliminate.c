#include <stdio.h>

int main(void)
{
	int a[20] = {0};
	int i, j;
	int currentInt;

	//as number is read, print it only if it's not a duplicate of a unumber already read
	//read, loop array for duplicate of that value, enter if not duplicate	
	for ( i = 0; i < 20; i++)
	{
		scanf("%d", &currentInt);
		
		for ( j = 0; j < 20; j++)
		{
			if ( currentInt == a[j]) //currentInt is a duplicate, do nothing and break out of for loop
			   {
				printf("%d is a duplicate at a[%d], not stored.", currentInt, j);
			   	break;
				//printf("current int %d assigned to array index %d, value of a[j]", currentInt, j, a[j]);
			   }
			else {
				
				if ( a[j] == 0) //not a duplicate, store value and break out of for loop. 
				{
					a[j] = currentInt;
					printf("Value: %d stored in a[%d]", currentInt, j);
					break;
				}
			}
		}
	}
return 0;
}
