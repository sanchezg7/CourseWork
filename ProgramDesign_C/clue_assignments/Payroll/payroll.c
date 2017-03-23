/* In Class Assignment 1 - Payroll */
/* Author: Gerardo Sanchez   */

#include <stdio.h>

int main(void)
{
  int id = 0, hours_worked = 0;
  int numberEmp, i; 
  double pay_rate = 0.0, wages = 0.0;
  double totWage = 0.0;

  
	scanf("%d", &numberEmp);

	for (i = numberEmp; i>=1; --i)
	{
		scanf("%d%lf%d", &id, &pay_rate, &hours_worked);
		
		//calculation for current iteration
		if (hours_worked >40) { 
			wages = (40 * pay_rate) + (hours_worked-40)*(1.5*pay_rate);
		}
		else {
			wages = (hours_worked * pay_rate);
		}
		totWage +=wages;

		printf("%d\t%.2f\n", id, wages);
	}
	
	printf("%.2f", totWage);
		

	return 0;	
}
		
