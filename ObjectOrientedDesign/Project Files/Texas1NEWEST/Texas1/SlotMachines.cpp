//slotMachines.cpp 

#include "slotMachines.h" 
#include <iostream> 
#include <time.h> 
#include "Player.h" 
using namespace std;

int slotMachines::balance = 1000;
//slot machine constructor 
slotMachines::slotMachines()
{
	//roll and randomize 
	rollSetColumns();

}

//slot machine destructor 
slotMachines::~slotMachines()
{

}

//instantiate the arrays 
int slotMachines::rollColumnRand[10] = { 0 };
int slotMachines::rollColumn1[10] = { 0 };
int slotMachines::rollColumn2[10] = { 0 };
int slotMachines::rollColumn3[10] = { 0 };

//play function runs slot machine. 
void slotMachines::play()
{
	cout << "Welcome to the Chill Ass Slot Machine!" << endl;
	cout << endl;
	if (balance != 0)
		Bet();
	else
	{
		cout << "You have no money!" << endl;
		return;
	}
}

//get the player's bet 
void slotMachines::Bet()
{

	//ask for the bet amount 
	cout << "Enter bet (1, 2, 5, or 10): " << endl;
	cin >> bet;

	//get the appropriate bet value 
	while (bet != 1 && bet != 2 && bet != 5 && bet != 10)
	{
		cout << "Enter bet (MUST BE 1, 2, 5, or 10): " << endl;
		cin >> bet;
	}

	//get the output of the randomized reels and show it. 
	showCombos();
}

//function to decide if player returns to lobby or keeps playing 
void slotMachines::keepPlay()
{
	//variable to decide if player plays again or not 
	int answer = 0;

	//ask if player wants to play again 
	cout << "Play Again? (1 for yes 2 for no)" << endl;
	cin >> answer;

	//yes answer continue play 
	if (answer == 1)
		Bet();

	//no answer go back to lobby 
	else if (answer == 2)
	{
		//explicitly call destructor 
		slotMachines::~slotMachines();
		//return to lobby 
		quitPlay = 1;
	}
}

//make a random reel 
void slotMachines::roll()
{
	srand(time(NULL));
	int i = 0;
	while (i < 11)
	{
		int randValue = rand() % 11;
		rollColumnRand[i] = randValue;
		i++;
	}
	int k = 0;
	while (k < 10)
	{
		k++;
	}
}

//randomize the random reel 3 times and store it in 3 different reels 
void slotMachines::rollSetColumns()
{
	roll();
	for (int k = 0; k < 10; k++)
		rollColumn1[k] = rollColumnRand[k];
	roll();
	for (int k = 0; k < 10; k++)
		rollColumn2[k] = rollColumnRand[k];
	roll();
	for (int k = 0; k < 10; k++)
		rollColumn3[k] = rollColumnRand[k];
}

