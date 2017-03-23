#include <iostream> 
#include <vector> 
#include <ctime> 
#include "DeckOfCards.h" 
#include "Card.h" 
using namespace std;

vector< Card > deck;

DeckOfCards::DeckOfCards()
{
	currentCard = -1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			Card sinCard(j, i);
			deck.push_back(sinCard);
			currentCard++;
		}
	}
}

DeckOfCards::~DeckOfCards()
{
	deck.clear();
}

void DeckOfCards::shuffle()
{
	int index;
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 52; i++)
	{
		index = rand() % 52;
		Card temp = deck[index];
		deck[index] = deck[i];
		deck[i] = temp;
	}
}

Card DeckOfCards::dealCard()
{
	Card next = deck[currentCard];
	currentCard--;
	return next;
}

bool DeckOfCards::moreCards()
{
	if (currentCard == -1)
	{
		return false;
	}
	else
	{
		return true;
	}

}

void DeckOfCards::reset()
{
	deck.clear();
	currentCard = -1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			Card sinCard(j, i);
			deck.push_back(sinCard);
			currentCard++;
		}
	}
}