// This program gets a series of test scores and
// calculates and display the highest score.
//Nathan Ross 986418127
#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void getTestScores(double[], int);
double getHighest(const double[], int);

int main()
{
	const int SIZE = 4;      // Array size
	double testScores[SIZE], // Array of test scores
		highestScore;     // Lowest test score

	// Set up numeric output formatting.
	cout << fixed << showpoint << setprecision(1);

	// Get the test scores from the user.
	getTestScores(testScores, SIZE);

	// Get the highest test score.
	highestScore = getHighest(testScores, SIZE);

	// Display the highest.
	cout << "The highest score is : " << highestScore << ".\n";

	return 0;
}

//************************************************************
// The getTestScores function accepts an array and its size  *
// as arguments. It prompts the user to enter test scores,   *
// which are stored in the array.                            *
//************************************************************

void getTestScores(double scores[], int size)
{
	// Loop counter
	int index;

	// Get each test score.
	for (index = 0; index <= size - 1; index++)
	{
		cout << "Enter test score number "
			<< (index + 1) << ": ";
		cin >> scores[index];
	}
}

//****************************************************
// The getHighest function accepts a double array and *
// its size as arguments. The highest value in the    *
// array is returned as a double.                    *
//****************************************************

double getHighest(const double array[], int size)
{
	double highest;  // To hold the highest value

	//implement code here to return the highest value
	
	highest = array[0];
	for (int i = 1; i < size; ++i)
	{
		if (array[i] > highest)
			highest = array[i];
	}

	// Return the highest value.
	return highest;
}