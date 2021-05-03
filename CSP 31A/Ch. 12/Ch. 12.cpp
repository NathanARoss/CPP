/*
Purpose:
	Create and maintain a database

Input:
	Customer Data.txt
	Menu choice
	Customer info
	Index of a customer

Processing:
	Validate account number and account balance values
	Validate menu choices

Output:
	Display contents of database
	Display individual customer information
	Customer Data.txt

Writen by Nathan Ross
Last modified 4/30/16
*/

#include <iostream> // std::cin std::cout
#include <fstream>  // std::ifstream std::ofstream
#include <vector>   // std::vector<T>
#include <cstdlib>  // EXIT_SUCCESS
#include <cstdint>  // uintN_t
#include <string>   // std::string
#include <sstream>  // std::stringstream
#include <iomanip>

struct CustomerData
{
	uint64_t accountNumber; // unique account ID
	std::string name;       // name of customer
	std::string address;    // address of customer, includes house number, street, city, etc
	std::string phoneNumber;// international numbers need formatted specific ways
	double accountBalance;  // currency balance of account
};

std::vector<CustomerData> getCustomerData(std::string fileName);

void appendCustomer(std::string fileName, const CustomerData &data);

std::string getCustomerDisplay(const CustomerData &data);

char inputChar();

template <typename type>
type inputType(bool &error);

int main(void)
{
	const std::string FILENAME = "Customer Data.txt";
	std::vector<CustomerData> customerData(getCustomerData(FILENAME));

	char again;

	do
	{
		std::cout << "1. Enter a new record" << std::endl;
		std::cout << "2. Search for a record at a specific index" << std::endl;
		std::cout << "3. Display contents of entire database" << std::endl;
		std::cout << "Choice: ";

		char choice = inputChar();
		while (choice < '1' || choice > '3')
		{
			std::cout << "Enter 1, 2, or 3: ";
			choice = inputChar();
		}

		std::cout << std::endl;

		switch (choice)
		{
		case '1':
		{
			CustomerData newCustomer;
			bool error = false;

			//account number
			std::cout << "Account Number: ";
			uint64_t accountNumber = inputType<uint64_t>(error);
			while (error)
			{
				error = false;
				std::cout << "Enter a positive integer: ";
				accountNumber = inputType<uint64_t>(error);
			}
			newCustomer.accountNumber = accountNumber;

			//name
			std::cout << "Name: ";
			std::getline(std::cin, newCustomer.name);

			//address
			std::cout << "Address: ";
			std::getline(std::cin, newCustomer.address);

			//phone number
			std::cout << "Phone Number: ";
			std::getline(std::cin, newCustomer.phoneNumber);

			//currency balance
			std::cout << "Account Balance: $";
			error = false;
			double accountBalance = inputType<double>(error);
			while (error) //note: balances can be negative
			{
				error = false;
				std::cout << "Enter a number: ";
				accountBalance = inputType<double>(error);
			}
			newCustomer.accountBalance = accountBalance;

			//save to the database on disk and in RAM
			customerData.push_back(newCustomer);
			appendCustomer(FILENAME, newCustomer);
			//even if the user closes the program unexpectedly, the customer data will be saved

			std::cout << std::endl;
		}
		break;

		case '2':
		{
			bool error = false;

			std::cout << "Enter an index between 0 and " << (customerData.size() - 1) << ": ";
			size_t index = inputType<size_t>(error);

			while (index < 0 || index >= customerData.size())
			{
				error = false;
				std::cout << "Error. Enter an index between 0 and " << (customerData.size() - 1) << ": ";
				index = inputType<size_t>(error);
			}

			std::cout << std::endl;
			std::cout << getCustomerDisplay(customerData[index]) << std::endl;
			std::cout << std::endl;
		}
		break;

		case '3':
		{
			if (customerData.size() == 0)
			{
				std::cout << "No records found" << std::endl;
				std::cout << std::endl;
			}
			else
				for (const CustomerData &data : customerData)
				{
					std::cout << getCustomerDisplay(data) << std::endl;
					std::cout << std::endl;
				}
		}
		break;
		}

		std::cout << "Continue (Y/N): ";
		again = inputChar();

		std::cout << std::endl;
	} while (toupper(again) != 'N');

	return EXIT_SUCCESS;
}

//read the customer data from the given file and return it formatted as a vector of CustomerData
std::vector<CustomerData> getCustomerData(std::string filename)
{
	std::ifstream inputFile(filename);
	std::vector<CustomerData> customerData;

	//if the file does not exist, leave the customer data vector empty
	if (!inputFile.fail())
	{
		while (!inputFile.eof())
		{
			CustomerData customer;

			//if there is a newline at the end, ignore it
			if (!(inputFile >> customer.accountNumber))
				break;

			inputFile.ignore(1, '\n'); // the >> operator leaves the '\n' behind
			std::getline(inputFile, customer.name);
			std::getline(inputFile, customer.address);
			std::getline(inputFile, customer.phoneNumber);
			inputFile.ignore(1, '$'); // skip the '$' and treat the currency as a double
			inputFile >> customer.accountBalance;
			inputFile.ignore(1, '\n'); // the >> operator leaves the '\n' behind

			customerData.push_back(customer);
		}

		inputFile.close();
	}

	return customerData;
}

void appendCustomer(std::string filename, const CustomerData &data)
{
	std::ofstream outputFile(filename, std::ios::out | std::ios::app);
	outputFile << std::fixed << std::showpoint << std::setprecision(2);

	outputFile << data.accountNumber << std::endl;
	outputFile << data.name << std::endl;
	outputFile << data.address << std::endl;
	outputFile << data.phoneNumber << std::endl;
	outputFile << '$' << data.accountBalance << std::endl;
}

std::string getCustomerDisplay(const CustomerData &data)
{
	std::stringstream ss;
	ss << std::fixed << std::showpoint << std::setprecision(2);

	ss << "Account Number:\t\t" << data.accountNumber << std::endl;
	ss << "Name:\t\t\t" << data.name << std::endl;
	ss << "Address:\t\t" << data.address << std::endl;
	ss << "Phone Number:\t\t" << data.phoneNumber << std::endl;
	ss << "Account Balance:\t$" << data.accountBalance;

	return ss.str();
}

char inputChar()
{
	char input;
	std::cin.get(input);

	//ignore extra input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return input;
}

template <typename type>
type inputType(bool &error)
{
	type input;
	std::cin >> input;

	if (std::cin.fail()) //detect failure to parse type
	{
		error = true;
		std::cin.clear(); //remove error flag
	}

	//ignore extra input
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return input;
}