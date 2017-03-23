#include "Poker.h"
#include <algorithm>
#include<iostream>
#include <math.h>
using namespace std;

template<class T>
int rounding(T a)
{
	
	return (int)ceil(a);
}


Poker::Poker(Player & mainPlyr)
{
	//int choice;
	currentDeck = new Deck();
	dealer = new Player("Dealer");
	table.push_back(mainPlyr);
	cout << "How many players ? (Must be 2-8)" << endl;
	cin >> numOfPlayers;

	while (!(numOfPlayers >= 2 && numOfPlayers <= 8))
	{
		cout << "You can't play Texas Hold 'em by yourself...\n" << "Please enter a number from 2 to 8: ";
		cin >> numOfPlayers;
		cout << endl;
	}

	for (int i = 1; i < numOfPlayers; ++i)
	{
		Player pTemp(1000);
		table.push_back(pTemp);
	}

	cout << table.size() << endl;

	allCheck = 0;
	blindIndex = 1;
	maxBetAmount = 0;
	folds = 0;
	pot = 0;
}

Poker::~Poker()
{
	table.clear();

	cout << "Game over" << endl;
}

void Poker::flop()
{
	//pulls a cards 3 times
	for (int i = 0; i < 3; ++i)
		flip();
}

void Poker::flip()
{
	river.push_back(currentDeck->Deal()); //add a card to the community cards 
}

void Poker::setMaxBetAmount(int a) //reset deck, increment blind index, 
{
	maxBetAmount = a;
}

int Poker::getMaxBetAmount() const //reset deck, increment blind index, 
{
	return maxBetAmount;
}

void Poker :: start()
{
	int select = 0;
	cout << "Welcome to Poker" << endl;
	cout << "What would you like to do ? (input number)"
		<< "\n1.) Play \n2.) Exit to lobby " << endl;
	cin >> select;

again:     
	while (select != 2) //initiate the games
	{
		int roundTotal = 0;   //Used to determine end game.

		switch (select)
		{
			case 1:
				while (roundTotal <= 5)
				{
					currentDeck->~Deck();
					currentDeck = new Deck();

					littleBigBlindBet();
					bet();  //subsequent players call or raise bet
					//check that all players have contributed equal amount after raise
					//if not go to bet function where they can call or raise

					if (folds == numOfPlayers - 1)
						goto win;

					for (int j = 0; j < 2; ++j)
					{
						dealer->addCard(currentDeck->Deal());    //Deals card to dealer

						for (size_t i = 0; i < table.size(); ++i)
						{
							//player i, deal
							if (!table[i].getSurrender())
							{
								table[i].addCard(currentDeck->Deal()); //takes current player deals them a card in the Deck 'Deal' function
								sort(table[i].hand.begin(), table[i].hand.end());
								table[i].highCard = table[i].hand[j];
							}
						}
					}

					flop(); 	//flop will show three cards in the river
					printRiver();

					for (int i = 0; i < numOfPlayers; ++i)   //reveal card and decide who has highest points
					{
						cout << table[i] << endl;
						//winner(table[i]);
					}

					bet();							//players can check if they dont want to bet until another card 
					//if player bets all must then call, raise, or fold
					if (folds == numOfPlayers - 1)
						goto win;

					flip();					//turn a card, flip(), 4 cards in community hand
					printRiver();
					bet();						//another round of betting
					if (folds == numOfPlayers - 1)
						goto win;

					flip();								//turn a card, flip for 5 card river
					printRiver();
					bet();							//another round of betting

	win:			int winningHand = 0;
					int playerIndex = 0;

					for (int i = 0; i < numOfPlayers; ++i)
					{
						if (!(table[i].getSurrender()))
						{
							if (river.size() < 5)
							{
								winningHand = 1;
								playerIndex = i;
								break;
							}

							table[i].pokerResult = winner(table[i]);

							if (table[i].pokerResult > winningHand)
							{
								winningHand = table[i].pokerResult;
								playerIndex = i;
							}
						}
					}

					cout << table[playerIndex].getName() << " wins!!!\n" << endl;

					table[playerIndex].setBalance(table[playerIndex].getBalance() + pot);

					cout << "Play again? (1 for yes, 2 for no)" << endl;
					cin >> select;

				//	if (select == 2)				
						
	
					folds = 0;
					++roundTotal; //increment roundTotal

					//reset surrender bool to stop 
					for (int j = 0; j < numOfPlayers; ++j)
					{
						table[j].resetHand();
						table[j].setSurrender(false);
					}

					river.clear();
					currentDeck->~Deck();
					currentDeck = new Deck();

					goto again;
				}
				break;
			case 2: //exit to main lobby
				break;

			default:
				cout << "\nInvalid input: Please put your drink down! :)" << endl;
				cout << "What would you like to do? (input number)"
					<< "\n1.) Play\n2.) Exit back to lobby\n -" << endl;
				cin >> select;
			
			break;
		
		}
	}
}

