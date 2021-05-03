/*
Purpose:
	Calculate an employee's total pay

Input:
	Amount of money earned each pay period

Processing:
	Set anual pay equal to pay amount times number of pay periods
	Set bonus pay equal to annual pay times bonus rate
	Set total pay equal to annual pay plus bonus pay

Output:
	Annual pay
	Bonus pay
	Total pay

Written by Nathan Ross
Last mondified 2/3/2016

COPYRIGHT 2016 (jk)
*/

//import the iostream header file before compilation
//needed for std::cout & std::cin
#include <iostream>

//import iomanip header file before compiling
//needed for std:fixed and std::setprecision
#include <iomanip>

//returns the value of the argument rounded to the nearest cent
double roundToNearestCent(const double &currency)
{
	//constant definition, cents per dollar never changes
	const double CENTS_PER_DOLLAR = 100.0;

	//process and return control of the program
	return round(currency * CENTS_PER_DOLLAR) / CENTS_PER_DOLLAR;
}

//entry point
int main() {
	//constant value definitions
	const double PAY_PERIODS = 26.0;
	const double BONUS_RATE = 0.05;

	//input earnings per pay period
	std::cout << "Enter amount earned each pay period: $";
	double payAmount;
	std::cin >> payAmount;

	//calculate total yearly pay
	double payPeriods = PAY_PERIODS;
	double annualPay = payAmount * payPeriods;
	annualPay = roundToNearestCent(annualPay);
	double bonusPay = annualPay * BONUS_RATE;
	bonusPay = roundToNearestCent(bonusPay);
	double totalPay = annualPay + bonusPay;
	//no need to round totalPay, annualPay and bonusPay do not contain sub-cent values

	//output the total annual earning along with it's components
	//fixed and setprecision(2) force cout to always print 2 decimal places after the dot
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Annual pay: $" << annualPay << std::endl;
	std::cout << "Bonus pay: $" << bonusPay << std::endl;
	std::cout << "Total pay: $" << totalPay << std::endl;

	//return success
	return EXIT_SUCCESS;
}