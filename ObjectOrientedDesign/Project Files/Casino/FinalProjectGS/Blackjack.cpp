#include "Blackjack.h"
//#include "Deck.h"
//#include "card.h"
#include <vector>
#include <iostream>
#include <string>
//#include "game.h"
using namespace std;

//game has 4 players and the dealer 
Blackjack::Blackjack(Player& mainPlyr)
{
	//gameDeck = new Deck();
	dealer = new Player("dealer");
	//reads in number of player and adds main player to game
	cout << "Enter how many players: " << endl;
	cin >> numOfPlayers;
	
	table.push_back(mainPlyr);

	//pushback amount of players into dynamic vector
	for(int i = 1; i < numOfPlayers; ++i)
	{
		Player pTemp(1000);
		table.push_back(pTemp);
	}
	//cout << table.size() << endl;

}
Blackjack::~Blackjack()
{
	//delete[] gameDeck;
	//delete[] dealer;
	table.clear();

	cout << "Game over" << endl;
	//somehow destory the game
}


void Blackjack::bet(Player &plyr)
{
	int wage =0;
	//at least 5 or less than 1000

	cout << plyr.getName() << "'s balance: $" << plyr.getBalance() << endl;

	do
	{
		cout << plyr.getName() << ", Enter amount to bet (minimum $5, maximum $100)" << endl;
		cin >> wage;
	} while (wage < 5 || wage > 100);

	plyr.setBetAmountPlyr(wage);
	plyr.setBalance(plyr.getBalance() - wage); //subtracts the difference from the players balance
}


//drive through the game for the blackjack game
void Blackjack::start()
{
	int select;
	cout << "Welcome to Blackjack: " << endl;
	cout << "What would you like to do? (input number)"
		 << "\n1.) Play\n2.) Exit back to lobby" << endl;
	cin >> select;

	while (select != 2)
	{
		gameDeck = new Deck(); // create deck in loop to randomize deck

		switch (select)
		{
		case 1: //Play Blackjack
		{
					for (size_t i = 0; i < table.size(); ++i) //collect bets for all players
					{
						bet(table[i]);
						table[i].resetHand();
						table[i].setStand(false);
						table[i].setBust(false);
						table[i].setSurrender(false);
					}
					//intial round deal two cards per player
					for (int j = 0; j < 2; ++j)
					{
						dealer->addCard(gameDeck->Deal());    //Deals card to dealer

						for (size_t i = 0; i < table.size(); ++i)
						{
							//player i, deal
							table[i].addCard(gameDeck->Deal()); //takes current player deals them a card in the Deck 'Deal' function
						}
					}

					cout << "dealer has: \n" << dealer->hand[0] << "\n" << endl;   //Exposes one card for dealer.

					//A loop that continue play until player stands, surrenders, doubles down, or busts
					//ask player to hit, stand, double down, surrender

					int aces = 2;

					for (size_t i = 0; i < table.size(); ++i)
					{
						//decide aces high or low.

						table[i].setAceHighLow(false);

						cout << table[i].getName() << ", do you want aces high or low?\n (1 for High, 2 for Low): ";
						cin >> aces;
						cout << "\n" << endl;

						if (aces == 1)
							table[i].setAceHighLow(true);


						if (table[i].getHandValue(table[i].aceHighLow) == 21)
						{
							cout << table[i].getName() << " has BLACKJACK!\n" << endl;
							goto natural;
						}

						cout << table[i] << "\n" << table[i].getName() << "'s hand total: " << table[i].getHandValue(table[i].aceHighLow) << "\n" << endl;


					cont:   //used to continue playing until Player busts



						int action = 0;

						if (table[i].getHandValue(table[i].aceHighLow) > 21)
							action = 2;

						else
						{
							cout << table[i].getName() << ", What do you wish to do this round?"
								<< "\n1)Hit 2)Stand 3)Double Down 4)Surrender"
								<< "\nEnter integer: ";
							cin >> action;
							cout << "\n" << endl;
						}

						switch (action)
						{
						case 1:
							hit(table[i]);

							break;

						case 2:
							table[i].setStand(true);
							break;

						case 3:
							doubleDown(table[i]);
							break;

						case 4:
							table[i].setSurrender(true);
							surrender(table[i]);
							break;

						default:
							cout << "Invalid input.\n"
								<< "What do you wish to do this round?"
								<< "\n1)Hit 2)Stand 3)Double Down 4)Surrender"
								<< "\nEnter integer: ";
							cin >> action;
							cout << "\n" << endl;
							break;
						} //End switch for 

natural:					if (table[i].getHandValue(table[i].aceHighLow) < 21 && !(table[i].getStand() || table[i].getSurrender()))
							goto cont;
					
					}	//end of switch statement for play	


					//Print out dealer's Hand and Total Value
					cout << *dealer << "\n" << dealer->getName() << "'s hand total: " << dealer->getHandValue(dealer->aceHighLow) << "\n" << endl;

					while (dealer->getHandValue(dealer->aceHighLow) < 17 && !(dealer->getHandValue(dealer->aceHighLow) > 21))
					{
						hit(*dealer);
					}

					for (size_t i = 0; i < table.size(); i++)
					{
						if (winner(table[i])) //checks if player wins
						{
							cout << table[i].getName() << " Wins! " << endl;
							//Blackjack::~Blackjack(); //destructor will disburse funds to winner
						}
					}

					dealer->resetHand();
		}
			break;

		case 2:
			break;

		default: //Incorrect input for select. 1 to play, 2 to exit
			cout << "\nInvalid input: Please put your drink down! :)" << endl;
			cout << "What would you like to do? (input number)"
				<< "\n1.) Play\n2.) Exit back to lobby\n -" << endl;
			cin >> select;
			break;
		} //end of switch statement for playing again. 

		cout << "Play again?\n (1 = Yes, 2 = No): ";
		cin >> select;

		gameDeck->~Deck(); //destroys deck
	}
}