void Poker::littleBigBlindBet() //take blindindex and use it to make certain player bet respective amount
{
	

	int tempBlindIndex = blindIndex;
	cout << table[tempBlindIndex % numOfPlayers].getName() << " and " << table[(tempBlindIndex + 1) % numOfPlayers].getName() << ", post $10 and $20 blind to the pot respectively." << endl;
	int blindBet = 10;
	for (int i = 0; i < 2; ++i)
	{
		table[(tempBlindIndex) % numOfPlayers].setBalance(table[tempBlindIndex % numOfPlayers].getBalance() - blindBet);
		pot += blindBet;
		blindBet = 20; //change it for the Big Blind
		++tempBlindIndex;
	}

	blindIndex++; //increments actual index for the next game of littleBig betting
}

void Poker::bet()
{
		int tempIndex = blindIndex % numOfPlayers;
		do
		{
			int choice = 0;

			if (folds == numOfPlayers - 1)
				break;

			if (!table[tempIndex % numOfPlayers].surrender)
			{
start:			cout << table[tempIndex % numOfPlayers].getName() << ", what would you like to do ? " << endl;

				if (table[tempIndex % numOfPlayers].getBetAmountPlyr() == getMaxBetAmount()) //bet amount matches 
					cout << "1.)Check " << endl;
				else
					cout << "1.)Call $" << getMaxBetAmount() << endl;
					cout << "2.)Raise\n3.)All In\n4.)Fold\n" << endl;
					cout <<table[tempIndex % numOfPlayers].getName() << "'s balance: $" << table[tempIndex % numOfPlayers].getBalance() << "\n" << endl;

					cin >> choice;
					switch (choice)
					{
					case 1:
						if (table[tempIndex % numOfPlayers].getBetAmountPlyr() == getMaxBetAmount()) //bet amount matches 

							cout << table[tempIndex % numOfPlayers].getName() << " checks.\n" << endl;

						else
						{
							cout << table[tempIndex % numOfPlayers].getName() << " calls.\n" << endl;

							table[tempIndex % numOfPlayers].setBetAmountPlyr(getMaxBetAmount());
							table[tempIndex % numOfPlayers].setBalance((table[tempIndex % numOfPlayers].getBalance() - table[tempIndex % numOfPlayers].getBetAmountPlyr()));
							
							pot += table[tempIndex % numOfPlayers].getBetAmountPlyr();
						}
						break;

					case 2:
						cout << "How much would you like to raise ? : ";
						cin >> maxBetAmount;
						cout << endl;

						table[tempIndex % numOfPlayers].setBetAmountPlyr(getMaxBetAmount());

						table[tempIndex % numOfPlayers].setBalance((table[tempIndex % numOfPlayers].getBalance() - table[tempIndex % numOfPlayers].getBetAmountPlyr())); //use setBalance

						cout << table[tempIndex % numOfPlayers].getName() << " raised by $" << getMaxBetAmount()
							 << "\n" << endl;

						pot += rounding(table[tempIndex % numOfPlayers].getBetAmountPlyr());
					
						allCheck = 0;
						break;

					case 3:
						cout << table[tempIndex % numOfPlayers].getName() << " is All In!" << endl;
						table[tempIndex % numOfPlayers].setBetAmountPlyr(table[tempIndex % numOfPlayers].getBalance());
						table[tempIndex % numOfPlayers].setBalance((table[tempIndex % numOfPlayers].getBalance() - table[tempIndex % numOfPlayers].getBetAmountPlyr()));
						maxBetAmount = table[tempIndex % numOfPlayers].betAmount;

						pot += rounding(table[tempIndex % numOfPlayers].getBetAmountPlyr());
						break;
					case 4:
						table[tempIndex % numOfPlayers].setSurrender(true);
						cout << table[tempIndex % numOfPlayers].getName() << " folds.\n" << endl;
						++folds;
						break;

					default:
						cout << "incorrect input.\n" << endl;
						goto start;

				}
					++allCheck; 
			}

			tempIndex++;

		} while (allCheck != numOfPlayers); 

	allCheck = 0;

}

void Poker::printRiver()
{
	cout << "Community cards in River:" << endl;
	for (size_t i = 0; i < river.size(); i++)
	{
		cout << river[i] <<endl;
	}
	cout << endl;
}

