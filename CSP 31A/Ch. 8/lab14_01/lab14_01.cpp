// Program to calculate wages for a number of employees
// after entering the number of hours worked and
// rate of pay for each employee.

// Nathan Ross
// 986418127

#include <iostream>
#include <iomanip>
using namespace std;

// Constant for the array size.
const int ARRAY_SIZE = 4;

// Function Prototypes
void getEmployeeInfo(long[], int[], double[], double[], int);

int main()
{
	// Array of employee ID numbers
	long empId[ARRAY_SIZE] = { 5658845, 4520125, 7895122, 8777541 };

	// Array to hold the hours worked for each employee
	int hours[ARRAY_SIZE] = { 0 };

	// Array to hold the hourly pay rate for each employee
	double payRate[ARRAY_SIZE] = { 0 };

	// Array to hold the gross wages for each employee
	double wages[ARRAY_SIZE] = { 0 };

	// Get the employee payroll information and store
	// it in the arrays.
	getEmployeeInfo(empId, hours, payRate, wages, ARRAY_SIZE);

	// Display the payroll information.
	//displayWages(empId, wages, ARRAY_SIZE);

	// Set up the numeric output formatting.
	cout << fixed << showpoint << setprecision(2) << endl;

	// Display the header.
	cout << "----------------------------\n";
	cout << "Employee               Wages\n";
	cout << "----------------------------\n\n";

	// Display each employee's pay.
	for (int count = 0; count < ARRAY_SIZE; count++)
	{
		cout << "Employee #" << empId[count] << "   $";
		cout << setw(7) << wages[count] << endl << endl;
	}

	return 0;
}

// ********************************************************
// The getEmployeeInfo function receives four parallel    *
// arrays as arguments. The 1st array contains employee   *
// IDs to be displayed in prompts. It asks for input and  *
// stores hours worked and pay rate information in the    *
// 2nd and 3rd arrays. This information is used to        *
// calculate gross pay, which it stores in the 4th array. *
// ********************************************************
void getEmployeeInfo(long emp[], int hrs[], double rate[],
	double pay[], int size)
{
	cout << "Enter the requested information "
		<< "for each employee.\n";

	// Get the information for each employee.
	for (int count = 0; count < size; count++)
	{
		cout << "\nEmployee #: " << emp[count] << "\t";

		// Get this employee's hours worked.
		cout << "Hours worked: ";
		cin >> hrs[count];

		// Validate hours worked.
		while (hrs < 0)
		{
			cout << "\nHours worked must be 0 or more. "
				<< "Please re-enter: ";
			cin >> hrs[count];
		}

		// Get this employee's pay rate.
		cout << "\tPay rate: $";
		cin >> rate[count];

		// Validate the pay rate.
		while (rate[count] < 6.00)
		{
			cout << "\nPay rate must be 6.00 or more. "
				<< "Please re-enter: $";
			cin >> rate[count];
		}

		// Calculate this employee's gross pay.

		// ADD statement to calculate wages by multiplying
		// hours with rate of pay;

		pay[count] = hrs[count] * rate[count];
	}
}