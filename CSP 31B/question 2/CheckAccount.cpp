//CheckAccount.cpp

#include <sstream>
#include <iomanip>
#include "CheckAccount.h"

//full constructor, verifies all money related values are at least 0
CheckAccount::CheckAccount(int accountNumber, double balance, double interestRate, double minBalance, double serviceCharge)
	: BankAccount(accountNumber, balance), interestRate(interestRate), minBalance(minBalance), serviceCharge(serviceCharge)
{
	if (interestRate < 0.0)
		interestRate = 0.0;

	if (minBalance < 0.0)
		minBalance = 0.0;

	if (serviceCharge < 0.0)
		serviceCharge = 0.0;
}

//after a withdraw, apply service fee if balance is below min balance
//if the whole fee cannot be paid, take what is available
void CheckAccount::processServiceFee()
{
	if (!isAboveMinBalance())
	{
		//charge fee or remainder of balance
		double fee = __min(serviceCharge, getBalance());
		BankAccount::withdraw(fee);
	}
}

//modify interest rate, added to balance during postInterest()
void CheckAccount::setInterestRate(double interestRate)
{
	this->interestRate = interestRate;
}

//get interest rate, added to balance during postInterest()
double CheckAccount::getInterestRate() const
{
	return interestRate;
}

//set minimum balance, below applies service fee
void CheckAccount::setMinBalance(double minBalance)
{
	this->minBalance = minBalance;
}

//get minimum balance, below applies service fee
double CheckAccount::getMinBalance() const
{
	return minBalance;
}

//set service charge to charge when balance falls too low
void CheckAccount::setServiceCharge(double serviceCharge)
{
	this->serviceCharge = serviceCharge;
}

//return fee to charge when balance drops
double CheckAccount::getServiceCharge() const
{
	return serviceCharge;
}

//calculate and deposit interest payment 
void CheckAccount::postInterest()
{
	double interestAmount = getBalance() * interestRate;
	deposit(interestAmount);
}

//return if balance is above threshhold for service fees
bool CheckAccount::isAboveMinBalance() const
{
	return (getBalance() > minBalance);
}

//as far as I can tell, writing checks and withdraws are the same
bool CheckAccount::writeCheck(double amount)
{
	return withdraw(amount);
}

//withdraw money, check if service fees should be charged
bool CheckAccount::withdraw(double amount)
{
	bool success = BankAccount::withdraw(amount);

	//potentially charge a service fee after successful withdraw
	if (success)
		processServiceFee();

	return success;
}

//returns info about CheckAccount as a string
std::string CheckAccount::getDisplay() const
{
	std::stringstream ss;
	ss << BankAccount::getDisplay();
	ss << std::showpoint << std::setprecision(2) << std::fixed;
	ss << "Interest Rate: " << interestRate * 100.0 << '%' << std::endl;
	ss << "Min Balance: $" << minBalance << std::endl;
	ss << "Service Charge: $" << serviceCharge << std::endl;
	return ss.str();
}