int Poker::winner(Player &tempPlyr)
{
	//push river into players hand
	for (size_t i = 0; i < river.size(); ++i)
	{
		tempPlyr.hand.push_back(river[i]);
	}

	//sort hand least to greatest
	sort(tempPlyr.hand.begin(), tempPlyr.hand.end());

	//Straight Flush consecutive cards same suit
	for (int i = 0; i < 2; ++i)
	{
		if (tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+1].getSuit()
			&& tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+2].getSuit()
			&& tempPlyr.hand[1].getSuit() == tempPlyr.hand[i+3].getSuit()
			&& tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+4].getSuit()
			&& tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+5].getSuit())
		{
			if ((tempPlyr.hand[i].getThValue() == (tempPlyr.hand[i + 1].getThValue() + 1))
				&& ((tempPlyr.hand[i + 2].getThValue() == (tempPlyr.hand[i + 3].getThValue() + 1))
				&& ((tempPlyr.hand[i + 4].getThValue() == (tempPlyr.hand[i + 5].getThValue() + 1)))))
			{
				if (tempPlyr.hand[i].getThValue() == 10){

				cout << tempPlyr.getName() << " has a Royal Flush of " << tempPlyr.hand[i].getSuit() << endl;
				return 135;
				}

				else
					cout << tempPlyr.getName() << " has a Straight Flush and High Card " << tempPlyr.highCard.getRank() << endl;
					return 120 + tempPlyr.highCard.getThValue(); //8 for STRAIGHT FLUSH
			}
		}
	}

	//FOUR OF A KIND 4 kind of same rank
	for (int i = 3; i < 7; ++i)
	{

		//if card 1 is equal to card 2 and equal to card 3 RANK 
		if ((tempPlyr.hand[i - 3].getThValue() == tempPlyr.hand[i - 2].getThValue())
			&&(tempPlyr.hand[i - 2].getThValue() == tempPlyr.hand[i - 1].getThValue())
			&& (tempPlyr.hand[i - 1].getThValue() == tempPlyr.hand[i].getThValue()))
		{
			cout << tempPlyr.getName() << " has Four of a Kind and High Card " << tempPlyr.highCard.getRank() << endl;
			return 105 + tempPlyr.highCard.getThValue(); //7 for a FOUR OF A KIND
		}
	}


	//FULL HOUSE 3 of a kind, and 2 of a kind
	//three of a kind
	for (int i = 2; i < 7; ++i)
	{

		//if card 1 is equal to card 2 and equal to card 3 RANK 
		if ((tempPlyr.hand[i - 2].getThValue() == tempPlyr.hand[i - 1].getThValue())
			&& (tempPlyr.hand[i - 1].getThValue() == tempPlyr.hand[i].getThValue()))
		{
			if ((tempPlyr.hand[i - 1].getThValue()) == (tempPlyr.hand[i].getThValue()))
			{
				cout << tempPlyr.getName() << " has a Full House and High Card " << tempPlyr.highCard.getRank() << endl;
				return 90 + tempPlyr.highCard.getThValue(); //FULL HOUSE
			}
		}
	}


	//FLUSH 5 card same suit
	for (int i = 0; i<2; ++i)
	{
		if (tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+1].getSuit()
			&& tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+2].getSuit()
			&& tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+3].getSuit()
			&& tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+4].getSuit()
			&& tempPlyr.hand[i].getSuit() == tempPlyr.hand[i+5].getSuit())
		
		{
			cout << tempPlyr.getName() << " has a Flush and High Card " << tempPlyr.highCard.getRank() << endl;
			return 75 + tempPlyr.highCard.getThValue();
		}
	}

	//STRAIGHT 5 conscutive card rank
	for (int i = 0; i < 2; ++i)
	{
		if ((tempPlyr.hand[i].getThValue() == (tempPlyr.hand[i + 1].getThValue() - 1))
			&& ((tempPlyr.hand[i + 2].getThValue() == (tempPlyr.hand[i + 3].getThValue() - 1))
			&& ((tempPlyr.hand[i + 4].getThValue() == (tempPlyr.hand[i + 5].getThValue() - 1)))))
		{
			cout << tempPlyr.getName() << " has a Straight and High Card " << tempPlyr.highCard.getRank() << endl;
			return 60 + tempPlyr.highCard.getThValue();
		}
	}


	//3 OF A KIND
	for (int i = 2; i < 7; ++i)
	{

		//if card 1 is equal to card 2 and equal to card 3 RANK 
		if ((tempPlyr.hand[i - 2].getThValue() == tempPlyr.hand[i - 1].getThValue())
			&& (tempPlyr.hand[i - 1].getThValue() == tempPlyr.hand[i].getThValue()))
		{
			cout << tempPlyr.getName() << " has Three of a Kind and High Card " << tempPlyr.highCard.getRank() << endl;
			return 45 + tempPlyr.highCard.getThValue();//THREE OF A KIND is greater than 2 pair and 1 pair
		}
	}



	//pairs
	for (int i = 1; i < 7; ++i)
	{
		if (tempPlyr.hand[i - 1].getThValue() == tempPlyr.hand[i].getThValue())
		{
			for (int j = 1; j < 7; ++j)
			{
				if (tempPlyr.hand[j - 1].getThValue() == tempPlyr.hand[j].getThValue())
				{
					cout << tempPlyr.getName() << " has Two Pair and High Card " << tempPlyr.highCard.getRank() << endl;
					return 30 + tempPlyr.highCard.getThValue(); //2 for a TWO PAIR
				}
			}
				cout << tempPlyr.getName() << " has a One Pair and High Card " << tempPlyr.highCard.getRank() << endl;
				return 15 + tempPlyr.highCard.getThValue(); //1 for a pair
		}
	}

	return tempPlyr.highCard.getThValue();
}

Player Poker::validWinner()
{
	int winningHand = 0;
	int playerIndex = 0;

	for (int i = 0; i < numOfPlayers; ++i)
	{

			if (winner(table[i]) > winningHand && !table[i].getSurrender())
			{
				winningHand = winner(table[i]);
				playerIndex = i;
			}
	}

	return table[playerIndex];
}
