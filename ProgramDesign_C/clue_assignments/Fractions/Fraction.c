#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "Fraction.h"

int gcd(int a, int b)
{
   if (a == 0 && b == 0) {
      printf("Illegal args to gcd: %d, %d\n",a,b);
      exit(1);
   }
   int aa = abs(a);
   int bb = abs(b);
   if (aa == 0)
      return bb;
   if (bb == 0)
      return aa;
   return gcd(bb,aa%bb);
}

Fraction string_to_fraction(const char *S)
{
	Fraction result = {0,1};
	/* Place your code here to initialize the Fraction result
	as specified in the string S (using sscanf)
	*/

	sscanf(S, "%d%/%d", &result.numer, &result.denom);

	if (result.denom == 0)
	{
		printf("Invalid fraction: denominator is 0");
		exit(2);
	}

	return result;
}

void fraction_to_string(Fraction R,char repr[])
{
	repr[0] = 0;
	/* Place your code here to place the string representation
	of the Fraction R in the character array repr using
	sprintf.
	*/
	//Equivalent to printf, except the output is stored in the
	//array s instead of printed on the screen. Returns the number of characters written to s, or EOFif an error occurs.
	sprintf(repr, "%d/%d", R.numer, R.denom);
}


int compare_fractions(Fraction L, Fraction R)
{
	/* Place your code here to return 1 if L and R
	have the same value as Fractions, 0 if not
	*/

	reduce_fraction (&L);
	reduce_fraction (&R);

	int tempGcd = gcd( L.denom, R.denom);

	L.numer *= tempGcd;
	L.denom *= tempGcd;

	R.numer *= tempGcd;
	R.denom *= tempGcd;

	if((L.numer) - (R.numer) == 0)
	{
		return 1;
	}
	else{
		return 0;
	}
}

void reduce_fraction(Fraction *R)
{
	/* Place your code here to modify the Fraction being passed
	in by reference so that it is reduced according to the
	specifications in Instructions.pdf
	*/
	int tempGcd = gcd(R->numer, R->denom);
	//divide by gcd
	R->numer /= tempGcd;
	R->denom /= tempGcd;

	//if denom is negative move to numer
	if ((R->denom) < 0)
	{
		//adjust the sign convention
		(R->numer) *= -1;
		(R->denom) *= -1;
	}
}

Fraction add_fractions(Fraction L, Fraction R)
{
	Fraction result = {0,1};
	/* Place your code here to make result a reduced
	Fraction representing the sum of the Fractions L and R
	*/
	reduce_fraction (&L);
	reduce_fraction (&R);

	int tempGcd = gcd((L.denom), (R.denom));

	L.numer *= tempGcd;
	L.denom *= tempGcd;

	R.numer *= tempGcd;
	R.denom *= tempGcd;

	result.numer += ((L.numer)+(R.numer));
	result.denom += L.denom;

	reduce_fraction (&result);
	return result;
}


