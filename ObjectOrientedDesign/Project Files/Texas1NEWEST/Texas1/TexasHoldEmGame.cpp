#include "TexasHoldEmGame.h" 
#include "TexasPlayer.h" 
using namespace std;



TexasHoldEmGame::TexasHoldEmGame(int n)
{
	numPlayers = n;
	vector<TexasPlayer>temp(numPlayers); //temp vector 
	for (int i = 0; i < numPlayers; ++i) // assigns id to each player 
	{
		temp[i].setId(i + 1);
	}
	
	
	texDeckOfCards.shuffle(); //shuffles the deck 
	texDeckOfCards.shuffle(); //shuffles the deck 
	players = temp; //assigns temp vector to player vector 
	if (numPlayers >= 3)
	{
		for (size_t i = 0; i < players.size(); ++i)
		{
			if (i == players.size() - 3)
				players[i].setDealer();
			if (i == players.size() - 2)
				players[i].setSmall();
			if (i == players.size() - 1)
				players[i].setBig();
		}
	}
	else
	{
		players[1].setDealer();
		players[1].setBig();
		players[0].setSmall();
	}
	pot = 0;
	MaxBet = 0;
}

TexasHoldEmGame::~TexasHoldEmGame()
{

}

void TexasHoldEmGame::playTexasHoldEm() //this is the actual game function 
{
	int a = 0;
	int count = 0;
	int j = numPlayers;
	while (a == 0)
	{
		texDeckOfCards.shuffle(); //shuffles the deck 
		texDeckOfCards.shuffle(); //shuffles the deck 
		++count;
		cout << endl;
		cout << "10 IS REMOVED FROM YOUR BALANCE TO PLAY" << endl;
		for (int i = 0; i < numPlayers; ++i)
		{
			players[i].sub(10); // sets each player's bet 
			pot += 10;
		}

		for (int i = 0; i < numPlayers; ++i) // ends the round for each player
		{
			players[i].endOfRound();
		}

		dealPlayers(); //deals Players' cards and displays them

		cout << "\nREMOVING MONEY FROM BIG BLIND AND SMALL BLIND\n" << endl;
		for (int i = 0; i < numPlayers; ++i)
		{
			if (players[i].smallBlind())
			{
				players[i].sub(10);
				pot += 10;
			}
			if (players[i].bigBlind())
			{
				players[i].sub(20);
				pot += 20;
			}
		}
		MaxBet = 20; //makes highBet = 20
		cout << "POT: " << pot << endl; //prints out the pot
		cout << "\nPLACE YOUR BET" << endl; // prompts the players to place their bet 
		cout << endl;

		MakeChoice1();
		displayCommunity3(); //displays 3 community cards 
		MakeChoice();
		MakeChoice1();
		displayCommunity4(); // displays the 4th community card along with the previous 3 cards 
		MakeChoice();
		MakeChoice1();
		displayCommunity5(); // displays the 5th community card along with the previous 4 cards 
		MakeChoice();
		MakeChoice1();

		for (int i = 0; i < players.size(); i++)
			players[i].CompareHand(community);
		
		TexasPlayer play;
		play.winner(pot);
		
		int c;
		cout << "Enter 0 to keep playing or 1 to quit" << endl;
		cin >> c;
		

		a = c; // used to check if the player wants to keep playing

		community.clear(); //clears community cards
		for (int i = 0; i < numPlayers; ++i) //clears the player's hand
		{
			players[i].clearHand();
		}

		for (int i = 0; i < numPlayers; ++i)
			players[i].resetSmBgDlAl();

		for (int i = 0; i < numPlayers; ++i) //deletes player if balance is zero
		{
			if (players[i].balanceReturn() == 0 || players[i].balanceReturn() < 0)
			{
				players[i].setCheckOut();
				j--;
				if(j == 0)
				{
					
				}
			}
		}
		if (j == 0)
			a = 1;
		if (numPlayers >= 3)
		{
			for (size_t i = 0; i < players.size(); ++i)
			{
				if (i == ((players.size() - 3 + count) % players.size()))
				{
					players[i].setDealer();
				}
				if (i == ((players.size() - 2 + count) % players.size()))
				{
					players[i].setSmall();
				}
				if (i == ((players.size() - 1 + count) % players.size()))
				{
					players[i].setBig();
				}
			}
		}
		else
		{
			players[1].setDealer();
			players[1].setBig();
			players[0].setSmall();
		}

		while (c > 1)
		{
			cout << "Enter 0 to keep playing or 1 to quit" << endl;
			cin >> c;
		}

		texDeckOfCards.reset(); //resets the deck
		pot = 0;
		MaxBet = 0;
	}

}