//show the 3 by 3 output of the reels 
void slotMachines::showCombos()
{
	srand(time(NULL));
	rollA = rollColumn1[rand() % 10];
	rollB = rollColumn2[rand() % 10];
	rollC = rollColumn3[rand() % 10];
	rollD = rollColumn1[rand() % 10];
	rollE = rollColumn2[rand() % 10];
	rollF = rollColumn3[rand() % 10];
	rollG = rollColumn1[rand() % 10];
	rollH = rollColumn2[rand() % 10];
	rollI = rollColumn3[rand() % 10];

	//output the 3x3 randomized reel values 
	cout << rollA << " " << rollB << " " << rollC << endl;
	cout << endl;
	cout << rollD << " " << rollE << " " << rollF << endl;
	cout << endl;
	cout << rollG << " " << rollH << " " << rollI << endl;

	//variables for row and column size 
	const int ROW = 3;
	const int COLUMN = 3;


	//comparison reel in two dimensional array 
	int comparisonReelArray[ROW][COLUMN] = { { rollA, rollB, rollC }, { rollD, rollE, rollF }, { rollG, rollH, rollI } };

	//match counter to decide which multiplier to use 
	int matchCount = 0;

	//while loop to break out of if matchCount changes 
	while (matchCount == 0)
	{
		//3 middle row match 
		if (rollD == rollE && rollE == rollF)
		{
			matchCount = 3;
			break;
		}

		//2 midddle row match 
		if (rollD == rollF || rollD == rollE || rollF == rollE)
		{
			//special case 2 midddle row match for matchCount 
			matchCount = 4;
			break;
		}

		//3 symbols anywhere match 
		int matchCountA = 0;
		int matchCountB = 0;
		int matchCountC = 0;
		int matchCountD = 0;
		int matchCountE = 0;
		int matchCountF = 0;
		int matchCountG = 0;
		int matchCountH = 0;
		int matchCountI = 0;

		for (int i = 0; i < ROW; i++)
		for (int k = 0; k < COLUMN; k++)
		{
			if (rollA == comparisonReelArray[i][k])
			{
				matchCountA++;
				if (matchCountA == 3)
				{
					matchCount = matchCountA - 1;
				}
			}
			if (rollB == comparisonReelArray[i][k])
			{
				matchCountB++;
				if (matchCountB == 3)
				{
					matchCount = matchCountB - 1;
				}
			}

			if (rollC == comparisonReelArray[i][k])
			{
				matchCountC++;
				if (matchCountC == 3)
				{
					matchCount = matchCountC - 1;
				}
			}
			if (rollD == comparisonReelArray[i][k])
			{
				matchCountD++;
				if (matchCountD == 3)
				{
					matchCount = matchCountD - 1;
				}
			}
			if (rollE == comparisonReelArray[i][k])
			{
				matchCountE++;
				if (matchCountE == 3)
				{
					matchCount = matchCountE - 1;
				}
			}
			if (rollF == comparisonReelArray[i][k])
			{
				matchCountF++;
				if (matchCountF == 3)
				{
					matchCount = matchCountF - 1;
				}
			}
			if (rollG == comparisonReelArray[i][k])
			{
				matchCountG++;
				if (matchCountG == 3)
				{
					matchCount = matchCountG - 1;
				}
			}
			if (rollH == comparisonReelArray[i][k])
			{
				matchCountH++;
				if (matchCountH == 3)
				{
					matchCount = matchCountH - 1;
				}
			}

			if (rollI == comparisonReelArray[i][k])
			{
				matchCountI++;
				if (matchCountI == 3)
				{
					matchCount = matchCountI - 1;
				}
			}
		}
		if (matchCount >= 2)
		{
			matchCount = 2;
			break;
		}

		//2 symbols match anywhere 
		for (int i = 0; i < ROW; i++)
		for (int k = 0; k < COLUMN; k++)
		{
			if (rollA == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollB == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollC == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollD == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollE == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollF == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollG == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollH == comparisonReelArray[i][k])
				matchCount = 1;

			if (rollI == comparisonReelArray[i][k])
				matchCount = 1;
		}
		if (matchCount == 1 || matchCount == 0)
			break;
	}

	//check matchCount and output appropriately 
	if (matchCount == 0)
	{
		cout << "***YOU LOSE :P***" << endl;
		balance -= bet;
	}
	if (matchCount != 0)
	{
		if (matchCount == 1)
		{
			cout << "2x" << endl;
			cout << bet * 2 << endl;
			balance += bet * 2;
		}

		if (matchCount == 2)
		{
			cout << "5x" << endl;
			cout << bet * 5 << endl;
			balance += bet * 5;
		}

		if (matchCount == 3)
		{
			cout << "300x" << endl;
			cout << bet * 300 << endl;
			balance += bet * 300;

		}

		if (matchCount == 4)
		{
			cout << "30x" << endl;
			cout << bet * 30 << endl;
			balance += bet * 30;
		}
		cout << "***YOU WIN!!!!***" << endl;
		cout << "Your Balance: " << balance << endl;
	}

	//ask if player wants to keep playing 
	keepPlay();
	if (quitPlay == 1)
		return;
}