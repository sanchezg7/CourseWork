#include <stdio.h>


/* 
As compared with the other program, "exercise3-29.c" the patterns are very different because the iterations happen differently. In this version (the altered version) only one symbol is output PER LINE. In the other example there are 10 iterations of the inside while statement before a new line is created. 
*/
int main (void)
{
	unsigned int row = 10; //initialize row
	unsigned int column; //define column

		column = 1; //set column to 1 as iteration begins

		while ( column <= 10 && row >=1) { //loop 10 times
			printf( "%s", row % 2 ? "<" : ">"); //output
			++column; //increment column
			--row; //decrement row
			puts (""); 
		} //end inner while



} //end function main
