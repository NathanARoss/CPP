/*
Purpose:
Input an integer array from the user and manipulate it in a few ways

Input:
Int array size
Int array members

Processing:
Allocating array memory
Copying array elements backwards
Copying elements from one array to another, setting the rest to 0
Copying elements from one array to another, offset by one element
Converting contents of array into a string

Output:
Contents of source and modified arrays

Writen by Nathan Ross
Last modified 4-13-16
*/

#include <iostream> // std::cout std::cin std::streamsize
#include <cstdlib> // EXIT_SUCCESS
#include <limits> // std::numeric_limits<T>::max()
#include <string> // std::string
#include <sstream> // std::stringstream

//delete everything in cin so further extractions wait for user input
void flushCin(void)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//attempt to parse a single user input into the designated datatype
template<typename T>
T inputType(const T errorValue)
{
	T input;
	std::cin >> input;

	if (std::cin.fail())
	{
		input = errorValue;
		std::cin.clear();
		flushCin();
	}

	return input;
}

struct IntArray
{
	int *p;
	size_t size;

	IntArray(int *p, size_t size) : p(p), size(size) {}
};

//prototypes
IntArray getSourceArray();
IntArray getReversedArray(const IntArray);
IntArray getExpandedArray(const IntArray);
IntArray getShiftedArray(const IntArray);
std::string getArrayDisplay(const IntArray);

//entry point - where all the good stuff happens
int main(void)
{
	IntArray sourceArray = getSourceArray();
	IntArray reversedArray = getReversedArray(sourceArray);
	IntArray expandedArray = getExpandedArray(sourceArray);
	IntArray shiftedArray = getShiftedArray(sourceArray);

	std::cout << "Source array: " << getArrayDisplay(sourceArray) << std::endl;
	std::cout << "Reversed array: " << getArrayDisplay(reversedArray) << std::endl;
	std::cout << "Expanded array: " << getArrayDisplay(expandedArray) << std::endl;
	std::cout << "Shifted array: " << getArrayDisplay(shiftedArray) << std::endl;

	delete[] sourceArray.p, reversedArray.p, expandedArray.p, shiftedArray.p;

	system("pause");
	return EXIT_SUCCESS;
}

//creates an array of ints, lets the user determine the size and contents
IntArray getSourceArray()
{
	std::cout << "Quantity of numbers to enter: ";
	int size = inputType<int>(-1);

	while (size <= 0)
	{
		std::cout << "Error. Enter an quantity of numbers greater than 0: ";
		size = inputType<int>(-1);
	}

	int *sourceArray = new int[size];

	for (int i = 0; i < size; ++i)
	{
		std::cout << "Enter number " << (i + 1) << ": ";

		//I do not use inputType() here because all integers are valid; an acceptable errorValue does not exist
		std::cin >> sourceArray[i];

		while (std::cin.fail())
		{
			std::cin.clear();
			flushCin();

			std::cout << "Error. Enter an integer for number " << (i + 1) << ": ";
			std::cin >> sourceArray[i];
		}

		flushCin();
	}

	return IntArray(sourceArray, size);
}

//returns a copy of the array with all elements flipped front to back
IntArray getReversedArray(const IntArray sourceArray)
{
	int *reversedArray = nullptr;

	if (sourceArray.size > 0)
	{
		reversedArray = new int[sourceArray.size];

		for (int i = 0; i < sourceArray.size; ++i)
			reversedArray[i] = sourceArray.p[sourceArray.size - i - 1];
	}
	return IntArray(reversedArray, sourceArray.size);
}

//returns a copy of the array double the size with new elements set to 0
IntArray getExpandedArray(const IntArray sourceArray)
{
	int *expandedArray = nullptr;

	if (sourceArray.size > 0)
	{
		expandedArray = new int[sourceArray.size * 2];

		//copy first half of array
		for (int i = 0; i < sourceArray.size; ++i)
			expandedArray[i] = sourceArray.p[i];

		//set the remainder of the array to 0
		for (int i = sourceArray.size; i < sourceArray.size * 2; ++i)
			expandedArray[i] = 0;
	}

	return IntArray(expandedArray, sourceArray.size * 2);
}

//returns a copy of the array shifted 1 element in the positive direction, first element set to 0
IntArray getShiftedArray(const IntArray sourceArray)
{
	int *shiftedArray = nullptr;

	if (sourceArray.size > 0)
	{
		shiftedArray = new int[sourceArray.size + 1];

		//set first element to 0
		shiftedArray[0] = 0;

		//set the remainder of the elements to the previous element in the source array
		for (int i = 0; i < sourceArray.size; ++i)
			shiftedArray[i + 1] = sourceArray.p[i];
	}

	return IntArray(shiftedArray, sourceArray.size + 1);
}

//loops through and displays all elements of an array in a single line
std::string getArrayDisplay(const IntArray sourceArray)
{
	std::stringstream ss;

	for (int i = 0; i < sourceArray.size - 1; ++i)
		ss << sourceArray.p[i] << ' ';

	ss << sourceArray.p[sourceArray.size - 1]; //no whitespace at the end of the string

	return ss.str();
}