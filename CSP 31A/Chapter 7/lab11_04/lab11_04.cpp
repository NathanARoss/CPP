//Program to count occurence of vowels
//Nathan Ross 986418127
#include <iostream>
#include <iomanip>

using namespace std;
const int SIZE = 5;

void print(const char[], const int[], const int); //print array
int main()
{
	char ch;
	int letterCount[SIZE] = { 0 };
	//array to count vowels, with index 0 for count of a's,
	// index 1 for count of b's and so on.

	cout << "\nEnter a character : ";
	cin >> ch;

	//a simple loop to trap only the indicated characters
	while ((ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e'))
	{

		//add code here to test if it is an a, then increment position 0
		//of array, if it is a b, then increment position 1, and so on.

		//Either you use a if-elseif statements or switch.
		//on second thought, do it all in one statement

		++letterCount[ch - 'a'];

		cout << ch << " ";
		cout << "\nEnter a character : ";
		cin >> ch;
	}

	const char letters[5] = { 'a', 'b', 'c', 'd', 'e' };
	print(letters, letterCount, SIZE);
	//print count of characters.

	cout << endl;
	return 0;
}

//*****************************************************************
// Function Definition for print                                  *
// The first argument is a 1-dimensional int array                *
// The second argumentis the size of the array                    *
// The function displays the array's contents.                    *
//*****************************************************************
void print(const char letters[], const int letterCount[], const int size)
{

	// write code to print values in the array letterCount
	// and have a space to separate each values. You can also use setw() function
	// if you want to.

	std::cout << std::endl;

	for (int i = 0; i < size; ++i)
	{
		std::cout << letters[i] << " was entered " << letterCount[i] << " times\n";
	}

	std::cout << std::endl;
}