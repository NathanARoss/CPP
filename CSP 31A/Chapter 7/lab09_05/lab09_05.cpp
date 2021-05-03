//Nathan Ross 986418127
#include <iostream>
#include <iomanip>

using namespace std;

const int SIZE = 5;

void getValues(int[]);  //to read  values to array
void print(const int[]);  //to print values in array
double findAverage(const int[]); //find average


int main()
{
	int arr[SIZE]; //declare the array
	double average = 0;

	getValues(arr);  //calling function getValues

	print(arr);   //call print function

	average = findAverage(arr);  //find avearge

	//write statement to print average (display 2 decimal values)
	std::cout << std::fixed << std::showpoint << std::setprecision(2);
	std::cout << std::endl << "The average is: " << average;

	cout << endl;

	return 0;
}
//ends main


//---------------------------------------------------------
//Document your function with what it is doing and pre and post conditions.
// See sample documentation below
//---------------------------------------------------------
double findAverage(const int array[])
{
	int sum = 0; //accumulator

	double average = 0;

	//implement find sum of each element in the array, and accumlate it to sum
	for (int i = 0; i < SIZE; ++i)
		sum += array[i];

	// Write statement to valuate average, and cast it correctly to double.
	average = static_cast<double>(sum) / SIZE;

	// return average
	return average;

}

//---------------------------------------------------------
// Display the contents of the argument array to the standard output. The size of the array is a global constant
// Preconditions: an integer array is passed.
// Postconditions: each value of the array is populated with an int value.
//---------------------------------------------------------
void print(const int array[])
{
	//implement code to print values in array arr passed in the parameter

	// Note that this is similar code that was in the main function in question 3.
	std::cout << "\nAll values are: ";

	for (int i = 0; i < SIZE; ++i)
		std::cout << array[i] << ' ';

	std::cout << std::endl;
}

//---------------------------------------------------------
// Function to read values to each element of array. The size of array is the global variable
// SIZE set above.
// Preconditions: an integer array is passed.
// Postconditions: each value of the array is populated with an int value.
//---------------------------------------------------------
void getValues(int array[])
{
	//This part was done in question 3.

	for (int i = 0; i<SIZE; i++) {
		cout << "\nEnter value for element " << i + 1 << " : ";
		cin >> array[i];
	}
}