/* Change project                     */
/* Program creator: Gerardo Sanchez     */
/* Date:                              */

#include <stdio.h>

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones);

int main( void)
{
	int dollars, twent, ten, five, one;
	printf("Enter a dollar amount:");
	scanf("%d", &dollars);
	
	pay_amount(dollars, &twent, &ten, &five, &one);
	
	printf("$20 bills: %d\n$10 bills: %d\n$5 bills: %d\n$1 bills: %d\n", twent, ten, five, one);
	

return 0;	
}

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *ones)
{

	*twenties = (dollars)/20;
	*tens = (dollars - (20 * *twenties))/10;
	*fives = (dollars - (20 * *twenties) - (10 * *tens))/5;
	*ones = (dollars - (20 * *twenties) - (10 * *tens) - (5 * *fives))/1;

}
