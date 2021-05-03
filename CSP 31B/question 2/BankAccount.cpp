//BankAccount.cpp

#include <sstream>
#include <iomanip>
#include "BankAccount.h"

//constructor, makes sure balance begins positive
BankAccount::BankAccount(int accountNumber, double balance)
	: accountNumber(accountNumber), balance(balance)
{
	if (balance < 0.0)
		balance = 0.0;
}

//modifies account number
void BankAccount::setAccountNumber(int accountNumber)
{
	this->accountNumber = accountNumber;
}

//gets account number
int BankAccount::getAccountNumber() const
{
	return accountNumber;
}

//gets balance
double BankAccount::getBalance() const
{
	return balance;
}

//adds amount to balance
void BankAccount::deposit(double amount)
{
	//unlike withdraw(), always succeeds
	balance += amount;
}

//returns true if the amount could be duducted from balance
bool BankAccount::withdraw(double amount)
{
	bool sufficentFunds = true;

	if (balance >= amount)
		balance -= amount;
	else
		sufficentFunds = false;

	return sufficentFunds;
}

//return the status of the account as a string
std::string BankAccount::getDisplay() const
{
	std::stringstream ss;
	ss << "Account #: " << accountNumber << std::endl;
	ss << std::showpoint << std::setprecision(2) << std::fixed;
	ss << "Balance: $" << balance << std::endl;
	return ss.str();
}