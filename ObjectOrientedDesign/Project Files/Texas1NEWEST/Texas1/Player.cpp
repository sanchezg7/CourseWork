#include "Player.h" 
using namespace std;
#include <iostream> 
#include <string> 

Player::Player(int bal)
{
	balance = bal; // player's balance 
}


void Player::displayPlayerId() const // display player ID 
{
	cout << "Player ";
}

double Player::getBalance() const // returns the balance of the player 
{
	return balance;
}