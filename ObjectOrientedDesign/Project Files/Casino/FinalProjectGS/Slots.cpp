//Slots.cpp		Anthony Baker
//Definition of Slots game

#include <iostream>
#include <array>
#include "Slots.h"
#include "Player.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>	

using namespace std;

const char Slots::symbols[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' }; //Symbols for Reel

Slots::Slots(Player &p1)
	:playerRef(p1) //reference to Player 1
{
	for (int i = 0; i > 9; ++i)
		reel[i] = 0;			//sets reels to 0

	betAmount = 0;
}

void Slots::start()
{
	short select = 0; //used to select options
	cout << "Welcome to Slots, " << playerRef.getName() << "!\n" << endl;
	cout << "What would you like to do? (input number)"
		<< "\n1.) Play\n2.) Exit back to lobby" << endl;
	cin >> select;

	while (select != 2)
	{
		switch (select)
		{
		case 1: //Play game
			
			cout << "\nCurrent Player balance: $" << playerRef.getBalance() << "\nHow much would you like to bet?\n" << "(Enter 1, 2, 5, or 10):";
			cin >> betAmount;

			while (betAmount != 1 && betAmount != 2 && betAmount != 5 && betAmount != 10) //checks if Player enters incorrect bet
			{
				cout << betAmount << "\nInvalid bet amount, Please enter 1, 2, 5 or 10." << endl;
				cin >> betAmount;
			}

			cout << "\nBetting: $" << betAmount << endl;
			bet(betAmount, playerRef);

			cout << endl;
			cout << "\npulling lever...\n" << endl;
			outcome();

			cout << "\n\nNew player balance: $" << playerRef.getBalance() << endl;

			cout << "Play again?\n (1 = Yes, 2 = No): ";
			cin >> select;

			break;
		case 2: //exits program
			break;

		default: //Incorrect input for select. 1 to play, 2 to exit
			cout << "\nInvalid input: Please put your drink down! :)" << endl;
			cout << "What would you like to do? (input number)"
				<< "\n1.) Play\n2.) Exit back to lobby\n -" << endl;
			cin >> select;
			break;
		}
	}
}

void Slots::outcome()
{
	int winner = 0; //Dummy variable to control determining outcome

	srand((unsigned) time(NULL)); //Seeded loop ensures randomly generated numbers

	for (int a = 0; a < 9; ++a)
	{
		reel[a] = symbols[rand()%10]; //Randomly assigns a symbol to a spot on the reel
	}

	print();

	if (reel[3] == reel[4] && reel[4] == reel[5])  //If 3 items in center row are the same, player wins 300 times bet
	{
		playerRef.balance += (betAmount * 300); //Player1.addWinnings(betAmount * 300);
		cout << "\n\nJackpot! You Win!" << endl;
		winner = 4;
	}

	else if (reel[3] == reel[4] || reel[4] == reel[5] || reel[3] == reel[5]) //If 2 items in center row are the same, player wins 30 times bet
	{
		playerRef.balance += (betAmount * 30);

		//winnings(playerPtr); //Player1.addWinnings(betAmount * 30);
		cout << "\n\nTwo in the center! You Win! " << endl;
		winner = 3;
	}

	//loop to compare all array elements
	else for (int i = 0; i < 9; ++i) // "i" is used to step through first element for comparison
	{
		for (int j = 0; j < 9; ++j) //"j" is used to step through second element for comparison
		{
			if (reel[i] == reel[j] && i != j) // comparing the two values and making sure they aren't the same index
			{
				winner = 2;

				for (int k = 0; k < 9; ++k)//"k" is used to compare a third element in case the first two match
				{
					if (reel[j] == reel[k] && j != k && i != k) // comparing the two values and making sure they aren't the same index
					{
						winner = 1; //Used to determine winning amount and then ends loop
						goto end; //jump to get out of loop once a 3 of a kind is determined.
					}
				}
			}
		}
	}

end: //destination for jump
	if (winner == 1) //indicates three of one kind on reels
	{
		playerRef.balance += (betAmount * 5);
		cout << "\n\nThree of a kind on the reels! You Win!" << endl;
	}

	else if (winner == 2) //indicates two of one symbol on reels
	{
		playerRef.balance += (betAmount * 2);
		cout << "\n\n Two of a kind on the reels! You Win!\n" << endl;
	}

	else if (winner == 0)
		cout << "\n\nSorry, you lost.\n" << endl;

}



void Slots::print()
{
	for (int i = 0; i < 9; i++)
	{
		if (i == 3 || i == 6)
			cout << "\n" << endl;

		cout << "      " << reel[i];
	}

}

void Slots::bet(int b, Player& ref)
{
	int newBalance = ref.getBalance() - b;

	ref.setBalance(newBalance);

}

Slots::~Slots()
{

	cout << "Thanks for playing!" << endl;
	//pass out winnings to player
	//somehow destory the game
}