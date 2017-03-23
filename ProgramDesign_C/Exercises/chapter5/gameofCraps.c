//Fig. 5.14: fig05_14.c
// Simulating the game of craps.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
	
	//enumeration constants represent game status
	enum Status {CONTINUE, WON, LOST};

	int rollDice( void ); //function prototype
	
	//function main begins pormgram execution 
	int main ( void )
	{
		int sum; //sum of rolled dice
		int myPoint; //player must must this point to win
		
		enum Status gameStatus; //can contain CONTINUE, WON, or LOST
		
		//randomize random number generator using current time
		srand( time( NULL) );

		sum = rollDice(); //first roll of the dice

		//determine game status based on sum of dice
		switch ( sum ) {
			//win on first roll
			case 7: //7 is a winner
			case 11: //11 is a winner
				gameStatus = WON; //game has been won
				break;

			//lose on first roll
			case 2: //2 is a loser
			case 3: //3 is a loser
			case 12: //12 is a loser
				gameStatus = LOST; //game has been lost
				break;

			//remember point
			default:
				gameStatus = CONTINUE; //player should keep rolling
				myPoint = sum; //remember the point
				printf("Point is %d\n", myPoint);
				break; //optional
		}

		//while game is not complete 
		while (CONTINUE  == gameStatus) { //player should keep rolling
			sum = rollDice(); //roll dice again

			//determine game status
			if ( sum == myPoint) { //win by making point 
				gameStatus = WON; //game over, player won 
			}
			
			else {
				if ( 7 == sum ) { //lose by rolling 7
					gameStatus = LOST;
				}
			}
		}
		if ( WON == gameStatus) { //did the player win?
			printf("PLayer wins\n");
		}
		else {
			printf("Player loses\n");
		}
	//roll dice, calcuate sum and dsiplay results
	int rollDice ( void )
	{
		int die1;
		int die2;
		int workSum; 
		
		die1 = 1 + ( rand() % 6);
		die2 = 1 + ( rand() % 6);
		workSum = die1 + die2;

		//display results of this roll
		printf("Player rolled %d + %d = %d\n", die1, die2, workSum);
		
		return workSum;
	}

		
	
}
