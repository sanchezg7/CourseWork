#include <stdio.h>

struct test
{
   int *p;
   char *c;
   
};

typedef struct test turkey;

int main()
{
   turkey chicken;
   
   turkey chicken.p = 10;
   turkey chicken.c = 'p';
   
   printf("%d\n", chicken.p);
   printf("%c", chicken.c);
}
