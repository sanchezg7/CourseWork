#include "Deck.h"

Deck::Deck () //constructor will push vector current deck and assign 52 cards
{
	//set the face
	for (int i = 0; i < 4; ++i)
	{
		//set the value
		for (int j = 0; j < 13; ++j)
		{
			currentDeck.push_back(card(j, i)); //pass in value then suit respectively
		}
	}

}

card Deck::Deal() //returns a card and then removes it from the index
{	
	srand((unsigned) time(NULL));

	int index = (rand() % currentDeck.size());
	card temp = currentDeck[index];

	currentDeck.erase(currentDeck.begin() + index);

	return temp;
}
