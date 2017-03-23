#include <stdio.h>

/* 
Program: [ Name ] [ File Name]

Programmer:  [Your Full Name]          Date: [DATE]
Instructor:  Alessio Gaspar	       	   Class: IT Program Design

Overview: [Type Yor Description]

*/

/* function Prototypes */

int readCoordinate( int max );  /* get user data , specificy valid end of range */
int randomCoordinate( int max ); /* get AI data , specificy valid end of range */
double evaluateShot( int shotX, int shotY, int targetX, int targetY); /* used to evaluate the shots and returns 0.0 if hit, othewise its Euclidian Distance between the two */


	
int main() {
   
	return 0;
}

/*
Function Name:   readCoordinate

Pre-conditions:  [ What the Function expects, conditions ]
            
Post-conditions: [ What The function returns or manipulates]

Logic:           [Explain what you do in here...]

Author:          [Your Name]
Date:            [Date]
                  
*/
int readCoordinate( int max )
{
	return( max );  /* You will want to change this ... */
}


/*
Function Name:   randomCoordinate

Pre-conditions:  [ What the Function expects, conditions ]
            
Post-conditions: [ What The function returns or manipulates]

Logic:           [Explain what you do in here...]

Author:          [Your Name]
Date:            [Date]
                  
*/
int randomCoordinate( int max )
{
	return( max );  /* You will want to change this ... */
}



/*
Function Name:   evaluateShot

Pre-conditions:  [ What the Function expects, conditions ]
            
Post-conditions: [ What The function returns or manipulates]

Logic:           [Explain what you do in here...]

Author:          [Your Name]
Date:            [Date]
                  
*/
double evaluateShot( int shotX, int shotY, int targetX, int targetY)
{
	return( shotX + shotY + targetX + targetY + 0.0); /* You will want to change this ... */
}
