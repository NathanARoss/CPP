/*
Purpose:
	Perform the tasks of a slot machine

Input:
	Amount of money to bet or 0 to exit

Processing:
	Generate 3 random numbers in the range of 0-5
	Determine if any of the numbers are a match
	Determine winnings

Output
	3 words representing the random numbers generated
	The user winnings
	A message asking for the amount to bet or 0 to exit

Written by Nathan Ross
Last modified 3/6/2016
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <time.h>
#include <string>
#include <sstream>

void flushCin();

int getRandomNumber(int min, int max);

std::string getSlotsDisplay(int slot1, int slot2, int slot3);

int getMatchingSlots(int slot1, int slot2, int slot3);

double getWinnings(double betAmount, int matchingSlots);


int main(void)
{
	//seed noise so the program is not as predictable
	time_t currentTime = time(NULL);
	unsigned int seed = static_cast<unsigned int>(currentTime);
	srand(seed);

	//format std::cout
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::left;

	char playAgain;

	do
	{
		double betAmount;
		std::cout << "Enter an amount of money to bet: $";
		std::cin >> betAmount;
		flushCin();

		while (betAmount < 0.1)
		{
			std::cout << "Error: bet must be at least $0.01." << std::endl;
			std::cout << "Re-enter an amount of money to bet: $";
			std::cin >> betAmount;
			flushCin();
		}

		int slot1 = getRandomNumber(0, 5);
		int slot2 = getRandomNumber(0, 5);
		int slot3 = getRandomNumber(0, 5);

		std::cout << getSlotsDisplay(slot1, slot2, slot3) << std::endl;

		int matchingSlots = getMatchingSlots(slot1, slot2, slot3);

		double winnings = getWinnings(betAmount, matchingSlots);

		std::cout << "You won $" << winnings << (winnings < betAmount ? "." : "!") << std::endl;
		std::cout << "Play again? (Y/N): ";
		std::cin.get(playAgain);
		flushCin();
	} while (playAgain != 'n' && playAgain != 'N');

	system("PAUSE");
	return EXIT_SUCCESS;
}

void flushCin()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getRandomNumber(int min, int max)
{
	return rand() % max + min;
}

std::string getSlotsDisplay(int slot1, int slot2, int slot3)
{
	const std::string SLOT_NAMES[6] = {
		"Cherries",
		"Oranges",
		"Plums",
		"Bells",
		"Melons",
		"Bars"
	};

	std::stringstream ss;

	//draw a grid around the 3 strings
	ss << std::string(9 * 3 + 1 * 4, '-') << std::endl;
	ss << "|";
	ss << std::setw(9) << SLOT_NAMES[slot1] << '|';
	ss << std::setw(9) << SLOT_NAMES[slot2] << '|';
	ss << std::setw(9) << SLOT_NAMES[slot3] << '|' << std::endl;
	ss << std::string(9 * 3 + 1 * 4, '-');

	return ss.str();
}

int getMatchingSlots(int slot1, int slot2, int slot3)
{
	int matching = 1;

	if (slot1 == slot2)
	{
		if (slot2 == slot3)
			matching = 3;
		else
			matching = 2;
	}
	else
	{
		if (slot1 == slot3)
			matching = 2;
		else if (slot2 == slot3)
			matching = 2;
	}

	return matching;
}

double getWinnings(double betAmount, int matchingSlots)
{
	const double MATCHING_SLOTS_MULTIPLIERS[3] = {
		0.0,
		2.0,
		3.0
	};

	return betAmount * MATCHING_SLOTS_MULTIPLIERS[matchingSlots - 1];
}