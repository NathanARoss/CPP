//SavingAccount.cpp

#include <sstream>
#include <iomanip>
#include "SavingAccount.h"

//full constructor, requires interest rate to be at least 0.0
SavingAccount::SavingAccount(int accountNumber, double balance, double interestRate)
	: BankAccount(accountNumber, balance), interestRate(interestRate)
{
	if (interestRate < 0.0)
		interestRate = 0.0;
}

//modify interest rate
void SavingAccount::setInterestRate(double interestRate)
{
	this->interestRate = interestRate;
}

//get interest rate
double SavingAccount::getInterestRate() const
{
	return interestRate;
}

//calculate interest payment and deposit it
void SavingAccount::postInterest()
{
	double interestAmmount = getBalance() * interestRate;
	deposit(interestAmmount);
}

//takes money from balance, same as withdraw
bool SavingAccount::writeCheck(double amount)
{
	return BankAccount::withdraw(amount);
}

//returns if the given amount can be removed from balance
bool SavingAccount::withdraw(double amount)
{
	return BankAccount::withdraw(amount);
}

//returns state of the SavingAccount as a string
std::string SavingAccount::getDisplay() const
{
	std::stringstream ss;
	ss << BankAccount::getDisplay();
	ss << std::showpoint << std::setprecision(2) << std::fixed;
	ss << "Interest Rate: " << interestRate * 100.0 << '%' << std::endl;
	return ss.str();
}