#include <iostream>
#include <cmath>
#include "RationalNumber.h"

//constructor
RationalNumber::RationalNumber(int num, int denom)
{
	numerator = num;
	denominator = denom;
	
	while(denom == 0)
	{
		
		cout << denom << " Enter a valid denominator (denominator was equal to 0)" << endl;
		cin >> denom;
	}
	
	//make sure fraction is in reduced form when the object is made
	reduceFrac(*this);
}

//this function finds the greatest common divisor used for reducing fractions
int RationalNumber::gcd(int a, int b)
{
	if (a == 0 && b == 0) 
	{
		cout << "A or B was equal to 0, exiting." << endl;
		exit(1);
	}
	int aa = abs(a);
	int bb = abs(b);
	if (aa == 0)
	{
		return bb;
	}
	if (bb == 0)
	{
		return aa;
	}
	return gcd(bb, aa%bb);
}

//uses function gcd to then divide out the fraction to its simplest form
void RationalNumber::reduceFrac(RationalNumber &frac)
{
	int tempGCD = gcd(frac.numerator, frac.denominator);
	frac.numerator /= tempGCD;
	frac.denominator /= tempGCD;

	if(frac.denominator < 0) //adjust signs if fraction has negative denominator
	{
		frac.denominator *= -1;
		frac.numerator *= -1;
	}
}

//prints only whole number if the denominator is equal to 1, or prints in fraction format
void RationalNumber::printRational()
{
	if(denominator == 1)
	{
		cout << numerator;
	}
	else {
		cout << numerator << "/" << denominator;
	}
}

//operator converts rational numbers to like terms and adds them
RationalNumber RationalNumber::operator+(RationalNumber &frac2)
{
	
	int newDenom = (denominator * frac2.denominator);
	int newNumer = ((frac2.denominator * numerator) + (denominator * frac2.numerator));
	
	//rational number is reduced in the constructor
	//returns temporary object values
	return RationalNumber((newNumer), (newDenom));
}

RationalNumber RationalNumber::operator-(RationalNumber &frac2)
{
	int newDenom = (denominator * frac2.denominator);
	int newNumer = ((frac2.denominator * numerator) - (denominator * frac2.numerator));
	//return temp object
	return RationalNumber((newNumer), (newDenom));
}

//multiplies straight across
RationalNumber RationalNumber::operator*(RationalNumber &frac2)
{
	return RationalNumber((numerator*frac2.numerator), (denominator*frac2.denominator));
}

//flips the second rational number and multiplies it to the first
RationalNumber RationalNumber::operator/(RationalNumber &frac2)
{
	return RationalNumber((numerator*frac2.denominator), (denominator*frac2.numerator));
}


bool RationalNumber::operator<(RationalNumber &op2)
{
	double first = ((double)numerator / denominator);
	double second = ((double)op2.numerator / op2.denominator);

	if (first < second)
	{
		return true;
	}
	else {
		return false;
	}
}

bool RationalNumber::operator<=(RationalNumber &op2)
{
	double first = ((double)numerator / denominator);
	double second = ((double)op2.numerator / op2.denominator);

	if (first <= second)
	{
		return true;
	}
	else {
		return false;
	}
}

bool RationalNumber::operator>(RationalNumber &op2)
{
	double first = ((double)numerator / denominator);
	double second = ((double)op2.numerator / op2.denominator);

	if (first > second)
	{
		return true;
	}
	else {
		return false;
	}
}

bool RationalNumber::operator>=(RationalNumber &op2)
{
	double first = ((double)numerator / denominator);
	double second = ((double)op2.numerator / op2.denominator);

	if (first >= second)
	{
		return true;
	}
	else {
		return false;
	}
}

bool RationalNumber::operator==(RationalNumber &op2)
{
	double first = ((double)numerator / denominator);
	double second = ((double)op2.numerator / op2.denominator);

	if (first == second)
	{
		return true;
	}
	else {
		return false;
	}
}

bool RationalNumber::operator!=(RationalNumber &op2)
{
	double first = ((double)numerator / denominator);
	double second = ((double)op2.numerator / op2.denominator);

	if (first != second)
	{
		return true;
	}
	else {
		return false;
	}
}