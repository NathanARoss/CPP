/*
Purpose:
	Calculate the amount of quarterly payments for a senior owned house of a given value at a given property tax rate

Input:
	House value
	Property tax rate

Processing:
	remainingAsessedValue = houseValue - $5000
	propertyTaxRate = (cost per $100) / 100
	annualPropertyTax = remainingAssessedValue * propertyTaxRate
	quarterlyTaxBill = annualPropertyTax * (1.0 / 4.0)

Output:
	Annual property tax
	Quarterly tax bill

Written by Nathan Ross
Last modified 2/12/16
*/

#include <iostream> //std::cin, std::cout
#include <iomanip> //std::fixed, std::showpoint, std::setprecision
#include <limits> //std::numeric_limits
#include <string> //std::string
#include <algorithm> //std::max

double promptDouble(std::string prompt)
{
	double input;
	std::cout << prompt;
	std::cin >> input;

	//only recieve one input per prompt
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return input;
}

int main(void)
{
	const double SENIOR_HOMEOWNER_EXEMPTION = 5000;

	double assessedHomeValue = promptDouble("Enter assessed value of the house: $");
	double propertyTaxRate = promptDouble("Enter property tax rate for each $100 of assessed value: $") * (1.0 / 100.0);

	double remainingHomeValue = std::max(0.0, assessedHomeValue - SENIOR_HOMEOWNER_EXEMPTION);
	double annualPropertyTax = remainingHomeValue * propertyTaxRate;
	double quarterlyTaxBill = annualPropertyTax * (1.0 / 4.0);

	//output formatting
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::endl; //blank line
	std::cout << "Annual property tax:\t\t$" << annualPropertyTax << std::endl;
	std::cout << "Quarterly tax bill:\t\t$" << quarterlyTaxBill << std::endl;
}