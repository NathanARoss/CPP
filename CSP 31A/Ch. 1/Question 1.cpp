/*
Purpose:
	Calculate a retail item's tax and total sale

Input:
	Item price and tax rate

Processing:
	Multiply the tax rate by the item price
	add tax to item price
	round total sale to the nearest cent

Output:
	Sales tax and total sale

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
int main(void) {
	//declare variables for input because cin requires that variables already exist
	//floating point data types are base 2 and inappropriate for currency
	double retailPrice, taxRate;

	//prompt the user for the retail price and tax rate
	std::cout << "Enter retail price: $";
	std::cin >> retailPrice;
	std::cout << "Enter sales tax rate: ";
	std::cin >> taxRate;

	//calculate total sale
	double salesTax = retailPrice * taxRate;
	salesTax = roundToNearestCent(salesTax);
	double totalSale = retailPrice + salesTax;

	//display the sales tax and total sale
	//fixed and setprecision(2) force cout to always print 2 decimal places after the dot
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Sales tax: $" << salesTax << std::endl;
	std::cout << "Total sale: $" << totalSale << std::endl;

	//return success
	return EXIT_SUCCESS;
}