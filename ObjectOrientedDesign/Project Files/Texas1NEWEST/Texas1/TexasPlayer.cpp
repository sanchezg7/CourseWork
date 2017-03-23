#include "TexasPlayer.h" 
#include "TexasHoldEmGame.h" 
#include <vector> 
#include <iostream> 
#include <string> 
#include <algorithm>
using namespace std;

TexasPlayer::TexasPlayer(int n, int b) : Player(b)
{
	setId(n); //player's id 
	dlr = false;
	smBl = false;
	bgBl = false;
	alIn = false;
	out = false;
	bt = 0;
}

TexasPlayer::~TexasPlayer()
{
	hand.clear();
}

void TexasPlayer::setId(int a) // function to set id 
{
	id = a;
}


int TexasPlayer::getId() const // function to get id 
{
	return id;
}

void TexasPlayer::hit(Card b) // gets card from the deck 
{
	hand.push_back(b); // puts the card in the vector 
}

void TexasPlayer::sub(int b) // removes amount from player's balance 
{
	balance -= b; // use protected member from the base class 
	bt += b;
}

int TexasPlayer::getBt()
{
	return bt;
}

void TexasPlayer::allIn()
{
	balance -= balance;
	alIn = true;
}

int TexasPlayer::balanceReturn()
{
	return balance;
}


void TexasPlayer::displayPlayerId() const // display player ID 
{
	Player::displayPlayerId();
	cout << id;
	if (dlr == true)
		cout << "  Dealer";
	if (smBl == true)
		cout << "  Small Blind";
	if (bgBl == true)
		cout << "  Big Blind";
	cout << endl;
}

void TexasPlayer::displayPlayerHand()  // display player's hand 
{
	for (size_t i = 0; i < hand.size(); ++i)
	{
		cout << hand[i].toString() << endl; // converts the card to string and displays it 
	}
	cout << "balance: " << balance << endl;
	cout << endl; // extra spacing  
}

bool TexasPlayer::dealer() const //returns true if the player is the dealer
{
	return dlr;
}

bool TexasPlayer::smallBlind() const // returns true if the player is small blind
{
	return smBl;
}

bool TexasPlayer::bigBlind() const //returns true if the player is big blind
{
	return bgBl;
}

void TexasPlayer::setDealer() //sets dlr to true
{
	dlr = true;
}
void TexasPlayer::setSmall() //sets smBl to true
{
	smBl = true;
}
void TexasPlayer::setBig() //sets bgBl to true
{
	bgBl = true;
}

void TexasPlayer::fold() // clears the hand of the player
{
	hand.clear();
}

bool TexasPlayer::checkFold() //returns true if the player has folded
{
	if (hand.size() == 0)
		return true;
	return false;
}

bool TexasPlayer::checkAllIn() //returns true if the player has gone all in
{
	return alIn;
}

void TexasPlayer::endOfRound() //makes all the conditions of the players back to zero
{
	bt = 0;
}

int TexasPlayer::match(int a) // how much the player must call before they can match what the cost is to play
{
	return a - bt;
}

void TexasPlayer::resetSmBgDlAl() //resets dealer, small and big blind and all in
{
	smBl = false;
	bgBl = false;
	dlr = false;
	alIn = false;
}

void TexasPlayer::clearHand() //clears the player's hand
{
	hand.clear();
}

void TexasPlayer::setCheckOut()
{
	out = true;
}

bool TexasPlayer::checkOut()
{
	return out;
}

