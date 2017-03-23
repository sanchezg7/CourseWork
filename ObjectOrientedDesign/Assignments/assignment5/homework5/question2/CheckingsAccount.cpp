#include "Account.h"
#include "CheckingsAccount.h"

CheckingsAccount::CheckingsAccount(double money, double fee)
: Account(money)
{
	setFee(fee);
}

void CheckingsAccount::credit (double money)
{

	Account::credit(money);
	Account::debit(getFee());

}

void CheckingsAccount::debit (double money)
{
	bool test = Account::debit(money);

	if (test)
	{
		Account::debit(getFee());
	}
}

void CheckingsAccount::setFee(double amount)
{
	fee = amount;
}

double CheckingsAccount::getFee() const
{
	return fee;
}