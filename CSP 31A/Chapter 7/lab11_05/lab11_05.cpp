// This program demonstrates the vector push_back, back and pop_back member function.
//Nathan Ross 986418127
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> values;
	int num;
	int count = 0;

	// loop 3 times and read 3 numbers to vector values

	for (count = 0; count < 3; count++)
	{
		cout << "Enter number : ";
		cin >> num;
		values.push_back(num);
	}

	/*
	// Remove a value from the vector.
	num = values.back();
	cout << "\nPopping a value " << num << " from the vector...\n";
	values.pop_back();
	cout << "The size of values is now " << values.size() << endl;

	// Now remove another value from the vector.
	num = values.back();
	cout << "\nPopping a value " << num << " from the vector...\n";
	values.pop_back();
	cout << "The size of values is now " << values.size() << endl;

	// Remove the last value from the vector.
	num = values.back();
	cout << "\nPopping a value " << num << " from the vector...\n";
	values.pop_back();
	cout << "The size of values is now " << values.size() << endl;
	/**/

	while (values.size() > 0)
	{
		num = values.back();
		cout << "\nPopping a value " << num << " from the vector...\n";
		values.pop_back();
		cout << "The size of values is now " << values.size() << endl;
	}

	return 0;
}