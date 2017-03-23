#include <iostream>
#include "Account.h"
using namespace std;

// function main begins program execution
int main()
{
	Account account1(50); // create Account object
	Account account2(25); // create Account object
	
	// display initial balance of each object
	cout << "account1 balance: $" << account1.getBalance() << endl;
	cout << "account2 balance: $" << account2.getBalance() << endl;
	
	int withdrawalAmount; // stores withdrawal amount read from user
	
	cout << "\nEnter withdrawal amount for account1: "; // prompt
	cin >> withdrawalAmount; // obtain user input
	
	cout << "\nattempting to subtract " << withdrawalAmount
		<< " from account1 balance\n\n";
	account1.debit(withdrawalAmount); // try to subtract from account1
	
	// display balances
	cout << "account1 balance: $" << account1.getBalance() << endl;
	cout << "account2 balance: $" << account2.getBalance() << endl;
	
	cout << "\nEnter withdrawal amount for account2: "; // prompt
	cin >> withdrawalAmount; // obtain user input
	
	cout << "\nattempting to subtract " << withdrawalAmount
		<< " from account2 balance\n\n";
	account2.debit(withdrawalAmount); // try to subtract from account2
	
	// display balances
	cout << "account1 balance: $" << account1.getBalance() << endl;
	cout << "account2 balance: $" << account2.getBalance() << endl;
} // end main