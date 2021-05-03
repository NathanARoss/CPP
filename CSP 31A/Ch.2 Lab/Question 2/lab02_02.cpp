// This program demonstrates a compile error.
// Nathan Ross

#include <iostream>
using namespace std; //forgot a semicolon here

int main()
{
	float salary = 15892.50;

	cout << endl << "Salary is : $ " << salary; //forgot the << before salary
	cout << "\\n\\n"; //this bit is weird, but is not a syntax error

	return EXIT_SUCCESS;

}