#include "BlackJackPlayer.h" 
#include <vector> 
#include <iostream> 
#include <string> 
using namespace std;


BlackJackPlayer::BlackJackPlayer(int bal, int iden, int bt, int S) : Player(bal)
{
	setId(iden); //sets id 
	setBet(bt); // sets the bet 
	st = S; // sets the value for stand 
}


void BlackJackPlayer::setId(int a)
{
	id = a; //sets id to the value passed in 
}

int BlackJackPlayer::getId() const
{
	return id; //returns id 
}

void BlackJackPlayer::displayPlayerId() const // display player ID 
{
	Player::displayPlayerId();
	cout << id << endl;
}

void BlackJackPlayer::displayPlayerHand()  // display player's hand 
{
	for (size_t i = 0; i < hand.size(); ++i)
	{
		cout << hand[i].toString() << endl; // converts the card to string and displays it 
	}
	if (total() > 21)
	{
		cout << "total: " << total() << "   BUST" << endl;
		setStand();
	}
	else
		cout << "total: " << total() << endl;

	cout << endl; // extra spacing 
}

void BlackJackPlayer::hit(Card b) // gets card from the deck 
{
	hand.push_back(b); // puts the card in the vector 
}

void BlackJackPlayer::displayPlayerBal() const
{
	cout << "player's " << id << " balance: " << /*Player::getBalance()*/ balance << endl;
	cout << endl;
}

void BlackJackPlayer::setBet(int b) // sets what the player wants to bet 
{
	bet = b;
	//balance -= b; // use protected member from the base class 
}

void BlackJackPlayer::surrender() // allows the player to receive back half of his/her bet and clears his/her hand 
{
	balance = (0.5 * bet) + balance;
	hand.clear();
}

void BlackJackPlayer::doubleDown() // allows the player to double his/her bet and receive one, and only one, additional card to the hand 
{
	balance -= bet;
	bet *= 2;
}

int BlackJackPlayer::total() // calculates the total of the player's hand 
{
	if (hand.size() == 0)
		return 0;
	else
	{
		int tot = 0;
		int numA = 0; // member to count the number of ace in the player's hand 
		for (size_t i = 0; i < hand.size(); ++i) // counts how many Ace's are in the player's hand 
		{
			if (hand[i].getFaceIn() == 0)
				numA += 1;
		}


		for (size_t i = 0; i < hand.size(); ++i) // calculates the total 
		{
			tot = hand[i] + tot;
		}

		switch (numA) // calculates the total based on the number of Ace 
		{
		case 1:
			if (tot > 21)
				tot -= 10;
			break;
		case 2:
			if ((tot - 22) < 10)
				tot -= 10;
			else
				tot -= 20;
			break;
		case 3:
			if ((tot - 33) < 9)
				tot -= 20;
			else
				tot -= 30;
			break;
		case 4:
			if ((tot - 44) < 8)
				tot -= 30;
			else
				tot -= 40;
			break;
		}

		return tot;
	}

}

void BlackJackPlayer::setStand() // sets the value of st to 1 
{
	st = 1;
}

bool BlackJackPlayer::stand() // returns true if the player hits stand 
{
	if (st == 1)
		return true;
	return false;
}

int BlackJackPlayer::checkBlJk() // returns the total of the value of the player's first two cards 
{
	int t = 0;
	for (size_t i = 0; i < hand.size(); ++i) // calculates the total 
	{
		t = hand[i] + t;
	}
	return t;
}

void BlackJackPlayer::blackJack() // pays the player money for blackjack 
{
	balance = balance + (3 * bet);
}

void BlackJackPlayer::win() // if the player wins 
{
	balance = balance + (2 * bet);
}

void BlackJackPlayer::tie() //if the player ties with dealer 
{
	balance = balance;
}

void BlackJackPlayer::lose()
{
	balance -= bet;
}