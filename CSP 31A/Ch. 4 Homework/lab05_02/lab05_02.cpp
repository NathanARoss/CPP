//program will compare 2 string values n alphabetical order. 
// Assume the strings are lowercase. End with newline. 
// Sample output:  // capes rabbits

//Nathan Ross


#include <iostream>
#include <string>
#include <limits>

int main() {
	std::string firstString;
	std::string secondString;

	//prompt for and read value for firstString
	std::cout << "Enter a lowercase word: ";
	std::cin >> firstString;

	//ignore all input before a newline to force one input per prompt
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	//prompt for and read value for secondString
	std::cout << "Enter another lowercase word: ";
	std::cin >> secondString;


	//Compare the 2 stings and then 
	// print the two string in alphabetical order.

	std::cout << "In alphabetical order: ";

	if (firstString < secondString)
		std::cout << firstString << " " << secondString;
	else
		std::cout << secondString << " " << firstString;

	std::cout << std::endl;

	return 0;
}