void TexasHoldEmGame::MakeChoice() // make choice function just for the big blind
{
	int choice = 0;
	for (int i = 0; i < numPlayers; ++i)
	{
		if (!players[i].checkOut())
		{
			if (!players[i].checkAllIn())
			{
				if (players[i].bigBlind())
				{
					if (!players[i].checkFold())
					{
						players[i].displayPlayerId();
						players[i].displayPlayerHand();
						cout << "Choose from the following" << endl;
						cout << "Enter 1 to Raise " << endl;
						cout << "Enter 2 to Fold" << endl;
						cout << "Enter 4 to All In" << endl;
						cin >> choice;
						while (choice < 1 || choice > 5 || choice == 3)
						{
							cout << "invalid input." << endl;
							cout << "Choose from the following" << endl;
							cout << "Enter 1 to Raise " << endl;
							cout << "Enter 2 to Fold" << endl;
							cout << "Enter 4 to All In" << endl;
							cin >> choice;
						}

						cout << endl;
						if (choice == 1)
						{
							int b = 0;
							cout << "by how much: ";
							cin >> b; // reads in each player's bet 
							while (b > players[i].balanceReturn() || b <= 0)
							{
								cout << "invalid bet. Place your bet: " << endl;
								cin >> b; // reads in each player's bet 
							}
							int c;
							c = players[i].match(MaxBet);
							cout << "Called " << c << " and Raised " << b << endl;
							cout << endl;
							b += c;
							pot += b;
							cout << "POT: " << pot << endl; //prints out the pot
							cout << endl;
							players[i].sub(b); // sets each player's bet
							MaxBet = b;
						}
						if (choice == 2)
						{
							players[i].fold(); //clears the player's hand
							cout << "" << endl;
						}
						if (choice == 4)
						{
							int b = 0;
							b = players[i].balanceReturn();
							pot += b;
							if (b > MaxBet)
								MaxBet = b;
							players[i].allIn();
							cout << "POT: " << pot << endl; //prints out the pot
							cout << endl;
						}
					}
				}
			}
		}
	}
}

