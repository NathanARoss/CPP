/*
Purpose:
	Calculate the total sale after state and county sale taxes

Input:
	Amount of purchase

Processing:
	State sales tax
	County sales tax
	Total sales tax
	Total of the sale

Output:
	Amount of purchase
	State sales tax
	County sales tax
	Total sales tax
	Total of sale

Written by Nathan Ross
Last modified 2/12/16
*/

#include <iostream> //std::cin, std::cout
#include <iomanip> //std::fixed, std::showpoint, std::setprecision
#include <limits> //std::numeric_limits
#include <string> //std::string

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
	//constants
	const double STATE_SALES_TAX_RATE = 0.04;
	const double COUNTY_SALES_TAX_RATE = 0.02;

	//input
	double amountOfPurchase = promptDouble("Enter amount of purchase: $");

	//processing
	double stateSalesTax = amountOfPurchase * STATE_SALES_TAX_RATE;
	double countySalesTax = amountOfPurchase * COUNTY_SALES_TAX_RATE;
	double totalSalesTax = stateSalesTax + countySalesTax;
	double totalOfPurchase = amountOfPurchase + totalSalesTax;

	//output formatting
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::endl;
	std::cout << "Amount of purchase:\t\t$" << amountOfPurchase << std::endl;
	std::cout << "State sales tax:\t\t$" << stateSalesTax << std::endl;
	std::cout << "County sales tax:\t\t$" << countySalesTax << std::endl;
	std::cout << "Total sales tax:\t\t$" << totalSalesTax << std::endl;
	std::cout << "Total of purchase:\t\t$" << totalOfPurchase << std::endl;
}