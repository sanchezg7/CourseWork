#include <stdio.h>
int main(void)
{
	int month1, month2, day1, day2, year1, year2;

	printf("Enter first date (mm/dd/yyyy): ");
	scanf("%d%*c%d%*c%d", &month1, &day1, &year1);
	printf("Enter second date (mm/dd/yyyy): ");
	scanf("%d%*c%d%*c%d", &month2, &day2, &year2);

	if(year1 == year2)
	{
		if(month1 == month2)
		{
			if(day1 == day2)
				printf("%d/%d/%d is the same day as %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
			if(day1 > day2)
				printf("%d/%d/%d is later than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
			if(day2 > day1)
				printf("%d/%d/%d is earlier than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
		}
		if(month1 > month2)
			printf("%d/%d/%d is later than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
		if(month2 > month1)
			printf("%d/%d/%d is earlier than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
	}
	if(year1 > year2)
		printf("%d/%d/%d is later than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
	if(year2 > year1)
		printf("%d/%d/%d is earlier than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
return 0;
}
