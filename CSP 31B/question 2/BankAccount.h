#pragma once
//BankAccount.h

//basis for curency tracking
//lays down basic functionality for deposits and withdraws
class BankAccount
{
	int accountNumber;
	double balance;

public:
	//default constructor
	BankAccount() : accountNumber(-1), balance(0.0)
	{}

	//full constructor (needs to make sure balance is not
	//initialized below $0.00)
	BankAccount(int accountNumber, double balance);

	void setAccountNumber(int accountNumber);
	int getAccountNumber() const;
	double getBalance() const;
	void deposit(double amount);
	bool withdraw(double amount);
	std::string getDisplay() const;
};