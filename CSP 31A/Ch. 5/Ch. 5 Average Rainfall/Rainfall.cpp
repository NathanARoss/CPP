/*
Purpose:
	Collect monthly rainfall over a period of 1-5 years and report average

Input:
	Number of years to test (RANDOM)
	Rainfall per month per year

Processing:
	Accumulate total rainfall
	Number of months tested
	Average rainfall

Output:
	Number of years tested (to file)
	Number of months tested (to screen)
	Total rainfall (both)
	Average monthly rainfall (both)

Written by Nathan Ross
Last modified 3-1-16
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <limits>
#include <iomanip>

const std::string MONTH_NAMES[12] = {
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
	"December",
};

void saveRainfallToFile(std::string fileName, int yearsMeasured, float totalRainfall, float monthlyRainfall);

int getRandomNumber(int min, int max);

void flushCin();

int main(void)
{
	time_t currentTime = time(NULL);
	unsigned int seed = static_cast<unsigned int>(currentTime);
	srand(seed);

	int yearsToMeasure = getRandomNumber(1, 5);

	std::cout << "Record the monthly rainfall over " << yearsToMeasure << " years." << std::endl;
	std::cout << std::endl;

	float totalRainfall = 0.0;

	for (int year = 1; year <= yearsToMeasure; ++year)
	{
		std::cout << "Enter the monthly rainful for year " << year << "." << std::endl;
		for (int month = 0; month < 12; ++month)
		{
			std::string monthName = MONTH_NAMES[month];
			float monthlyRainfall;
			std::cout << "Enter the inches of rainful during " << monthName << ": ";
			std::cin >> monthlyRainfall;
			flushCin();

			while (monthlyRainfall < 0.0)
			{
				std::cout << monthName << " cannot have less than 0 inches of rain." << std::endl;
				std::cout << "Enter the inches of rainful during " << monthName << ": ";
				std::cin >> monthlyRainfall;
				flushCin();
			}

			totalRainfall += monthlyRainfall;
		}

		std::cout << std::endl;
	}

	int monthsMeasured = yearsToMeasure * 12;
	float averageMonthlyRainfall = totalRainfall / static_cast<float>(monthsMeasured);

	//format output, force 1 decimal place after dot
	std::cout << std::fixed << std::showpoint << std::setprecision(1);
	std::cout << "Number of months: " << monthsMeasured << std::endl;
	std::cout << "Total rainfall: " << totalRainfall << (totalRainfall == 1 ? " inch" : " inches") << std::endl;
	std::cout << "Average monthly rainfall: " << averageMonthlyRainfall << (averageMonthlyRainfall == 1 ? " inch" : " inches") << std::endl;

	saveRainfallToFile("rainfall.txt", yearsToMeasure, totalRainfall, averageMonthlyRainfall);

	//pause before returning to let the user read output
	//it's not portable, but it works for this class
	system("PAUSE");
	return EXIT_SUCCESS;
}

void saveRainfallToFile(std::string fileName, int yearsMeasured, float totalRainfall, float monthlyRainfall)
{
	std::ofstream outputFile(fileName.c_str());

	if (outputFile.fail())
	{
		std::cout << "Failed to create " << fileName << std::endl;
	}
	else
	{
		//format output, force 1 decimal place after dot
		outputFile << std::fixed << std::showpoint << std::setprecision(1);

		outputFile << "Over a period of " << yearsMeasured << (yearsMeasured == 1 ? " year" : " years")
			<< ", a total of " << totalRainfall << (totalRainfall == 1 ? " inch" : " inches")
			<< " of rain fell." << std::endl;
		outputFile << "The average rainfall was " << monthlyRainfall << (monthlyRainfall == 1 ? " inch" : " inches")
			<< " per month." << std::endl;
	}
}

int getRandomNumber(int min, int max)
{
	return rand() % max + min;
}

void flushCin()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}