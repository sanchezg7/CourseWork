#include <iostream>
#include <string>
#include <vector>

#include "game.h"
#include "card.h"
#include "Deck.h"
#include "Blackjack.h"
#include <algorithm>
//#include "Holdem.h"
#include "Slots.h"
using namespace std;

Player::Player(int bal)
{
	string n;
	cout << "Enter a name for the player: ";
	cout << endl;
	cin >> n;

	setName(n);
	setBalance(bal);
	setBetAmountPlyr(0);
	setStand(false);
	setSurrender(false);
	setBust(false);
	pokerResult = 0;
}

Player::Player(string n)
{
	setName(n);
	setBalance(1000);
	setBetAmountPlyr(0);
	setStand(false);
	setSurrender(false);
	setBust(false);
	pokerResult = 0;

}

//fetch sum of players hand
int Player::getHandValue(bool ace)
{
	int sum = 0; //value of cards
	for(size_t i =0; i < hand.size(); ++i)
	{
		if (ace && hand[i].rank == "Ace")
			sum += 11;
		else
			sum += hand[i].bjValue;	
	}
	return sum;
}

void Player::setBetAmountPlyr(int temp)
{
	betAmount = temp;
}

void Player::setBalance(int b)
{
	balance = b;
}

int Player::getBalance() const
{
	return balance;
}

void Player::setName(string n)
{
	name = n;
}

void Player::addCard(card c)
{
	hand.push_back(c);
}

string Player::getName() const
{
	return name;
}

void Player::setStand(bool stand)
{
	this->stand = stand;
}

bool Player::getStand() const
{
	return stand;
}

void Player::setSurrender(bool surrender)
{
	this->surrender = surrender;
}

bool Player::getSurrender() const
{
	return surrender;
}

void Player::setBust(bool bust)
{
	this->bust = bust;
}

bool Player::getBust() const
{
	return bust;
}

void Player::resetHand()
{
	hand.clear(); //eliminates all cards and size is then 0;
}

int Player::getBetAmountPlyr() const
{
	return betAmount;
}

ostream &operator<<(ostream &out, Player tempPlyr) //output a player
{
	out << tempPlyr.getName() << "'s hand: " << endl;

	for(size_t i =0; i<tempPlyr.hand.size(); ++i)
	{
		out << tempPlyr.hand[i]; //print card rank and value for each in players hand
		out << endl;
	}

	return out;
}

Player::~Player()
{
	//Player class destructor
}

bool Player::getAceHighLow() const
{
	return aceHighLow;
}

void Player::setAceHighLow(bool highLow)
{
	//aces HIGH is TRUE
	//aces LOW is FALSE

	this->aceHighLow = highLow;
}
