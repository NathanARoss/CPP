#pragma once
//CheckAccount.h

#include "BankAccount.h"

//extends functionality of SavingAccount
//adds minimum balance and fees for withdrawing when beneath it
class CheckAccount : public BankAccount
{
	double interestRate;
	double minBalance;
	double serviceCharge;

	void processServiceFee();

public:
	//default constructor
	CheckAccount() : BankAccount(), interestRate(0.0), minBalance(0.0), serviceCharge(0.0)
	{}

	//base class only constructor
	CheckAccount(int accountNumber, double balance)
		: BankAccount(accountNumber, balance), interestRate(0.0), minBalance(0.0), serviceCharge(0.0)
	{}

	//full constructor (all values must be >= 0)
	CheckAccount(int accountNumber, double balance, double interestRate, double minBalance, double serviceCharge);

	void setInterestRate(double interestRate);
	double getInterestRate() const;

	void setMinBalance(double minBalance);
	double getMinBalance() const;

	void setServiceCharge(double serviceCharge);
	double getServiceCharge() const;

	void postInterest();
	bool isAboveMinBalance() const;
	bool writeCheck(double amount);
	bool withdraw(double amount);

	std::string getDisplay() const;
};