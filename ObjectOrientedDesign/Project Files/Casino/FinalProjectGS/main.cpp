#include <iostream>
#include "player.h"
#include "card.h"
#include "game.h"
#include "Blackjack.h"
#include "Slots.h"
#include "Poker.h"

using namespace std;

game* gameSelectPtr = nullptr;

//int playBlackjack(Player&); //start game of blackjack return which player won the game as int
//int playSlots(Player&);
//int playPoker(Player);

int main()
{

	int choice = 0; //scan for user input in game
	Player p1(1000);	

	cout << "Welcome to the Casino! " << p1.getName() << "!" << endl;

	while ( choice != 4)
	{
		cout << "\n Enter a choice to play a certain game: "
			<< "\n1)Blackjack \n2)Slots \n3)Poker \n4)Exit" << endl;
		cin >> choice;

		//switch statement to play respective games
		switch (choice)
		{
		case 1:
			//cout << "Work in progress, Sorry!\n" << endl;

			gameSelectPtr = new Blackjack(p1);
			gameSelectPtr->start();
			delete [] gameSelectPtr;
			gameSelectPtr = nullptr;
			
			break;

		case 2:
		{
			gameSelectPtr = new Slots(p1);
			gameSelectPtr->start();
			delete gameSelectPtr;
			gameSelectPtr = nullptr;		
		}
			break;

		case 3:

			gameSelectPtr = new Poker(p1);
			gameSelectPtr->start();
			delete gameSelectPtr;
			gameSelectPtr = nullptr;

			break;
		case 4:
			cout << "Hope you had fun! Come again!" << endl;
			break;
		default:
			cout << "Choice does not exist.\n" << endl;
			cout << "\n Enter a choice to play a certain game: "
				<< "\n1)Blackjack \n2)Slots \n3)Poker \n4)Exit" << endl;
			cin >> choice;

			break;
		}

	}
	return 0;
}
