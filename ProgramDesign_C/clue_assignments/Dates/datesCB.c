/*
Program assignment name: Dates

Author: Gerardo Sanchez
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
		int month;
		int day;
		int year;
	} date;

int compareDt(date *d1, date *d2);


int main ( void )
{
	date A, B;
	date *ptrA, *ptrB;

	ptrA = &A;
	ptrB = &B;
    int Result;

    int month, day, year;

	//prompt for user input
	printf("Enter the first date (mm/dd/yyyy)");
	scanf("%d%*c%d%*c%d", &month, &day, &year );

	//Input MON, DAY, YEAR into struct variables date
	A.month = month;
	A.day = day;
	A.year = year;

	printf("Enter the second date (mm/dd/yyyy)");
	scanf("%d%*c%d%*c%d", &month, &day, &year );

	B.month = month;
	B.day = day;
	B.year = year;


	printf("First date: %d/%d/%d\nSecond date: %d/%d/%d\n", A.month, A.day, A.year, B.month, B.day, B.year);

	//Call compare function
	Result = compareDt(ptrA, ptrB);

	printf("Result: %d\n", Result);

    switch (Result)
    {
        case -1:
            printf("%d/%d/%d is earlier than %d/%d/%d\n", A.month, A.day, A.year, B.month, B.day, B.year);
            break;
        case 0:
            printf("%d/%d/%d is the same day as %d/%d/%d\n", A.month, A.day, A.year, B.month, B.day, B.year);
            break;
        case 1:
            printf("%d/%d/%d is later than %d/%d/%d\n", A.month, A.day, A.year, B.month, B.day, B.year);
            break;
    }
return 0;
}

int compareDt(date *d1, date *d2)
{
    if(d1->year == d2->year)
	{
		if( d1->month == d2->month)
		{
			if(d1->day == d2->day)
            {
 				//printf("%d/%d/%d is the same day as %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
				return 0;
            }
			if( d1->day > d2->day)
            {
				//printf("%d/%d/%d is later than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
				return 1;
            }
			if( d2->day > d1->day)
            {
				//printf("%d/%d/%d is earlier than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
				return -1;
            }
		}
		if(d1->month > d2->month)
		{
		    //printf("%d/%d/%d is later than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
		    return 1;
        }
		if(d2->month > d1->month)
        {
            //printf("%d/%d/%d is earlier than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
            return -1;
        }
	}
	if(d1->year > d2->year)
    {
		//printf("%d/%d/%d is later than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
		return 1;
    }
	if(d2->year > d1->year)
    {
		//printf("%d/%d/%d is earlier than %d/%d/%d\n", month1, day1, year1, month2, day2, year2);
        return -1;
    }
}
