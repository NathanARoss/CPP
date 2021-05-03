// This program will prompt for a score value(between 0 and 100)
//  and then print "PASS" if score is >= 50 othewise print FAIL

//Nathan Ross

#include <iostream>

using namespace std;


int main()
{
	int score;

	//Add statements to prompt and read value for score
	std::cout << "Enter score: ";
	std::cin >> score;


	// Add a test to show that if score > 100
	// then print invalid score
	if (score > 100 || score < 0)
		std::cout << "Invalid score";
	else if (score >= 50)
		std::cout << "Pass";
	else
		std::cout << "Fail";

	// Also test if score < 0 then
	// print invalid score also

	//test value of score for Pass or Fail
	// test score >= 50 then pass, which you done above
	// else it is a fail

	cout << endl;

	return 0;

}