/*
Stock transaction program

Purpose:
	The program calculates the profit after buying a number of shares at one price,
	selling them at another, and being charged 2% commission on both transactions.

Example input and output:
	Enter share name: ROST //unused input, required by assignment
	Enter number of shares purchased: 200
	Enter share price during purchase: $5
	Enter share price during sale: $6
	
	Share purchase: $1000
	Commission on purchase: $20
	Total purchase: $1020

	Share sale: $1200
	Commission on sale: $24
	Total sale: $1176

	Profit: $156

Input:
	Share name
	Number of shares purchased
	Price per share during purchase
	Price per share during sale

Processing:
	Amount paid for shares
	Commission on amount paid
	Total amount paid
	Income for selling shares
	Commission on income from selling shares
	Total income
	Profit

Output:
	(same as processing)

Written by Nathan Ross
Last mondified 2/12/16
*/

#include <iostream> //std::cout, std::cin, std::streamsize
#include <iomanip> //std::fixed, std::showpoint, std::setprecision
#include <string> //std::string
#include <limits> //std::numeric_limits

//I do not recommend looking inside this file
//All classes are double value types with restrictions on assignment and arithmitic
#include "Unit Types.h" //unit::Amount, unit::Cost, unit::Currency

std::string promptString(std::string prompt)
{
	std::string input;
	std::cout << prompt;
	std::getline(std::cin, input);
	return input;
}

double promptDouble(std::string prompt)
{
	double input;
	std::cout << prompt;
	std::cin >> input;

	//delimit input with new lines to enforce one input per prompt
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return input;
}

int main(void)
{
	//inputs
	std::string shareName = promptString("Enter the share name: "); //unused input
	unit::Amount sharesPurchased = promptDouble("Enter number of shares purchased: ");
	unit::Cost buyPrice = promptDouble("Enter share price during purchase: $");
	unit::Cost sellPrice = promptDouble("Enter share price during sale: $");

	//correct unit conversions are guareneed and required
	//unit::Cost contains all unit conversions so it goes on the left of the *
	unit::Currency purchaseAmount = buyPrice * sharesPurchased;
	unit::Currency purchaseCommission = purchaseAmount * 0.02;
	unit::Currency totalPurchase = purchaseAmount + purchaseCommission;

	unit::Currency saleAmount = sellPrice * sharesPurchased;
	unit::Currency saleCommission = saleAmount * 0.02;
	unit::Currency totalSale = saleAmount - saleCommission;

	unit::Currency profit = totalSale - totalPurchase;

	//output formatting
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::endl; //blank line
	std::cout << "Purchase amount:\t\t$" << purchaseAmount.getValue() << std::endl;
	std::cout << "Commission on purchase:\t\t$" << purchaseCommission.getValue() << std::endl;
	std::cout << "Total purchase:\t\t\t$" << totalPurchase.getValue() << std::endl;
	std::cout << std::endl; //blank line
	std::cout << "Sale amount:\t\t\t$" << saleAmount.getValue() << std::endl;
	std::cout << "Commission on sale:\t\t$" << saleCommission.getValue() << std::endl;
	std::cout << "Total sale:\t\t\t$" << totalSale.getValue() << std::endl;
	std::cout << std::endl; //blank line
	std::cout << "Profit:\t\t\t\t$" << profit.getValue() << std::endl;

	//C++ standards say the main module returns 0 if it ends without a return statement
	//I forgot the return statement in my question 1 and 2, but they still compile
	return EXIT_SUCCESS;
}