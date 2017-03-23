#include "game.h"

game::game()
{
	//polymorphism and inheritance
	//create a game point object that is abstract
	//game pointer will perform virtual function based on derived class 
	

}

void game::bet()
{
	cout << "This should never print." << endl;
}

void game::print()
{
	cout << "This print function should overridden." << endl;
}