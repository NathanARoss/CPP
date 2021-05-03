//  This program will prompt for a score value (between 0 and 100)
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


	//test value of score for Pass or Fail
	if (score >= 50)
	{
		cout << "\nPass.";
		cout << "\nYour score is " << score << ".";
	}
	else
	{
		cout << "\nFail.";
		cout << "\nYour score is " << score << ".";
	}

	cout << endl;

	return 0;

}