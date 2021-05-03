#include <iostream> //std::cout
#include <math.h> //floor
#include <iomanip> //std::fixed std::showpoint std::setprecision(2)
#include <sstream>

using namespace std;

class BankAccount {
private:
	int dollars;
	int cents;
	double interestRate;

public:
	//initilizes data with parameters
	BankAccount(int dollars, int cents, double interestRate) : dollars(dollars), cents(cents), interestRate(interestRate)
	{
	}

	//default constructor, initilizes parameters to 0
	BankAccount() : dollars(0), cents(0), interestRate(0.0)
	{
	}

	void set(int dollars, int cents, double interestRate);
	void update();
	double getBalance() const;
	double getInterestRate() const;
	void print() const;
};

//overwrite existing balance and interest rate
void BankAccount::set(int dollars, int cents, double interestRate)
{
	this->dollars = dollars;
	this->cents = cents;
	this->interestRate = interestRate;
}

//add interest payment to balance
void BankAccount::update()
{
	double balance = getBalance();
	balance += balance * interestRate;

	//round to nearest cent to prevent $1.999 from becoming $1 & 100¢
	double roundedBalance = round(balance * 100.0) / 100.0;

	double dWholeDollars = floor(roundedBalance);
	double dFractionalDollars = roundedBalance - dWholeDollars;
	double dCents = round(dFractionalDollars * 100.0); //rounding is needed again to fix floating point errors

	this->dollars = static_cast<int>(dWholeDollars);
	this->cents = static_cast<int>(dCents);
}

//converts int dollars, cents into a single double representing the whole balance
double BankAccount::getBalance() const
{
	return static_cast<double>(dollars) + static_cast<double>(cents) / 100.0;
}

//return the current interest rate
double BankAccount::getInterestRate() const
{
	return interestRate;
}

//display the balance and interest rate to std::cout
void BankAccount::print() const
{
	//output the balance to a string stream to avoid manipulating std::cout's IO
	stringstream balance;
	balance << std::fixed << std::showpoint << std::setprecision(2) << getBalance();
	std::cout << "Current balance: $" << balance.str() << std::endl;
	std::cout << "Interest rate: " << getInterestRate() * 100.0 << '%' << std::endl;
}

int main()
{
	//crate account and set balance, $100.50 at 10% interest
	BankAccount acct01(100, 50, 0.10);

	//show current balance
	acct01.print();

	//add interest payment to balance
	std::cout << "\nAdding interest payment\n\n";
	acct01.update();

	//display the balance again after adding interest payment
	acct01.print();

	system("pause");

	return 0;
}