//return current value of players hand
//face cards worth 10
//ace either high or low
int Blackjack::sumPoints(Player tempPlyr) const
{
	int bjSum = 0;
	for ( size_t i =0; i<table.size(); ++i)
	{
		if (tempPlyr.hand[i].getRank() == "Ace")
		{
			if (tempPlyr.getAceHighLow() == true) //aces are high, add 11 to score
			{
				bjSum += 11;
			}
			else {
				bjSum += 1; //aces low add one to score
			}
		}
		else
			bjSum += tempPlyr.hand[i].getBjValue();
	}
	return bjSum;
}



bool Blackjack::winner(Player& tempPlyr)
{
	if (tempPlyr.getSurrender() == true)
	{
		cout << tempPlyr.getName() << " surrenders, deduct half of original bet." << endl;
		return false;
	}

	//if player busts
	else if (tempPlyr.getHandValue(tempPlyr.aceHighLow) > 21)
	{
		cout << tempPlyr.getName() << " has busted." << endl;
		return false;
	}
	//if dealer busts
	else if (dealer->getHandValue(dealer->aceHighLow) > 21)
	{
		cout <<  "Dealer has busted." << endl;
		tempPlyr.setBalance(tempPlyr.getBalance() + (tempPlyr.getBetAmountPlyr() * 2));
		return true;
	}
	//indicates blackjack, or natural
	else if (tempPlyr.getHandValue(tempPlyr.aceHighLow) == 21 && (tempPlyr.hand.size() < dealer->hand.size() || dealer->getHandValue(dealer->aceHighLow) != 21)) 
	{
		tempPlyr.setBalance(tempPlyr.getBalance() + (tempPlyr.getBetAmountPlyr() * 3 / 2));
		return true;
	}
	//non-natural win
	else if (tempPlyr.getHandValue(tempPlyr.aceHighLow) > 21 && tempPlyr.getHandValue(tempPlyr.aceHighLow) > dealer->getHandValue(tempPlyr.aceHighLow) 
		|| (tempPlyr.getHandValue(tempPlyr.aceHighLow) == 21 && dealer->getHandValue(tempPlyr.aceHighLow) != 21))
	{
		tempPlyr.setBalance(tempPlyr.getBalance() + (tempPlyr.getBetAmountPlyr() * 2));
		return true;
	}
	else if (dealer->getHandValue(dealer->aceHighLow) > tempPlyr.getHandValue(tempPlyr.aceHighLow))
		cout << tempPlyr.getName() << " lost." << endl;

	else if (dealer->getHandValue(dealer->aceHighLow) == tempPlyr.getHandValue(tempPlyr.aceHighLow))
	{
		cout << tempPlyr.getName() << " tied with dealer." << endl;
		tempPlyr.setBalance(tempPlyr.getBalance() + tempPlyr.getBetAmountPlyr());
	}
	return false;
}

void Blackjack::hit(Player& tempPlyr)
{
	//access current deck of blackjack game and add it requested player hand
	tempPlyr.hand.push_back(gameDeck->Deal());
	
	cout << tempPlyr << tempPlyr.getName() << "'s hand total: " 
		 << tempPlyr.getHandValue(tempPlyr.aceHighLow) << "\n" << endl; //print players new cards and sum of ranks
	
}

void Blackjack::surrender(Player &tempPlyr)
{
	//only remove half of original bet from beginning of the game
	tempPlyr.setBalance(tempPlyr.getBalance() + (tempPlyr.getBetAmountPlyr()/ 2));
}

void Blackjack::doubleDown(Player &tempPlyr)
{
	if (tempPlyr.hand.size() != 2)
		cout << "You cannot double down." << endl;
	else
	{
		tempPlyr.setStand(true);
		tempPlyr.setBetAmountPlyr((tempPlyr.getBetAmountPlyr()) * 2); //fetch current bet amount from player and doubles it
		hit(tempPlyr);
	}
}

/*srand(time(NULL));
int i = rand() % 1;
if (i = 0)
setAceHighLow(false);
else
setAceHighLow(true);*/