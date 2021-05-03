//Nathan Ross 986418127
#include <iostream>

using namespace std;

const int SIZE = 5;

int main()
{
	int arr[SIZE]; //declare the array

	//Entries of array elements is now done in a loop
	for (int i = 0; i<SIZE; i++) {
		cout << "\nEnter value for element " << i + 1 << " : ";
		cin >> arr[i];
	}

	//write a for-loop to display all elements of array
	//and space it out each value with a space.
	// WHICH YOU ALREADY DONE ABOVE.
	std::cout << "\nAll values are: ";
	for (const int& i : arr)
		std::cout << i << ' ';

	cout << endl;

	return 0;
}