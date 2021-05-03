//Nathan Ross 986418127
#include <iostream>

using namespace std;

const int SIZE = 3;

int main()
{
	int arr[SIZE]; //declare the array

	//prompt for an element then put it in 1st element of array (index 0)
	// This is done below
	cout << "\nEnter value : ";
	cin >> arr[0];

	//prompt for an element then put it in 2nd element of array (index 1)
	cout << "\nEnter another value : ";
	cin >> arr[1];

	//prompt for an element then put it in 3rd element of array (index 2)
	cout << "\nEnter one last value : ";
	cin >> arr[2];

	//write a for-loop to display all elements of array
	//and space it out each value with a space.
	std::cout << "\nAll values are: ";
	for (const int& i : arr)
		std::cout << i << ' ';

	cout << endl;

	return 0;
}