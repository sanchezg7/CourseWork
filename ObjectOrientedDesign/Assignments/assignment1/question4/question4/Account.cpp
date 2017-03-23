#include <iostream>
#include "Account.h"
using namespace std;

	Account::Account(double amount)
	{
		if (amount >= 0)
		{
			balance = amount;
		}
		else {
			balance = 0;
			cout << "Invalid specified amount, balance set to 0." << endl;
		}
	}
	void Account::credit(double amount) //adds to account balance
	{
		balance += abs(amount);
	}
	void Account::debit(double amount) //withdraws from account balance
	{
		if (amount > balance)
		{
			cout << "Debit amount exceeded account balance." << endl;
			return;
		}
		else {
			balance -= abs(amount);
		}
	}
	double Account::getBalance()
	{
		return balance;
	}