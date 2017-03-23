#include "card.h"
#include <iostream>
#include <string>
#include <array>
using namespace std;

card::card(int value, int suit)
{
	resetCard(value, suit);
}

void card::resetCard(const int value, const int suit)
{
	setSuit(suit);
	setBjValue(value);
	setThValue(value);
}

void card::setSuit(const int suit)
{
	//feeds in number of suit and assigns card object to that suit
	//1 is hearts, 2 is diamonds, 3 is clubs, 4 is spades
	switch (suit + 1)
	{
	
	case 1:
		this->suit = "HEARTS"; //use this* pointer requires arrow notation
		break;
	case 2:
		this->suit = "DIAMONDS"; 
		break;
	case 3:
		this->suit = "CLUBS";
		break;
	case 4:
		this->suit = "SPADES";
		break;
	default:
		break;
	}
}

void card::setRank(const int rank)
{
	//feeds in number of suit and assigns card object to that suit
	//1 is hearts, 2 is diamonds, 3 is clubs, 4 is spades
	switch (rank)
	{
	case 2:
		this->rank = "Two"; //use this* pointer requires arrow notation
		break;
	case 3:
		this->rank = "Three"; 
		break;
	case 4:
		this->rank = "Four"; 
		break;
	case 5:
		this->rank = "Five"; 
		break;
	case 6:
		this->rank = "Six"; 
		break;
	case 7:
		this->rank = "Seven"; 
		break;
	case 8:
		this->rank = "Eight"; 
		break;
	case 9:
		this->rank = "Nine"; 
		break;
	case 10:
		this->rank = "Ten";
		break;
	case 11:
		this->rank = "Jack";
		break;
	case 12:
		this->rank = "Queen";
		break;
	case 13:
		this->rank = "King";
		break;
	case 14:
		this->rank = "Ace";
		break;

	default:
		break;
	}
}

void card::setBjValue(const int val)
{
	//feeds in number of suit and assigns card object to that suit
	//1 is hearts, 2 is diamonds, 3 is clubs, 4 is spades
	switch (val + 2)
	{

	case 2:
		this->bjValue = 2; //use this* pointer requires arrow notation
		break;
	case 3:
		this->bjValue = 3; //use this* pointer requires arrow notation
		break;
	case 4:
		this->bjValue = 4; //use this* pointer requires arrow notation
		break;
	case 5:
		this->bjValue = 5; //use this* pointer requires arrow notation
		break;
	case 6:
		this->bjValue = 6; //use this* pointer requires arrow notation
		break;
	case 7:
		this->bjValue = 7; //use this* pointer requires arrow notation
		break;
	case 8:
		this->bjValue = 8; //use this* pointer requires arrow notation
		break;
	case 9:
		this->bjValue = 9; //use this* pointer requires arrow notation
		break;
	case 10:
	case 11:
	case 12:
	case 13:
		this->bjValue = 10;
		break;
	case 14:
		this->bjValue = 1;
		break;

	default:
		break;
	}
	setRank(val + 2);
}

void card::setThValue(const int val)
{
	//feeds in number of suit and assigns card object to that suit
	//1 is hearts, 2 is diamonds, 3 is clubs, 4 is spades
	switch (val + 2)
	{

	case 2:
		this->thValue = 2; //use this* pointer requires arrow notation
		break;
	case 3:
		this->thValue = 3; //use this* pointer requires arrow notation
		break;
	case 4:
		this->thValue = 4; //use this* pointer requires arrow notation
		break;
	case 5:
		this->thValue = 5; //use this* pointer requires arrow notation
		break;
	case 6:
		this->thValue = 6; //use this* pointer requires arrow notation
		break;
	case 7:
		this->thValue = 7; //use this* pointer requires arrow notation
		break;
	case 8:
		this->thValue = 8; //use this* pointer requires arrow notation
		break;
	case 9:
		this->thValue = 9; //use this* pointer requires arrow notation
		break;
	case 10:
		this->thValue = 10; //use this* pointer requires arrow notation
		break;
	case 11:
		this->thValue = 11; //use this* pointer requires arrow notation
		break;
	case 12:
		this->thValue = 12; //use this* pointer requires arrow notation
		break;
	case 13:
		this->thValue = 13; //use this* pointer requires arrow notation
		break;
	case 14:
		this->thValue = 14; //use this* pointer requires arrow notation
		break;

	default:
		break;
	}
	setRank(val + 2);
}


string card::getSuit() const
{
	return this->suit;
}

string card::getRank() const
{
	return this->rank;
}

int card::getBjValue() const
{
	return this->bjValue;
}

int card::getThValue() const
{
	return this->thValue;
}

//declaring the arrays here, they are static and for future use in dealing cards
const string card::suits[4] = { "HEARTS", "DIAMONDS", "CLUBS", "SPADES" };
const string facecards[4] = { "JACK", "QUEEN", "KING", "ACE" };

//operator overload for card Rank of Suit
ostream &operator<<(ostream &out, const card &tempCard)
{

		out << tempCard.getRank() << " of " //returns facecard
			<< tempCard.getSuit();
	return out;
}

bool card::operator<(card& c)
{
	if (thValue < c.thValue)
		return true;
	return false;
}