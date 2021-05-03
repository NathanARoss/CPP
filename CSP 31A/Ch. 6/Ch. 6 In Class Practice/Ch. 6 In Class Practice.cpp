/*
This program get 5 scores and drop the lowest one, then calculate
and display the average

Nathan Ross
*/

#include <cstdlib>
#include <iostream>

using namespace std;

//function prototypes
double getScore();   //score has to be 0 - 100
double findLowest(double, double, double, double, double);
double calcAverage(double, double, double, double, double);
void display(double);

int main(int argc, char *argv[])
{
	//variable declaration
	double s1, s2, s3, s4, s5, avg;

	//call getScore 5 times
	s1 = getScore();
	s2 = getScore();
	s3 = getScore();
	s4 = getScore();
	s5 = getScore();

	//call the calcAverage function
	avg = calcAverage(s1, s2, s3, s4, s5);

	//call display function
	display(avg);

	system("PAUSE");
	return EXIT_SUCCESS;
}

/*
getScore function: this function displays a prompt and get a score from the keyboard
input validation is needed to make sure the score is 0-100. The function returns the score
*/

double getScore()
{
	//add your code here 
	double score;

	std::cout << "Enter a score between 0 and 100: ";
	std::cin >> score;

	while (score < 0 || score > 100)
	{
		std::cout << "Error: Score is out of range." << std::endl;
		std::cout << "Re-Enter score: ";
		std::cin >> score;
	}

	return score;
}

/*
findLowest: this function returns the lowest score among the five scores
*/
double findLowest(double a, double b, double c, double d, double f)
{
	//add your code here
	double lowestValue = a;

	if (b < lowestValue)
		lowestValue = b;

	if (c < lowestValue)
		lowestValue = c;

	if (d < lowestValue)
		lowestValue = d;

	if (f < lowestValue)
		lowestValue = f;

	return lowestValue;
}

/*
calcAverage: this function calculates and returns the average after dropping the lowest
*/
double calcAverage(double a, double b, double c, double d, double f)
{
	//call the findLowest function to get the lowest
	double lowestScore = findLowest(a, b, c, d, f);


	//calculate the average
	double total = a + b + c + d + f;
	double adjustedTotal = total - lowestScore;
	double average = adjustedTotal / 4.0;


	//return the average
	return average;
}


void display(double a)
{
	//display the avrage 
	std::cout << "The average score is " << a << "%" << std::endl;
}



