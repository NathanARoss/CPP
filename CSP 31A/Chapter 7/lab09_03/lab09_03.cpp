//Nathan Ross 986418127
#include <iostream>

using namespace std;

const int SIZE = 5;

void getValues(int[]);  //to read  values to array

int main()
{
	int arr[SIZE]; //declare the array

	getValues(arr);  //calling function getValues

	//write a for-loop to display all elements of array
	//and space it out each value with a space.
	// WHICH YOU ALREADY DONE ABOVE.
	std::cout << "\nAll values are: ";
	for (const int& i : arr)
		std::cout << i << ' ';

	cout << endl;

	return 0;
}


void getValues(int array[])
{
	//implement code to read values to array arr passed in the parameter

	// Note that this is similar code that was in the main function in question 2.
	// That is, move the code to this function, and make all names consistent
	for (int i = 0; i<SIZE; i++) {
		cout << "\nEnter value for element " << i + 1 << " : ";
		cin >> array[i];
	}
}