int TexasPlayer::CompareHand(vector<Card> &v)
{
	int i = 0;
	int k = 0;
	while (i < 2)
	{
		if (hand[i].getFaceIn() != 0)
		{
			tempVectCards.push_back(hand[i].getFaceIn());
			handA.push_back(hand[i].getFaceIn());
		}
		i++;
	}

	while (k < 5)
	{
		if (v[k].getFaceIn() != 0)
		{
			sortedCommunity.push_back(v[k].getFaceIn());
		}
		k++;
	}

	while (sortedCommunity.size() < 5)
		sortedCommunity.push_back(13);
	while (handA.size() < 2)
		handA.push_back(13);
	int pairCount = 0;
	int morePairCount = 0;
	for (int y = 0; y < sortedCommunity.size(); y++)
	{
		if (handA[1] == handA[0])
		if (handA[1] == sortedCommunity[y])
			pairCount++;

	}
	if (handA[1] == handA[0])
		pairCount++;
	for (int i = 0; i < hand.size(); i++)
	{
		for (int y = 0; y < sortedCommunity.size(); y++)
		{
			if (sortedCommunity[y] == handA[i] && handA[0] != handA[1] && i != 1)
				pairCount++;
			if (handA[0] != handA[1] && sortedCommunity[y] == handA[1] && i != 0)
				morePairCount++;
		}
	}

	if (handA[0] != handA[1] && pairCount == 0 && morePairCount == 0)
	{
		if (handA[1] > handA[0])
			cout << handA[1] + 1 << " " << "High" << endl;
		else
			cout << handA[0] + 1 << " " << "High" << endl;
		handValComp = 1;
	}

	if ((pairCount == 1 && morePairCount == 0) || (pairCount == 1 && morePairCount == 0))
	{
		cout << "PAIR!" << endl;
		handValComp = 2;
	}
	if (pairCount == 1 && morePairCount == 1)
	{
		cout << "2 PAIR!" << endl;
		handValComp = 3;
	}
	if ((pairCount == 2 && morePairCount == 0) || (pairCount == 0 && morePairCount == 2))
	{
		cout << "3 OF A KIND!" << endl;
		handValComp = 4;
	}
	if (straight(v))
	{
		cout << "JUU HAS STRAIGHT!" << endl;
		handValComp = 5;
	}
	if (flush(v))
	{
		cout << "JUU HAS FLUSH!" << endl;
		handValComp = 6;
	}
	if ((pairCount == 2 && morePairCount == 1) || (pairCount == 1 && morePairCount == 2))
	{
		cout << "FULL HOUSE!" << endl;
		handValComp = 7;
	}
	if ((pairCount >= 3 && morePairCount == 0) || (pairCount == 0 && morePairCount >= 3))
	{
		cout << "FOUR OF A KIND!" << endl;
		handValComp = 8;
	}
	if (straightFlush(v))
	{
		cout << "JUU HAS STRAIGHT FLUSH!" << endl;
		handValComp = 9;
	}
	if (royalFlush(v))
	{
		cout << "JUU HAS ROYAL FLUSH!" << endl;
		handValComp = 10;
	}

	winHands.push_back(handValComp);
	handValComp = 0;
	handA.clear();
	sortedCommunity.clear();
	return handValComp;
}
void TexasPlayer::winner(int p)
{
	int winner = 0;
	for (int i = 0; i < winHands.size(); i++)
	{
		if (i == winHands.size() - 1)
			break;
		if (winHands[i] > winHands[i + 1])
			winner = i;
		else
			winner = i + 1;
	}
	TexasHoldEmGame money;
	winHands.clear();
	cout << p << endl;
	balance += p;
	cout << "Player " << winner + 1 << "Wins" << endl;
	cout << "Your Balance: " << balance << endl;
}
bool TexasPlayer::straight(vector <Card> &v)
{
	int i = 0;
	int k = 0;
	vector<int> royalVect = { 9, 10, 11, 12, 13 };
	while (i < 2)
	{
		if (hand[i].getFaceIn() != 0)
		{
			tempVectCards.push_back(hand[i].getFaceIn());
			handA.push_back(hand[i].getFaceIn());
		}
		i++;
	}

	while (k < 5)
	{
		if (v[k].getFaceIn() != 0)
		{
			tempVectCards.push_back(v[k].getFaceIn());
			sortedCommunity.push_back(v[k].getFaceIn());
		}
		k++;
	}
	while (tempVectCards.size() < 7)
		tempVectCards.push_back(13);
	while (sortedCommunity.size() < 5)
		sortedCommunity.push_back(13);
	while (handA.size() < 2)
		handA.push_back(13);

	sort(sortedCommunity.begin(), sortedCommunity.end());
	int sortCount = 1;

	//THIS IS FOR SEQUENTIAL COMMUNITY
	for (int y = 0; y < sortedCommunity.size(); y++)
	{
		if (y == sortedCommunity.size() - 1)
			break;
		if (sortedCommunity[y + 1] - sortedCommunity[y] == 1)
			sortCount++;
	}

	if (sortCount == 5)
	{
		for (int o = 0; o < handA.size(); o++)
		{
			for (int w = 0; w < sortedCommunity.size(); w++)
			{
				if (handA[o] == sortedCommunity[w])
				{
					royalHand = sortedCommunity;
					handA.clear();
					sortedCommunity.clear();
					return true;
				}
			}
		}
	}

	sort(tempVectCards.begin(), tempVectCards.end());
	int straightFlag1 = 1;
	int straightFlag2 = 1;
	int straightFlag3 = 1;
	for (int y = 0; y < tempVectCards.size() - 2; y++)
	{
		if (y == tempVectCards.size() - 3)
		{
			royalHand.push_back(tempVectCards[y]);
			break;
		}
		if (tempVectCards[y + 1] - tempVectCards[y] != 0)
		{
			if (tempVectCards[y + 1] - tempVectCards[y] == 1)
			{
				royalHand.push_back(tempVectCards[y]);
				straightFlag1++;
			}
		}
	}
	for (int y = 1; y < tempVectCards.size() - 1; y++)
	{

		if (y == tempVectCards.size() - 2)
		{
			royalHand.push_back(tempVectCards[y]);
			break;
		}
		if (tempVectCards[y + 1] - tempVectCards[y] != 0)
		{
			if (tempVectCards[y + 1] - tempVectCards[y] == 1)
			{
				royalHand.push_back(tempVectCards[y]);
				straightFlag2++;
			}
		}
	}
	for (int y = 2; y < tempVectCards.size(); y++)
	{
		if (y == tempVectCards.size() - 1)
		{
			royalHand.push_back(tempVectCards[y]);
			break;
		}
		if (tempVectCards[y + 1] - tempVectCards[y] != 0)
		{
			if (tempVectCards[y + 1] - tempVectCards[y] == 1)
			{
				royalHand.push_back(tempVectCards[y]);
				straightFlag3++;
			}
		}
	}
	tempVectCards.clear();
	handA.clear();
	sortedCommunity.clear();

	if (straightFlag1 == 5 || straightFlag2 == 5 || straightFlag3 == 5)
		return true;
	if (straightFlag1 != 5 && straightFlag2 != 5 && straightFlag3 != 5)
		return false;
}

