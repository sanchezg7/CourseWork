#include <stdio.h>

int main ()
{
    int act = 10;
    int* a; //notice location of asterisk
    int *b;

    a = &act;
    b = &act;

    printf("Actual: %d\n 'a' pointer: %d\n 'b' pointer: %d\n", act, *a, *b);

return 0;
}
