#include <stdio.h>

int main (void)
{
	unsigned int count = 1; //initialize row

	while (count <=10) { //loop ten times

		//output line of text
		puts(count % 2 ? "***" : "++++++++");
		++count; //increment count
	} //end while

} //end function main