bool TexasPlayer::flush(vector <Card> &v)
{
	int i = 0;
	int k = 0;
	int flushCount1 = 0;
	int flushCount2 = 0;
	int flushCount3 = 0;
	int flushCount4 = 0;
	while (i < 2)
	{
		tempVectCards.push_back(hand[i].getSuitIn());
		handA.push_back(hand[i].getSuitIn());
		i++;
	}

	while (k < 5)
	{
		tempVectCards.push_back(v[k].getSuitIn());
		sortedCommunity.push_back(v[k].getSuitIn());
		k++;
	}

	int sortFlushCount = 0;

	//THIS IS FOR FLUSHED COMMUNITY
	for (int y = 0; y < sortedCommunity.size(); y++)
	{
		if (y == sortedCommunity.size() - 1)
			break;
		if (sortedCommunity[y + 1] == sortedCommunity[y])
			sortFlushCount++;
	}

	if (sortFlushCount == 5)
	{
		for (int o = 0; o < handA.size(); o++)
		{
			if (handA[o] == sortedCommunity[0])
			{
				handA.clear();
				sortedCommunity.clear();
				return true;
			}
		}
	}
	for (int y = 0; y < tempVectCards.size(); y++)
	if (tempVectCards[y] == 0)
		flushCount1++;

	for (int y = 0; y < tempVectCards.size(); y++)
	if (tempVectCards[y] == 1)
		flushCount2++;

	for (int y = 0; y < tempVectCards.size(); y++)
	if (tempVectCards[y] == 2)
		flushCount3++;

	for (int y = 0; y < tempVectCards.size(); y++)
	if (tempVectCards[y] == 3)
		flushCount4++;
	tempVectCards.clear();
	handA.clear();
	sortedCommunity.clear();

	if (flushCount1 >= 5 || flushCount2 >= 5 || flushCount3 >= 5 || flushCount4 >= 5)
		return true;
	return false;
}

bool TexasPlayer::royalStraight(vector <Card> &v)
{
	vector<int> royalVect = { 9, 10, 11, 12, 13 };
	sort(royalHand.begin(), royalHand.end());
	if (straight(v) && royalVect == royalHand)
		return true;
	return false;
}
bool TexasPlayer::royalFlush(vector <Card> &v)
{
	if (royalStraight(v) && royalFlush(v))
		return true;
	return false;
}
bool TexasPlayer::straightFlush(vector <Card> &v)
{
	if (straight(v) && flush(v))
		return true;
}