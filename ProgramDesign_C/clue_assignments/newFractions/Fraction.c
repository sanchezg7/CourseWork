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
   return result;
}

void fraction_to_string(Fraction R,char repr[])
{
   repr[0] = 0;
}


int compare_fractions(Fraction L, Fraction R)
{
   return 0;
}

void reduce_fraction(Fraction *R)
{

}

Fraction add_fractions(Fraction L, Fraction R)
{
   Fraction result = {0,1};
   return result;
}

