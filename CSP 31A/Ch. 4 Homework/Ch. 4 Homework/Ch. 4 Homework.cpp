/*
Purpose:
	Calculate the monthly cost for internet service
	Tell the user how much they would save by switching to other plans

Input:
	Package letter
	Month of billing
	Hours of usage for the given month

Processing
	Validate package letter, month name, and hours of usage
	Calculate monthly service cost
	Calculate potential savings by switching to other packages

Output:
	Monthly service cost
	Potential savings by switching to other packages

Written by Nathan Ross
Last modified 2/21/2016
*/

#include <iostream> //std::cout std::cin
#include <iomanip> //std::setw std::setprecision std::showpoint std::fixed
#include <string> //std::string
#include <sstream> //std::stringstream
#include <locale> //std::toupper

#include <stdint.h> //uint16_t
#include <limits> //std::numeric_limits<>::max()
#include <cstdlib> //EXIT_SUCCESS
#include <algorithm> //std::max

const int8_t DAYS_PER_MONTH[12]{
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};

const double PACKAGE_MONTHLY_COST[3]{
	9.95,
	13.95,
	29.99
};

const double PACKAGE_HOURLY_COST[3]{
	2.00,
	1.00,
	0.00
};

const int16_t PACKAGE_HOURS[3]{
	10,
	20,
	std::numeric_limits<int16_t>::max()
};

const int HOURS_PER_DAY = 24;

//player input is compared to abbrevations of month names so users do not need to spell names correctly
const std::string MONTH_ABBREVIATIONS[12]{
	"JAN",
	"FEB",
	"MAR",
	"APR",
	"MAY",
	"JUN",
	"JUL",
	"AUG",
	"SEP",
	"OCT",
	"NOV",
	"DEC"
};

const std::string MONTH_FULL_NAMES[12]{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};


char promptUppercaseChar(std::string message)
{
	std::cout << message;

	char input;
	std::cin.get(input);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::locale loc;
	input = std::toupper(input, loc);

	return input;
}

std::string promptUppercaseString(std::string message)
{
	std::cout << message;

	std::string input;
	std::getline(std::cin, input);

	std::locale loc;
	int length = input.length();
	for (int i = 0; i < length; ++i)
	{
		input[i] = std::toupper(input[i], loc);
	}

	return input;
}

int getMonthIndex(std::string month)
{
	int index = -1;

	for (int i = 0; i < 12; ++i)
	{
		//check if the user input contains the abbreviation of a month
		if (month.find(MONTH_ABBREVIATIONS[i]) != std::string::npos)
		{
			index = i;
			break;
		}
	}

	return index;
}

std::string getPackageInformation()
{
	std::stringstream ss;
	//currency formatting
	//show decimal place, show fixed point, show 2 numbers past decimal place, allign to the left
	ss << std::showpoint << std::fixed << std::setprecision(2) << std::left;

	ss << "+---------+--------------+-----------------+--------------------------+" << std::endl;
	ss << "| Package | Monthly cost | Hours of access | Cost per additional hour |" << std::endl;
	ss << "+---------+--------------+-----------------+--------------------------+" << std::endl;

	//display information from constant arrays to guarantee information displayed and used for processing are identical
	for (int i = 0; i < 3; ++i)
	{
		ss << "| " << std::setw(8) << static_cast<char>(static_cast<int>('A') + i) << "|";
		ss << " $" << std::setw(12) << PACKAGE_MONTHLY_COST[i] << "|";

		if (PACKAGE_HOURLY_COST[i] < 0.01)
		{
			ss << std::setw(17) << " Unlimited" << "|";
			ss << std::setw(26) << " Free" << "|";
		}
		else
		{
			ss << " " << std::setw(16) << PACKAGE_HOURS[i] << "|";
			ss << " $" << std::setw(24) << PACKAGE_HOURLY_COST[i] << "|";
		}

		ss << std::endl;
	}

	ss << "+---------+--------------+-----------------+--------------------------+" << std::endl;
	ss << std::endl;

	return ss.str();
}


int main(void)
{
	//determine which package the user has selected and convert it to an array subscript
	std::cout << getPackageInformation();
	char paymentPlan = promptUppercaseChar("Enter the letter of your payment plan: ");

	//verify that the user entered a valid package
	while (paymentPlan < 'A' || paymentPlan > 'C')
		paymentPlan = promptUppercaseChar("The payment plan must be A, B, or C: ");

	int planIndex = static_cast<int>(paymentPlan) - static_cast<int>('A');


	//determine which month the user is being billed for and convert it to an array subscript
	std::string month = promptUppercaseString("Enter month of billing: ");
	int monthIndex = getMonthIndex(month);

	//verify that the user entered a valid month
	//getMonthIndex returns -1 during failure, but testing if monthIndex is in the range 0 - 11 inclusive is more portable
	while (monthIndex < 0 || monthIndex > 11)
	{
		std::string month = promptUppercaseString("Month not recognized. Try again: ");
		monthIndex = getMonthIndex(month);
	}

	//determine the number of hours the service is used for the given month
	int hoursUsage;
	std::cout << "Enter hours of usage for " << MONTH_FULL_NAMES[monthIndex] << ": ";
	std::cin >> hoursUsage;

	//disregard all input before a newline to force one input per prompt
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//verify that the hours of usage do not exceed the hours in the month of billing
	const int HOURS_THIS_MONTH = static_cast<int>(DAYS_PER_MONTH[monthIndex]) * HOURS_PER_DAY;
	while (hoursUsage > HOURS_THIS_MONTH)
	{
		std::cout << MONTH_FULL_NAMES[monthIndex] << " only has " << HOURS_THIS_MONTH << " hours." << std::endl;
		std::cout << "Enter hours of usage less than or equal to " << HOURS_THIS_MONTH << ": ";
		std::cin >> hoursUsage;

		//disregard all input before a newline to force one input per prompt
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	//calculate and display the total cost for the given month of service
	int additionalHours = std::max(0, hoursUsage - PACKAGE_HOURS[planIndex]);
	double overages = additionalHours * PACKAGE_HOURLY_COST[planIndex];
	double totalCost = PACKAGE_MONTHLY_COST[planIndex] + overages;

	std::cout << "The total cost is $" << totalCost << std::endl;

	//only compare the user's current cost with higher cost plans
	//we do not want to promote a smaller plan
	for (int i = planIndex + 1; i < 3; ++i)
	{
		int potentialAdditionalHours = std::max(0, hoursUsage - PACKAGE_HOURS[i]);
		double potentialOverages = potentialAdditionalHours * PACKAGE_HOURLY_COST[i];
		double potentialTotalCost = PACKAGE_MONTHLY_COST[i] + potentialOverages;

		if (potentialTotalCost < totalCost)
		{
			std::cout << "You could save $" << (totalCost - potentialTotalCost) << " by switching to package ";
			std::cout << static_cast<char>( static_cast<int>('A') + i ) << std::endl;
		}
	}

	return EXIT_SUCCESS;
}