void TexasHoldEmGame::MakeChoice1() // make choice 1 function
{
	for (int i = 0; i < numPlayers; ++i)
	{
		int choice = 0;
		if (!players[i].checkOut())
		{
			if (!players[i].checkAllIn())
			{
				if (!players[i].checkFold()) {
					players[i].displayPlayerId();
					players[i].displayPlayerHand();
					if (!players[i].bigBlind())
					{
						cout << "Choose from the following" << endl;
						cout << "Enter 1 to Raise " << endl;
						cout << "Enter 2 to Fold" << endl;
						if (players[i].match(MaxBet) != 0)
							cout << "Enter 3 to Call " << players[i].match(MaxBet) << endl;
						else
							cout << "Enter 5 to Check" << endl;
						cout << "Enter 4 to All In" << endl;
						cin >> choice;
						while (choice < 1 || choice > 5)
						{
							cout << "invalid input." << endl;
							cout << "Choose from the following" << endl;
							cout << "Enter 1 to Raise " << endl;
							cout << "Enter 2 to Fold" << endl;
							if (players[i].match(MaxBet) != 0)
								cout << "Enter 3 to Call " << players[i].match(MaxBet) << endl;
							else
								cout << "Enter 5 to Check" << endl;
							cout << "Enter 4 to All In" << endl;
							cin >> choice;
						}
					}
					else
					{
						cout << "Choose from the following" << endl;
						cout << "Enter 2 to Fold" << endl;
						if (players[i].match(MaxBet) != 0)
							cout << "Enter 3 to Call " << players[i].match(MaxBet) << endl;
						else
							cout << "Enter 5 to Check" << endl;
						cout << "Enter 4 to All In" << endl;
						cin >> choice;
						while (choice < 2 || choice > 5)
						{
							cout << "invalid input." << endl;
							cout << "Choose from the following" << endl;
							cout << "Enter 2 to Fold" << endl;
							if (players[i].match(MaxBet) != 0)
								cout << "Enter 3 to Call " << players[i].match(MaxBet) << endl;
							else
								cout << "Enter 5 to Check" << endl;
							cout << "Enter 4 to All In" << endl;
							cin >> choice;
						}
					}
					cout << endl;
					if (choice == 1)
					{
						int b = 0;
						cout << "by how much: ";
						cin >> b; // reads in each player's bet 
						while (b > players[i].balanceReturn() || b <= 0)
						{
							cout << "invalid bet. Place your bet: " << endl;
							cin >> b; // reads in each player's bet 
						}
						int c;
						c = players[i].match(MaxBet);
						cout << "Called " << c << " and Raised " << b << endl;
						cout << endl;
						b += c;
						pot += b;
						cout << "POT: " << pot << endl; //prints out the pot
						cout << endl;
						players[i].sub(b); // sets each player's bet
						MaxBet = b;
					}
					if (choice == 2)
					{
						players[i].fold(); //clears the player's hand
						cout << "" << endl;
					}
					if (choice == 3)
					{
						pot += players[i].match(MaxBet);
						players[i].sub(players[i].match(MaxBet)); // sets each player's bet
						cout << "POT: " << pot << endl; //prints out the pot
						cout << endl;
					}
					if (choice == 4)
					{
						int b = 0;
						b = players[i].balanceReturn();
						pot += b;
						if (b > MaxBet)
							MaxBet = b;
						players[i].allIn();
						cout << "POT: " << pot << endl; //prints out the pot
						cout << endl;
					}

					if (choice != 1)
						players[i].endOfRound();
				}
			}
		}
	}

	MaxBet = 0;
	for (int i = 0; i < numPlayers; ++i) // ends the round for each player
	{
		players[i].endOfRound();
	}
}

void TexasHoldEmGame::dealPlayers()
{
	// loop for passing out first card 
	for (int i = 0; i < numPlayers; ++i)
	{
		if (texDeckOfCards.moreCards()) // deals card if there are cards in the deck 
			players[i].hit(texDeckOfCards.dealCard());
	}

	// loop for passing out second card 
	for (int i = 0; i < numPlayers; ++i)
	{
		if (texDeckOfCards.moreCards()) // deals card if there are cards in the deck 
			players[i].hit(texDeckOfCards.dealCard());
	}

	for (int i = 0; i < numPlayers; ++i) //displays player id and hand using polymorphic behavior 
	{
		Player *aPtr = &players[i];
		aPtr->displayPlayerId();
		aPtr->displayPlayerHand();
		aPtr = nullptr;
	}
}

void TexasHoldEmGame::displayCommunity3() //displays 3 community cards 
{
	for (int i = 0; i < 3; ++i)
	{
		if (texDeckOfCards.moreCards()) // deals card if there are cards in the deck 
			community.push_back(texDeckOfCards.dealCard());
	}
	cout << "DEALING FLOP" << endl;
	for (size_t i = 0; i < community.size(); ++i)
	{
		cout << community[i].toString() << endl; // converts the card to string and displays it 
	}
	cout << endl;
}

void TexasHoldEmGame::displayCommunity4() // displays the 4th community card along with the previous 3 cards 
{
	if (texDeckOfCards.moreCards()) // deals card if there are cards in the deck 
		community.push_back(texDeckOfCards.dealCard());
	cout << "DEALING TURN" << endl;
	for (size_t i = 0; i < community.size(); ++i)
	{
		cout << community[i].toString() << endl; // converts the card to string and displays it 
	}
	cout << endl;
}

void TexasHoldEmGame::displayCommunity5() // displays the 5th community card along with the previous 4 cards 
{
	if (texDeckOfCards.moreCards()) // deals card if there are cards in the deck 
		community.push_back(texDeckOfCards.dealCard());
	cout << "DEALING RIVER" << endl;
	for (size_t i = 0; i < community.size(); ++i)
	{
		cout << community[i].toString() << endl; // converts the card to string and displays it 
	}
	cout << endl;
}

void TexasHoldEmGame::setPot(int p)
{
	pot = p;
}
int TexasHoldEmGame::returnPot()
{
	return pot;
}