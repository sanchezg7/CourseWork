#include <stdio.h>

void reverse( const char * const sPtr); //prototype

 int main( void)
 {
    int i;
   char sentence[80]; /* create char array */

 printf( "Enter a line of text:\n");

 //use fgets to read in a line of text
 fgets(sentence, 4, stdin); //notice the sentence array which passes in an address

 printf("The for loop prints:\n");
 for ( i = 0; i < sizeof(sentence); i++)
 {
     printf("%c", sentence[i]);
 }

 printf("\nusing printf with the percent S prints: %s\n%s%c\n%s%c\n%s%s", sentence,
        "with percent c gives:", sentence,
        "Percent c with index of sentence: ", sentence [1],
        "Print string with ampersnad of array of characters: ", &sentence
        /*"Print with string tag with sentence[0]", sentence[0]*/ );


   return 0; /* indicates successful termination */
 } /* end main */
