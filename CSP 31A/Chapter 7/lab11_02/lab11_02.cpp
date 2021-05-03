// This program demonstrates accepting a 2D array argument.
//Nathan Ross 986418127
#include <iostream>
#include <iomanip>
using namespace std;

// Global constants
const int NUM_COLS = 4; // Number of columns in each array
const int NUM_ROWS = 3; // Number of rows in arr

void showArray(const int[][NUM_COLS], int); // Function prototype

int main()
{
	int arr[NUM_ROWS][NUM_COLS] = {
	{ 1, 2, 3, 4 },
	{ 5, 6, 7, 8 },
	{ 9, 10, 11, 12 } };


	cout << "The content of array arr is :\n";
	showArray(arr, NUM_ROWS);
	cout << endl << endl;

	return 0;
}

//*****************************************************************
// Function Definition for showArray                              *
// The first argument is a two-dimensional int array with COLS    *
// columns. The second argument, rows, specifies the number of    *
// rows in the array. The function displays the array's contents. *
//*****************************************************************

void showArray(const int array[][NUM_COLS], int rows)
{

	//write code here to print the 2-dimensional array.

	//Ensure to print the rows and columns of numbers as shown in the array passed

	for (int row = 0; row < rows; ++row)
	{
		for (int column = 0; column < NUM_COLS; ++column)
		{
			std::cout << array[row][column] << ' ';
		}
		std::cout << std::endl;
	}

}