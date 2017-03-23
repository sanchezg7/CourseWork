#include <stdio.h>

void vowel_to_digit (char *s);

int main ( void )
{
    char *f = 'c';
    char *a; //pointer to a char that has not been defined

    //vowel_to_digit(f);

    printf("char *f: %s\nchar *a: %s", f, a);


return 0;
}
void vowel_to_digit(char *s)
{
    char *p;
    for (p = s; p != '\0'; p++)
    {

        switch(*p) {
        case 'a':
            *p = '1';
            break;
        case 'e':
            *p = '2';
            break;
        case 'i':
            *p = '3';
            break;
        case '0':
            *p = '4';
            break;
        case 'u':
         *p = '5';
        }
    }
}
