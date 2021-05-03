//Here is program 8-2
// Nathan Ross
// 986418127

// This program demonstrates the binarySearch function, which
// performs a binary search on an integer array.
#include <iostream>
#include <string>
using namespace std;

// Function prototypes
void selectionSort(string[], int);
void showArray(string[], int);

int main()
{
	// Define an array with unsorted values
	const int NUM_NAMES = 20;
	string names[NUM_NAMES] = { "Collins, Bill", "Smith, Bart", "Allen, Jim",
		"Griffin, Jim", "Stamey, Marty", "Rose, Geri",
		"Taylor, Terri", "Johnson, Jill", "Allison, Jeff",
		"Looney, Joe", "Wolfe, Bill", "James, Jean",
		"Weaver, Jim", "Pore, Bob", "Rutherford, Greg",
		"Javens, Renee", "Harrison, Rose", "Setzer, Cathy",
		"Pike, Gordon", "Holland, Beth" };

	// Display the values.
	cout << "The unsorted values are\n";
	showArray(names, NUM_NAMES);

	// Sort the values.
	selectionSort(names, NUM_NAMES);

	// Display the values again.
	cout << std::endl;
	cout << "The sorted values are\n";
	showArray(names, NUM_NAMES);
	return 0;
}

//**************************************************************
// Definition of function selectionSort.                       *
// This function performs an ascending order selection sort on *
// array. size is the number of elements in the array.         *
//**************************************************************

void selectionSort(string array[], int size)
{
	int startScan, minIndex;

	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		minIndex = startScan;
		for (int index = startScan + 1; index < size; index++)
		{
			if (array[index] < array[minIndex])
				minIndex = index;
		}

		if (minIndex != startScan)
		{
			string minValue = array[minIndex];
			array[minIndex] = array[startScan];
			array[startScan] = minValue;
		}
	}
}

//**************************************************************
// Definition of function showArray.                           *
// This function displays the contents of array. size is the   *
// number of elements.                                         *
//**************************************************************

void showArray(string array[], int size)
{
	for (int count = 0; count < size; count++)
		cout << array[count].c_str() << "\n";
	cout << endl;
}