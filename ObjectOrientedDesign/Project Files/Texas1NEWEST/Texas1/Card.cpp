#include <iostream> 
#include <string> 
#include <array> 
#include "Card.h" 
using namespace std;

const size_t faceSize = 13;
const size_t suitSize = 4;

static array<string, faceSize > faceArray = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
static array<string, suitSize > suitArray = { "Spades", "Hearts", "Diamonds", "Clubs" };

Card::Card(int fa, int su)
{
	face = fa;
	suit = su;
}


string Card::toString()
{
	string faceSuit;
	faceSuit = faceArray[face] + " of " + suitArray[suit];
	return faceSuit;
}

/*int Card::operator+(Card a) // operator overloading Card + Card. Remember face is an index
{
int num;
if (face == 10 || face == 11 || face == 12)
{
if (a.face == 10 || a.face == 11 || a.face == 12)
num = 10 + 10;
else
{
if (a.face == 0)
{
num = 10 + 11;
}
else
num = 10 + a.face + 1;
}
}
else
{
if (face == 0 && a.face == 0)
num = 11 + 1;
else if (face == 0)
{
num = 11 + a.face + 1;
if (num > 21)
num = face + a.face + 2;
}
else
num = face + a.face + 2;
}

return num;
}*/

int Card::operator+(int a)
{
	int num;
	if (face == 10 || face == 11 || face == 12)
		num = 10 + a;
	else if (face == 0)
		num = 11 + a;
	else
		num = face + a + 1;
	return num;
}

int Card::getFaceIn() const // returns the index of the face value 
{
	return face;
}

int Card::getSuitIn() const //returns the index of suit value
{
	return suit;
}