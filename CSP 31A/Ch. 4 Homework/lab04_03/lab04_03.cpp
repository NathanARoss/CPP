//  This program will prompt for a score value (between 0 and 100)
//  and then print grade according to score: 90 to 100 is an A
// 80 to 89 is B, 70 to 79 is C, 60 to 69 is D else an F
//  Also validate invalid scores, and all done via nested if-else

//Nathan Ross

#include <iostream>

using namespace std;


int main()

{
	int score;
	char grade;

	//Add statements to prompt and read value for score
	std::cout << "Enter score (0 - 100): ";
	std::cin >> score;


	//test value of score and determine the grade by
	// implent algorithm shown below
	// if score < 0 print invalid
	// else if score > 100 print invalid
	// else if score >= 90 set grade to A
	// else if score >= 80 set grade to B
	// else if score >= 70 set grade to C
	// else if score >= 60 set grade to D
	// else set grade to F

	grade = '\0';

	if (score < 0)
		std::cout << "Invalid score. Score cannot be less than 0.";
	else if (score > 100)
		std::cout << "Invalid score. Extra credit is not supported.";
	else if (score >= 90)
		grade = 'A';
	else if (score >= 80)
		grade = 'B';
	else if (score >= 70)
		grade = 'C';
	else if (score >= 60)
		grade = 'D';
	else
		grade = 'F';


	//  Display both score and grade if a valid score was entered
	if (grade != '\0')
		std::cout << score << "% is a" << ((grade == 'A') ? "n " : " ") << grade;

	cout << endl;

	return 0;

}