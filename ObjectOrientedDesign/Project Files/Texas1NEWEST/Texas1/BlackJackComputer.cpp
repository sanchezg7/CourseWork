#include "BlackJackComputer.h" 
#include <vector> 
#include <iostream> 
#include <string> 
using namespace std;

BlackJackComputer::BlackJackComputer(int b, int c) //constructor 
{
	totOpen = b; // total value of open hand 
	numA = c; // number of ace 
}


void BlackJackComputer::displayCompHandHidden() // displays the computer's hand except for the one hidden 
{
	cout << "first card hidden" << endl; // shows first card is hidden 
	for (size_t i = 1; i < compHand.size(); ++i)
	{
		cout << compHand[i].toString() << endl; // converts the card to string and displays it 
	}

	cout << "\n" << endl; // extra spacing 
}

void BlackJackComputer::displayCompHandAll() // displays all computer's hand 
{
	cout << "dealer's hand" << endl;
	for (size_t i = 0; i < compHand.size(); ++i)
	{
		cout << compHand[i].toString() << endl; // converts the card to string and displays it 
	}

	cout << "dealer's total: " << total() << endl;
	if (total() == 21)
		cout << "Dealer Has 21!" << endl;
	if (total() > 21)
		cout << "bust" << endl;
	cout << "\n" << endl; // extra spacing 
}

void BlackJackComputer::hit(Card b) // computer gets a card from the deck 
{
	compHand.push_back(b); // puts the card in the vector 
	//canHit17(); 
}


bool BlackJackComputer::canHit17() // checks if computer's open cards are up to value 17 
{
	if (total() < 17)
		return true;
	return false;
}

int BlackJackComputer::total() // calculates the total of the computer's hand 
{
	int numA = 0;
	int tot = 0;
	for (size_t i = 0; i < compHand.size(); ++i) // counts how many Ace's are in the computer's hand 
	{
		if (compHand[i].getFaceIn() == 0)
			numA += 1;
	}


	for (size_t i = 0; i < compHand.size(); ++i) // calculates the total 
	{
		tot = compHand[i] + tot;
	}

	switch (numA) // calculates the total based on the number of Ace 
	{
	case 1:
		if (tot > 21)
		{
			tot -= 10;
			cout << tot << endl;
		}
		else
			cout << tot << endl;
		break;
	case 2:
		if ((tot - 22) < 10)
		{
			tot -= 10;
			cout << tot << endl;
		}
		else
		{
			tot -= 20;
			cout << tot << endl;
		}
		break;
	case 3:
		if ((tot - 33) < 9)
		{
			tot -= 20;
			cout << tot  << endl;
		}
		else
		{
			tot -= 30;
			cout << tot  << endl;
		}
		break;
	case 4:
		if ((tot - 44) < 8)
		{
			tot -= 30;
			cout << tot  << endl;
		}
		else
		{
			tot -= 40;
			cout << tot  << endl;
		}
		break;
	}
	return tot;
}