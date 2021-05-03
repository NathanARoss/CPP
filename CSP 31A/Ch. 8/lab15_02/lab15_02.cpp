// Nathan Ross
// 986418127

// This program demonstrates the binarySearch function, which
// performs a binary search on an integer array.
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Function prototypes
void selectionSort(string[], const size_t);
void showArray(const string[], const size_t);
int binarySearch(const string[], const size_t, const string);

int main()
{
	// Define an array with unsorted values
	const size_t NUM_NAMES = 20;
	string names[NUM_NAMES] = { "Collins, Bill", "Smith, Bart", "Allen, Jim",
		"Griffin, Jim", "Stamey, Marty", "Rose, Geri",
		"Taylor, Terri", "Johnson, Jill", "Allison, Jeff",
		"Looney, Joe", "Wolfe, Bill", "James, Jean",
		"Weaver, Jim", "Pore, Bob", "Rutherford, Greg",
		"Javens, Renee", "Harrison, Rose", "Setzer, Cathy",
		"Pike, Gordon", "Holland, Beth" };

	size_t results;   // To hold the search results
	string empName;     // To hold an employee name

	//sort and display a list of all employees
	selectionSort(names, NUM_NAMES);
	showArray(names, NUM_NAMES);

	// Get an employee name to search for.
	cout << "Enter the employee name you wish to search for: ";
	std::getline(std::cin, empName);

	// Search for the name.
	results = binarySearch(names, NUM_NAMES, empName);

	// If results contains -1 the ID was not found.
	if (results == std::numeric_limits<size_t>::max())
		cout << "That name does not exist in the array.\n";
	else
	{
		// Otherwise results contains the subscript of
		// the specified employee ID in the array.
		cout << "That name is found at element " << results;
		cout << " in the array.\n";
	}

	system("pause");
	return 0;
}

//**************************************************************
// Definition of function selectionSort.                       *
// This function performs an ascending order selection sort on *
// array. size is the number of elements in the array.         *
//**************************************************************

void selectionSort(string array[], const size_t size)
{
	size_t startScan, minIndex;

	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		minIndex = startScan;
		for (size_t index = startScan + 1; index < size; index++)
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

void showArray(const string array[], const size_t size)
{
	for (size_t count = 0; count < size; count++)
		cout << count << ": " << array[count].c_str() << "\n";
	cout << endl;
}

int binarySearch(const string array[], const size_t size, const string name)
{
	size_t lowerBound = 0;
	size_t upperBound = size - 1;
	size_t middle = (upperBound + lowerBound) / 2;

	const size_t notFound = std::numeric_limits<size_t>::max();
	size_t foundAt = notFound;

	while (lowerBound <= upperBound)
	{
		if (name == array[middle])
		{
			foundAt = middle;
			break; //jump out of loop
		}
		else if (name < array[middle])
			upperBound = middle - 1;
		else
			lowerBound = middle + 1;

		middle = (upperBound + lowerBound) / 2;
	}

	return foundAt;
}