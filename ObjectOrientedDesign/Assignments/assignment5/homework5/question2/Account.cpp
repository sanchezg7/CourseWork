#include "Account.h"
#include <stdexcept>


Account::Account(double money)
{
	if (money >= 0.0)
	{
		balance = 0.0;
		credit(money);
	}
	else {
		cout << "Wrong initial balance, account set to $0.00 " << endl;
		balance = 0.0;
	}
}

void Account::credit(const double money)
{
	if ( money > 0)
	{
		balance = balance + money;
	}
	else{
		cout << "Cannot credit negative amount" << endl;
	}
}

bool Account::debit(const double money)
{
	if (balance >= money)
	{
		balance -= money;
		return true;
	}
	else{
		cout << "Money is greater than balance, operation not done." << endl;
		return false;
	}
}

double Account::getBalance() const
{
	return balance;
}
