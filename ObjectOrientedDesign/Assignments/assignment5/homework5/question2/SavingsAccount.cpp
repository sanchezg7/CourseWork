#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(double money, double rate)
:Account (money)
{
	setRate(rate);
}

void SavingsAccount::setRate(double rate)
{
	interestRate = rate;
}

double SavingsAccount::calculateInterest() const
{
	return (getBalance() * interestRate);
}
