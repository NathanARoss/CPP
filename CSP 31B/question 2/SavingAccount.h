#pragma once
//SavingAccount.h

#include "BankAccount.h"

//extends BankAccount's functionality by adding an interest rate
//balance still cannot go beneath $0.00
class SavingAccount : public BankAccount
{
	double interestRate;

public:
	//default constructor
	SavingAccount() : BankAccount(), interestRate(0.0)
	{}

	//base class constructor
	SavingAccount(int accountNumber, double balance)
		: BankAccount(accountNumber, balance), interestRate(0.0)
	{}

	//full constructor (verify positive interest rate)
	SavingAccount(int accountNumber, double balance, double interestRate);

	void setInterestRate(double interestRate);
	double getInterestRate() const;
	void postInterest();
	bool writeCheck(double amount);
	bool withdraw(double amount);
	std::string getDisplay() const;
};