/*
Nathan Ross

This program proves I know how to use recursion by displaying a list of numbers,
calculatng the sum of squares of numbers from 1 to a given range,
and repeat a given character for the given number of repetitions

input is the range of numbers to list, the range of numbers to sum square, and
a character and the number of times to repeat it.  This ensures I do not cheat
with precomputed output or ignore input validation.
*/
#include <iostream>
#include <limits>

//recursively writes integers from 1 to range
void writeNumbers(int range);

//returns 1^2 + 2^2 + ... + range^range
int getSumSquares(int range);

//displays the given character n number of times in a row
void writeLine(char c, int repetitions);

//entry point
int main()
{
	int countRange, sumSquareRange, reps;
	char c;
	std::cout << "Enter range to count: ";
	std::cin >> countRange;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Enter range to sum square: ";
	std::cin >> sumSquareRange;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Enter character to repeat: ";
	std::cin.get(c);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Enter number of repetitions: ";
	std::cin >> reps;
	std::cout << std::endl;

	std::cout << "1-" << countRange << ": ";
	writeNumbers(countRange);
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "getSumSquare(" << sumSquareRange << ") == " << getSumSquares(sumSquareRange) << std::endl;
	std::cout << std::endl;

	std::cout << "writeLine(" << c << ", " << reps << "): ";
	writeLine(c, reps);
	std::cout << std::endl;

	system("pause");
	return 0;
}

//check if the range parameter is valid and that the base condition is not met
//if so, display from the base condition working our way back
void writeNumbers(int range)
{
	if (range > 0)
	{
		writeNumbers(range - 1);
		std::cout << range << ' ';
	}
}

//verify that the range parameter is valid, then return the current range^2
//plus the sum square for the next lower range
int getSumSquares(int range)
{
	int squaresSum = 0;

	if (range > 0)
		squaresSum = range * range + getSumSquares(range - 1);

	return squaresSum;
}

//verify that the number of repetitions is valid and not the base condition,
//then display the character and call the function again with a decremented
//number of repetitions
void writeLine(char c, int repetitions)
{
	if (repetitions > 0)
	{
		std::cout << c;
		writeLine(c, repetitions - 1);
	}
}