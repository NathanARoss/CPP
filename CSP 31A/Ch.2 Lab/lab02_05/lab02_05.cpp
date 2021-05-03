//  This program demonstrates the use of characters and strings
//  Nathan Ross

#include <iostream> //std::cout
#include <string> //std::string

int main()
{
	char grade;
	std::string name;
	float score;

	//  Assign a grade of 'A' to varable grade
	grade = 'A';
	//  Assign your name (first and last) to variable name
	name = "Nathan Ross";
	//  Assign 92 to variable score
	score = 92.0f;

	// Display Name: then followed by your name in one line
	std::cout << "Name: " << name << std::endl;
	// Display Score : then followed by your score of 92 
	std::cout << "Score: " << score << std::endl;
	// Also display Grade: followed by grade of A on the same line.
	std::cout << "Grade: " << grade << std::endl;

	return EXIT_SUCCESS;

}