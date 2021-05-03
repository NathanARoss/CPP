//Question 2.cpp

#include <iostream> // std::cout std::cin
#include <string>   // std::string
#include <iomanip>  // std::fixed std::showpoint << std::setprecision(2)
#include "CheckAccount.h" // CheckAccount BankAccount
#include "SavingAccount.h" // SavingAccount (BankAccount)

//declare prototypes
void testBankAccount();
void testCheckAccount();
void testSavingAccount();

//test each class to prove each works as expected
int main()
{
	std::cout << std::fixed << std::setprecision(2) << std::showpoint;

	testBankAccount();
	std::cout << std::endl;

	testCheckAccount();
	std::cout << std::endl;

	testSavingAccount();
	std::cout << std::endl;

	system("pause");
	return 0;
}

//testing suite for BankAccount
void testBankAccount()
{
	BankAccount bankAccount;

	std::cout << "Default bank account settings:" << std::endl;
	std::cout << bankAccount.getDisplay();

	bankAccount.setAccountNumber(12345);
	bankAccount.deposit(50.00);
	std::cout << "Configured:" << std::endl;
	std::cout << bankAccount.getDisplay();

	std::cout << "Overwring BankAccount:" << std::endl;
	bankAccount = BankAccount(31232, 100.0);
	std::cout << "Account #: " << bankAccount.getAccountNumber() << std::endl;
	std::cout << "Balance: $" << bankAccount.getBalance() << std::endl;

	bool withdraw = bankAccount.withdraw(75.00);
	std::cout << "$75 withdraw, success: " << withdraw << std::endl;
	std::cout << "Balance: $" << bankAccount.getBalance() << std::endl;

	withdraw = bankAccount.withdraw(50.00);
	std::cout << "$50 withdraw, success: " << withdraw << std::endl;
	std::cout << "Balance: $" << bankAccount.getBalance() << std::endl;
	std::cout << std::endl;
}

//testing suite for CheckAccount
void testCheckAccount()
{
	CheckAccount checkAccount(1000, 100);

	std::cout << "CheckAccount base constuction:" << std::endl;
	std::cout << checkAccount.getDisplay();

	std::cout << "Custom configuration:" << std::endl;
	checkAccount.setInterestRate(0.06);
	checkAccount.setMinBalance(10.00);
	checkAccount.setServiceCharge(5.0);
	std::cout << "Interest rate: " << checkAccount.getInterestRate() * 100.0 << '%' << std::endl;
	std::cout << "Min balance: $" << checkAccount.getMinBalance() << std::endl;
	std::cout << "Service charge: $" << checkAccount.getServiceCharge() << std::endl;

	checkAccount.postInterest();
	std::cout << "Post interest balance: $" << checkAccount.getBalance() << std::endl;
	std::cout << "Above min balance: " << checkAccount.isAboveMinBalance() << std::endl;

	checkAccount.writeCheck(100.0);
	std::cout << "Balance after writing $100 check and paying $5 fee: $" << checkAccount.getBalance() << std::endl;
	std::cout << "Above min balance: " << checkAccount.isAboveMinBalance() << std::endl;

	checkAccount.writeCheck(0.01);
	std::cout << "Balance after withdrawing $0.01 and paying $5 fee: $" << checkAccount.getBalance() << std::endl;
	std::cout << std::endl;

}

//testing suite for SavingAccount
void testSavingAccount()
{
	SavingAccount savingAccount(1000, 100.0, 0.06);
	
	std::cout << "Full SavingAccount constructor:" << std::endl;
	std::cout << savingAccount.getDisplay();

	savingAccount.setInterestRate(0.07);
	std::cout << "New interest rate: " << savingAccount.getInterestRate() * 100.0 << '%' << std::endl;
	savingAccount.postInterest();
	std::cout << "Balance after interest payment: $" << savingAccount.getBalance() << std::endl;

	savingAccount.writeCheck(100.0);
	std::cout << "Balance after writing $100 check: $" << savingAccount.getBalance() << std::endl;

	savingAccount.withdraw(10.0);
	std::cout << "Balance after (trying to) withdraw $10: $" << savingAccount.getBalance() << std::endl;
}