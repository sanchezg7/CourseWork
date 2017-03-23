#include "Player.h" 
#include "BlackJackPlayer.h" 
#include "BlackJackComputer.h" 
#include "Card.h" 
#include "DeckOfCards.h" 
#include "slotMachines.h" 
#include "TexasHoldEmGame.h" 
#include <iostream> 
#include <vector> 
using namespace std;

int decision = 0;
int main()
{
	while (decision == 0)
	{
		cout << "Play which game?" << endl;
		cout << "Enter\n 1 for Slots\n 2 for Black Jack\n 3 for Hold Em'\n 4 to leave this FABULOUS CASINO: ";
		cin >> decision;

		while (decision == 1)
		{
			slotMachines reel;
			decision = 0;
			reel.play();
			break;
		}
		while (decision == 3)
		{
			int a; // number of players
			cout << endl;
			cout << "WELCOME TO TEXAS HOLD'EM!!!!!" << endl;
			cout << "Enter the number of players from 2 to 8" << endl;
			cin >> a; //reads in the number of players
			while (a < 2 || a > 8) //input validation
			{
				cout << "Enter the number of players from 2 to 8" << endl;
				cin >> a; //reads in the number of players
			}
			TexasHoldEmGame *HoldEmPtr = new TexasHoldEmGame(a); //dynamically allocates memory for texas hold em game
			decision = 0;
			HoldEmPtr->playTexasHoldEm();
			delete HoldEmPtr;
			break;
		}
		while (decision == 2)
		{
			int numPlayers; // number of players 
			DeckOfCards myDeckOfCards; // Blackjack deck of cards 
			BlackJackComputer computer; // computer player is created 
			cout << "WELCOME TO BLACKJACK!!!" << endl;
			cout << endl;
			cout << "Input the number of players between 1 and 4 inclusive: ";
			cin >> numPlayers; // inputs the number of players 
			while (numPlayers < 1 || numPlayers > 4) // loop to handle invalid inputs 
			{
				cout << "Incorrect input" << endl;
				cout << "Input the number of players between 1 and 4 inclusive: ";
				cin >> numPlayers; // inputs the number of players 
			}
			while (decision == 4)
			{
				exit(1);
			}
			cout << endl;

			vector< BlackJackPlayer >players(numPlayers); // vector creating players 

			cout << "PLACE YOUR BET" << endl; // prompts the players to place their bet 
			cout << "Minimum: $5   Maximum: $100" << endl; // states the range of what the players can bet 
			cout << endl;

			for (int i = 0; i < numPlayers; ++i)
			{
				players[i].setId(i + 1); // sets the proper id for each player 
				players[i].displayPlayerId(); // displays' player id 
				int a;
				cin >> a; // reads in each player's bet 
				while (a < 5 || a > 100)
				{
					cout << "invalid bet. Place your bet: " << endl;
					cin >> a; // reads in each player's bet 
				}
				players[i].setBet(a); // sets each player's bet      
			}

			cout << endl;
			cout << "SHUFFLING THE DECK" << endl;

			myDeckOfCards.shuffle(); // shuffles the deck 
			myDeckOfCards.shuffle(); // shuffles the deck 

			cout << endl;
			cout << "DEALING CARDS!!" << endl; // getting ready to deal cards 

			//loop for passing out first card 
			for (int i = 0; i < numPlayers; ++i)
			{
				if (myDeckOfCards.moreCards()) // deals card if there are cards in the deck 
					players[i].hit(myDeckOfCards.dealCard());
			}

			// passing first card to computer 
			if (myDeckOfCards.moreCards())
				computer.hit(myDeckOfCards.dealCard());

			// loop for dealing second card 
			for (int i = 0; i < numPlayers; ++i)
			{
				if (myDeckOfCards.moreCards()) // deals card if there are cards in the deck 
					players[i].hit(myDeckOfCards.dealCard());
			}

			// passing second card to computer 
			if (myDeckOfCards.moreCards())
				computer.hit(myDeckOfCards.dealCard());

			//displays the cards 
			for (int i = 0; i < numPlayers; ++i) // displays players' hand 
			{
				players[i].displayPlayerId();
				players[i].displayPlayerHand();
			}

			// displays computer's hand 
			cout << "dealer's hand" << endl;
			computer.displayCompHandHidden();

			static int countBlJk = 0; // counts how many people have black jack 
			//checks if anyone has blackjack 
			for (int i = 0; i < numPlayers; ++i)
			{
				if (players[i].checkBlJk() == 21)
				{
					players[i].displayPlayerId();
					cout << "HAS BLACKJACK!!" << "\n" << endl;
					players[i].setStand();
					countBlJk++; // counts how many people have black jack 
				}
			}


			// first round 
			for (int i = 0; i < numPlayers; ++i)
			{
				if (players[i].checkBlJk() != 21)
				{
					players[i].displayPlayerId();
					players[i].displayPlayerHand();
					players[i].displayPlayerId(); // display's the player's id 
					cout << "Your turn" << endl;
					string first; // gets the option for the players 
					int fir = 0; // number option for the players 
					cout << "choose from the following options" << endl;
					cout << "Hit  Stand  DoubleDown  Surrender" << endl;
					cin >> first;
					if (first == "Hit" || first == "hit")
						fir = 1;
					else if (first == "Stand" || first == "stand")
						fir = 2;
					else if (first == "DoubleDown" || first == "doubledown")
						fir = 3;
					else if (first == "Surrender" || first == "surrender")
						fir = 4;

					// process first round 
					switch (fir)
					{
					case 1:
						if (myDeckOfCards.moreCards()) // deals card if there are cards in the deck 
						{
							players[i].hit(myDeckOfCards.dealCard());
							players[i].displayPlayerId(); // display's the player's id 
							players[i].displayPlayerHand();
							if (players[i].total() == 21)
								players[i].setStand();
						}
						break;
					case 2:
						players[i].setStand(); // indicates that the player cannot get a hit 
						players[i].displayPlayerId();
						players[i].displayPlayerHand();
						break;
					case 3:
						players[i].doubleDown();
						if (myDeckOfCards.moreCards()) // deals card if there are cards in the deck 
						{
							players[i].hit(myDeckOfCards.dealCard());
						}
						cout << "DOUBLE DOWN IS CALLED" << endl;
						players[i].setStand();
						players[i].displayPlayerId(); // display's the player's id 
						players[i].displayPlayerHand();
						break;
					case 4:
						players[i].surrender(); // clears the hand of the player and gives the player half of his/her bet 
						players[i].setStand();
						players[i].displayPlayerId(); // display's the player's id 
						cout << "surrenders" << endl;
						players[i].lose();
						break;
					}
				}
			}

			cout << "\n" << endl;

			//PROBLEM WITH THIS SWITCH 
			// other rounds 
			int breakingCheck = 0;
			for (int i = 0; i < numPlayers; ++i)
			{
				while (!players[i].stand())
				{
					if (players[i].total() < 21)
					{
						players[i].displayPlayerId();
						players[i].displayPlayerHand();
						players[i].displayPlayerId(); // display's the player's id 
						cout << "Your turn" << endl;
						string f; // gets the option for the players 
						int fi = 0; // number option for the players 
						players[i].displayPlayerHand();
						cout << "choose from the following options" << endl;
						cout << "Hit  Stand" << endl;
						cin >> f;

						if (f == "Hit" || f == "hit")
							fi = 1;
						else if (f == "Stand" || f == "stand")
							fi = 2;

						switch (fi)
						{
						case 1:
							if (myDeckOfCards.moreCards()) // deals card if there are cards in the deck 
								players[i].hit(myDeckOfCards.dealCard());
							if (players[i].total() >= 21)
							{
								players[i].setStand();
								players[i].displayPlayerId();
								players[i].displayPlayerHand();
								breakingCheck = 1;
							}

							break;
						case 2:
							players[i].setStand(); // indicates that the player cannot get a hit 
							players[i].displayPlayerId();
							players[i].displayPlayerHand();
							break;
						}
					}
					if (breakingCheck == 1)
						break;
				}
			}

			//find who wins 
			int high = 0; // value of who has the highest 
			int temp = 0; // temperorary value 
			int count = 0;
			for (int i = 0; i < numPlayers; ++i)
			{
				if (players[i].total() > temp && players[i].total() <= 21)
					high = players[i].total();
				else if (players[i].total() == temp)
					count++;
				temp = players[i].total();
			}

			for (int i = 0; i < numPlayers; ++i)
			{
				players[i].displayPlayerId();
				players[i].displayPlayerHand();
			}

			while (computer.canHit17()) // dealer keeps getting hit unitl his total is 17 or above 
				computer.hit(myDeckOfCards.dealCard());

			computer.displayCompHandAll(); // display's dealer's hand 

			//pays bet back to winner 
			for (int i = 0; i < numPlayers; ++i)
			{
				if (players[i].total() <= 21 && players[i].total() > computer.total() && computer.total() <= 21)
				{
					players[i].win();
					players[i].displayPlayerId();
					cout << "WINS!!!!" << endl;
					players[i].displayPlayerHand();
					cout << endl;
				}
				else if (/*players[i].total() == high && */players[i].total() == computer.total())
				{
					players[i].tie();
					players[i].displayPlayerId();
					cout << "\nTIED WITH THE DEALER! \n" << endl;
				}
				else if (computer.total() > 21 && players[i].total() <= 21 && players[i].total() != 0)
				{
					players[i].win();
					players[i].displayPlayerId();
					cout << "WINS!!!!" << endl;
					players[i].displayPlayerHand();
					cout << endl;
				}
				else
				{
					players[i].lose();
					players[i].displayPlayerId();
					cout << "LOSES!!!!" << endl;
					players[i].displayPlayerHand();
					cout << endl;
				}


			}

			// display's player's balance 
			for (int i = 0; i < numPlayers; ++i)
			{
				players[i].displayPlayerId();
				players[i].displayPlayerBal();
			}
			//} 
			if (countBlJk == 1)
			{
				//dealer takes hit until his cards are up to 17 
				while (computer.canHit17())
					computer.hit(myDeckOfCards.dealCard());

				computer.displayCompHandAll(); // display's dealer's hand 

				for (int i = 0; i < numPlayers; ++i)
				{
					if (players[i].total() == 21)
					{
						if (computer.total() == 21)
						{
						}
						else
						{
							players[i].displayPlayerId();
							players[i].displayPlayerHand();
							players[i].blackJack();
							cout << "balance: ";
							players[i].displayPlayerBal();
						}
					}
					else
					{
						players[i].displayPlayerId();
						players[i].displayPlayerHand();
						cout << "balance: ";
						players[i].displayPlayerBal();
					}
				}
			}
			else
			{
				for (int i = 0; i < numPlayers; ++i)
				{
					players[i].displayPlayerId();
					players[i].displayPlayerHand();
					cout << "balance: ";
					players[i].displayPlayerBal();
				}

			}
			int choice = 0;
			cout << "Play Another Round? (1 for yes 2 for no) " << endl;
			cin >> choice;
			if (choice == 1)
				decision = 2;
			else
				decision = 0;
			system("PAUSE");
		}
	}
}