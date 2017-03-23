#include <stdio.h>

//card structure definition
struct card{
	char *face; //define pointer face
	char *suit; //deinfe pointer suit
};

int main ( void )
{
	struct card aCard; //define aCard which is struct card variable
	struct card *cardPtr; //pointer to struct card

	//operations into aCard 
	aCard.face = "Ace";
	aCard.suit = "Spades";

	cardPtr = &aCard; 
	
	printf(
