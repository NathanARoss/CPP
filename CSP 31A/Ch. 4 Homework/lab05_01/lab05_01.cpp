//this program will use switch to test different values possible for nextChoice
//Write a switch statement that checks nextChoice. If 0, print "Rock". If 1, print "Paper". 
// If 2, print "Scissors". For any other value, print "Unknown". End with newline. 

//Nathan Ross


#include <iostream>
using namespace std;

int main() {
	int nextChoice = 0;

	//write statement to prompt for and read value for nextChoice
	std::cout << "Enter 0, 1, or 2: ";
	std::cin >> nextChoice;


	//Write switch statements to test for nextChoice and print values explained above.
	switch (nextChoice)
	{
	case 0:
		std::cout << "Rock";
		break;
	case 1:
		std::cout << "Paper";
		break;
	case 2:
		std::cout << "Scissors";
		break;
	default:
		std::cout << "Unknown";
	}

	//thoroughly test your program.
	std::cout << std::endl;

	return 0;
}