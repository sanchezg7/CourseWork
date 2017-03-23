/* Project: X11_Container                */
/* Programmer: <Gerardo Sanchez> */

#include <stdio.h>

#define PI 3.141593 

int main (void)
{
	int length, radius;
	double volCylinder, volSphere, surCyl, surSphere;
	double totVol, totSurface;
	
	
	//user input
	printf("Enter the length of the tank (feet)");
	scanf("%d", &length);

	printf("%s", "Enter the radius of the tank (feet)");
	scanf("%d", &radius);


	//input validation
	while (!((10<=length && length<=20) && (3<=radius && radius<=6)))
	{
		printf("Retry: Enter the length of the tank (feet)");
		scanf("%d", &length);
		
		printf("Enter the radius of the tank (feet)");
		scanf("%d", &radius);
	}

	//Making calculations
	volCylinder = (PI)*(radius*radius*length);
	volSphere = (4.0/3.0)*(PI)*(radius*radius*radius);
	surCyl = 2*(PI)*(radius*length);
	surSphere = 4*(PI)*(radius*radius);
	
	totVol = (volCylinder - volSphere);
	totSurface = (surCyl + surSphere);
	
	printf("A cylindrical tank of length %d and radius %d with inverted spherical caps has\n", length, radius);
	printf("volume: %.3f\nsurface area: %.3f\n", totVol, totSurface);

	
	
	
return (0);
}

