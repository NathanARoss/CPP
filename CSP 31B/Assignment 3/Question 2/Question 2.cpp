//Question 2.cpp
//maintain a car rental database

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <limits>

#include "Customer.h"
#include "Car.h"
#include "LinkedList.h"

//short-hands
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

//loads information from given file
bool loadInventory(const string &fileName, vector<Car> &inventory, LinkedList<int> &activeRentals);
bool loadCustomers(const string &fileName, LinkedList<Customer> &customers);

//saves information to given file (in the same format)
bool saveInventory(const string &fileName, const vector<Car> &inventory, const LinkedList<int> &activeRentals);
bool saveCustomers(const string &fileName, const LinkedList<Customer> &customers);

//get an item's position within a container by its id
int getCarPosition(const vector<Car> &inventory, int id);
int getCustomerPosition(const LinkedList<Customer> &customers, int id);

//find the smallest unused customer ID
int getNewCustomerID(const LinkedList<Customer> &customers);

//short-hand display functions
void displayHelpMessage();
void displayCar(const Car& car);
void displayCustomer(const Customer &customer);

//the appropriate function is called based on the first word of a command
void rentCar(stringstream &command, LinkedList<int> &activeRentals, const vector<Car> &inventory, LinkedList<Customer> &customers);
void returnCar(stringstream &command, LinkedList<int> &activeRentals, const vector<Car> &inventory);
void listCars(stringstream &command, const LinkedList<int> &activeRentals, const vector<Car> &inventory);
void carDetails(stringstream &command, const vector<Car> &inventory);
void carStatus(stringstream &command, const LinkedList<int> &activeRentals, const vector<Car> &inventory);
void addCustomer(LinkedList<Customer> &customers);
void removeCustomer(stringstream &command, LinkedList<Customer> &customers);
void customerDetails(stringstream &command, const LinkedList<Customer> &customers);
void listCustomers(const LinkedList<Customer> &customers);
void customerHistory(stringstream &command, const LinkedList<Customer> &customers, const vector<Car> &inventory);

//the number of characters for cin and ifstream to ignore
const long long maxStreamLength = std::numeric_limits<std::streamsize>::max();

const string INVENTORY_PATH = "Inventory.txt";
const string CUSTOMERS_PATH = "Customers.txt";

int main()
{
	vector<Car> inventory;
	LinkedList<int> activeRentals;
	LinkedList<Customer> customers;

	//load the inventory from file in the on-disk order
	bool loadedInventory = loadInventory(INVENTORY_PATH, inventory, activeRentals);
	if (!loadedInventory)
		cout << "Failed to read " << INVENTORY_PATH << endl << endl;

	bool loadedCustomers = loadCustomers(CUSTOMERS_PATH, customers);
	if (!loadedCustomers)
		cout << "Failed to read " << CUSTOMERS_PATH << endl << endl;

	//display available commands
	displayHelpMessage();
	std::cout << endl;

	//receive commands and respond, exit window to close program
	while (true)
	{
		string input;
		std::getline(std::cin, input);
		std::stringstream command(input);

		string function;
		command >> function;
		//NOTE: >> does not remove data from command
		//it only changes its read position

		if (function == "rent")
			rentCar(command, activeRentals, inventory, customers);
		else if (function == "return")
			returnCar(command, activeRentals, inventory);
		else if (function == "list_cars")
			listCars(command, activeRentals, inventory);
		else if (function == "car_details")
			carDetails(command, inventory);
		else if (function == "status")
			carStatus(command, activeRentals, inventory);
		else if (function == "add_customer")
			addCustomer(customers);
		else if (function == "remove_customer")
			removeCustomer(command, customers);
		else if (function == "customer_details")
			customerDetails(command, customers);
		else if (function == "list_customers")
			listCustomers(customers);
		else if (function == "customer_history")
			customerHistory(command, customers, inventory);
		else
		{
			//unrecognized commands trigger the help text
			displayHelpMessage();
			cout << endl;
		}

		//line breaks between commands
		cout << endl;
	}

	return 0;
}

bool loadInventory(const string &fileName, std::vector<Car> &inventory, LinkedList<int> &activeRentals)
{
	bool result;

	std::ifstream file(fileName);
	if (file.is_open())
	{
		while (true)
		{
			int id;
			string make, model;
			unsigned char doorCount;
			bool isAutomatic, rented;

			//ignore the "id " before the id number
			file.ignore(3, ' ');
			file >> id;
			file.ignore(maxStreamLength, '\n');

			//fixes issue where the eof newline is treated as not the eof
			if (file.eof())
				break;

			std::getline(file, make);
			std::getline(file, model);

			file >> doorCount;
			file.ignore(maxStreamLength, '\n');

			string str;

			file >> str;
			isAutomatic = (str == "automatic");

			file >> str;
			rented = (str == "rented");

			//ignore the newline following "rented" or "available"
			//and the newline between entries
			file.ignore(maxStreamLength, '\n');
			file.ignore(maxStreamLength, '\n');

			Car entry(id, make, model, doorCount, isAutomatic);
			inventory.push_back(entry);

			//keep rented status separate
			if (rented)
				activeRentals.insert(1, id);
		}

		result = true;
	}
	else
		result = false;

	return result;
}

bool loadCustomers(const string &fileName, LinkedList<Customer> &customers)
{
	bool result;

	std::ifstream file(fileName);
	if (file.is_open())
	{
		while (true)
		{
			int id;
			string lastName, firstName, phoneNumber, city, email;
			std::vector<int> rentalHistory;

			//ignore the "id " before the id number
			file.ignore(3, ' ');
			file >> id;
			file.ignore(maxStreamLength, '\n');

			//file.eofbit is not set we read off the last newline
			if (file.eof())
				break;

			std::getline(file, lastName);
			std::getline(file, firstName);
			std::getline(file, phoneNumber);
			std::getline(file, city);
			std::getline(file, email);

			Customer customer(id, lastName, firstName, phoneNumber, city, email);

			std::string rentals;
			std::getline(file, rentals);
			std::stringstream ss(rentals);

			int carID;
			while (ss >> carID)
				customer.rent(carID);

			//ignore newline between entries
			file.ignore(maxStreamLength, '\n');

			//insert the customers in the correct order
			customers.insert(customers.getLength() + 1, customer);
		}

		result = true;
	}
	else
		result = false;

	return result;
}

bool saveInventory(const string &fileName, const vector<Car> &inventory, const LinkedList<int> &activeRentals)
{
	bool result;

	std::ofstream file(fileName, std::ios::trunc);
	if (file.is_open())
	{
		for (const Car &car : inventory)
		{
			file << "id " << car.getID() << endl;
			file << car.getMake() << endl;
			file << car.getModel() << endl;
			file << car.getDoorCount() << " doors" << endl;
			file << (car.getIsAutomatic() ? "automatic" : "manual") << endl;
			
			bool status = activeRentals.contains(car.getID());
			file << (status ? "rented" : "available") << endl;
			file << endl;
		}

		result = true;
	}
	else
		result = false;

	return result;
}

bool saveCustomers(const string &fileName, const LinkedList<Customer> &customers)
{
	bool result;

	std::ofstream file(fileName, std::ios::trunc);
	if (file.is_open())
	{
		for (int i = 1; i <= customers.getLength(); ++i)
		{
			const Customer &customer = customers.getEntry(i);
			file << "id " << customer.getID() << endl;
			file << customer.getLastName() << endl;
			file << customer.getFirstName() << endl;
			file << customer.getPhoneNumber() << endl;
			file << customer.getCity() << endl;
			file << customer.getEmail() << endl;

			for (int id : customer.getRentalHistory())
				file << id << ' ';
			file << endl;

			//newline between entries
			file << endl;
		}

		result = true;
	}
	else
		result = false;

	return result;
}

int getCarPosition(const vector<Car> &inventory, int id)
{
	for (int i = 0; i < inventory.size(); ++i)
	{
		if (inventory[i].getID() == id)
			return i;
	}
	return -1;
}

int getCustomerPosition(const LinkedList<Customer> &customers, int id)
{
	for (int i = 1; i <= customers.getLength(); ++i)
	{
		if (customers.getEntry(i).getID() == id)
			return i;
	}
	return -1;
}

int getNewCustomerID(const LinkedList<Customer> &customers)
{
	int id = 0;
	for (int i = 1; i < customers.getLength(); ++i)
	{
		if (customers.getEntry(i).getID() == id)
			++id;
	}
	return id;
}

void displayHelpMessage()
{
	cout << "Enter a command\n"
		"rent [customerID] [carID]\n"
		"return [carID]\n"
		"list_cars [all | rented | available]\n"
		"car_details [carID]\n"
		"status [carID]\n"
		"add_customer\n"
		"remove_customer [customerID]\n"
		"customer_details [customerID]\n"
		"list_customers\n"
		"customer_history [ID | all]" << endl;
}

void displayCar(const Car& car)
{
	cout << car.getID() << ": " << car.getMake() << " " << car.getModel() << endl;
}

void displayCustomer(const Customer &customer)
{
	cout << customer.getID() << ": " << customer.getLastName()
		<< ", " << customer.getFirstName() << endl;
}

void rentCar(stringstream &command, LinkedList<int> &activeRentals, const vector<Car> &inventory, LinkedList<Customer> &customers)
{
	int customerID, carID;

	if (command.eof())
		cout << "If available, marks the selected car as rented\n"
		"rent [carID]" << endl;

	//if we successfully read 2 int values
	else if (command >> customerID >> carID)
	{
		int customerPosition = getCustomerPosition(customers, customerID);
		if (customerPosition == -1)
			cout << "Customer id " << customerID << "does not exist" << endl;
		else {
			//if the specified customer exists
			int carPosition = getCarPosition(inventory, carID);
			if (carPosition == -1)
				cout << "Car id " << carID << " does not exist" << endl;

			//if the specified car exists
			else if (activeRentals.contains(carID))
				cout << "Car id " << carID << " is already taken" << endl;

			//if the specified car is available
			else
			{
				//LinkedList<> has no functionality for mutating values in place
				//Items must be overwriten with modified copies
				Customer rentingCustomer = customers.getEntry(customerPosition);
				rentingCustomer.rent(carID);
				customers.replace(customerPosition, rentingCustomer);
				activeRentals.insert(1, carID);

				//the inventory file keeps track of what cars are available
				//the customers file keeps track of what cars each customer rents
				saveInventory(INVENTORY_PATH, inventory, activeRentals);
				saveCustomers(CUSTOMERS_PATH, customers);

				//user feedback
				displayCar(inventory[carPosition]);
				cout << "is now rented to " << endl;
				displayCustomer(rentingCustomer);
			}
		}
	}
	else
		cout << "Error. Failed to parse customer ID or car ID" << endl;
}

void returnCar(stringstream &command, LinkedList<int> &activeRentals, const vector<Car> &inventory)
{
	int id;

	if (command.eof())
		cout << "If available, marks the selected car as available\n"
		"return [carID]" << endl;
	else if (command >> id)
	{
		int carPosition = getCarPosition(inventory, id);
		if (carPosition == -1)
			cout << "Car id " << id << " does not exist" << endl;
		else
		{
			const Car &car = inventory[carPosition];
			displayCar(car);

			int rentalIndex = activeRentals.find(id);
			if (rentalIndex == -1)
				cout << "is not rented" << endl;
			else
			{
				activeRentals.remove(rentalIndex);
				saveInventory(INVENTORY_PATH, inventory, activeRentals);
				cout << "is now available" << endl;
			}
		}
	}
	else
		cout << "Error. Failed to parse car ID" << endl;
}

void listCars(stringstream &command, const LinkedList<int> &activeRentals, const vector<Car> &inventory)
{
	string listScope;

	if (command >> listScope)
	{
		if (listScope == "all")
		{
			for (const Car &car : inventory)
				displayCar(car);
		}
		else if (listScope == "rented")
		{
			for (const Car &car : inventory)
			{
				if (activeRentals.contains(car.getID()))
					displayCar(car);
			}
		}
		else if (listScope == "available")
		{
			for (const Car &car : inventory)
			{
				if (!activeRentals.contains(car.getID()))
					displayCar(car);
			}
		}
		else
			std::cout << "Error. Unrecognized list scope" << endl;
	}
	else //no second argument
	{
		cout << "Lists all cars with the given range\n"
			"list_cars [all | rented | available]" << endl;
	}
}

void carDetails(stringstream &command, const vector<Car> &inventory)
{
	int id;

	if (command.eof())
		cout << "Returns information about a car by its id\n"
		"details [carID]" << endl;
	else if (command >> id)
	{
		int position = getCarPosition(inventory, id);
		if (position == -1)
			cout << "Car id " << id << " does not exist" << endl;
		else
		{
			const Car &car = inventory[position];
			displayCar(car);
			cout << car.getDoorCount() << " doors" << endl;
			cout << (car.getIsAutomatic() ? "Automatic" : "Manual") << " transmission" << endl;
		}
	}
	else
		cout << "Error. Failed to parse car ID" << endl;
}

void carStatus(stringstream &command, const LinkedList<int> &activeRentals, const vector<Car> &inventory)
{
	int id;

	if (command.eof())
		cout << "Returns rental status of a car by its id\n"
		"status [carID]" << endl;
	else if (command >> id)
	{
		if (getCarPosition(inventory, id) == -1)
			cout << "Car id " << id << " does not exist" << endl;
		else
		{
			if (activeRentals.contains(id))
				cout << "Car id " << id << " is rented" << endl;
			else
				cout << "Car id " << id << " is available" << endl;
		}
	}
	else
		cout << "Error. Failed to parse car ID" << endl;
}

void addCustomer(LinkedList<Customer> &customers)
{
	//only command that does not use arguments
	//ids are picked by what is available

	//gather additional information about the customer
	int id = getNewCustomerID(customers);

	string lastName, firstName, phoneNumber, city, email;
	std::cout << "Last name: ";
	std::getline(std::cin, lastName);
	std::cout << "First name: ";
	std::getline(std::cin, firstName);
	std::cout << "Phone number: ";
	std::getline(std::cin, phoneNumber);
	std::cout << "City: ";
	std::getline(std::cin, city);
	std::cout << "Email: ";
	std::getline(std::cin, email);

	Customer newCustomer(id, lastName, firstName, phoneNumber, city, email);

	cout << "Confirm customer additon? (Y/N): ";
	char c = std::cin.get();
	std::cin.ignore(maxStreamLength, '\n');

	if (c == 'y' || c == 'Y')
	{
		customers.insert(1, newCustomer);
		saveCustomers(CUSTOMERS_PATH, customers);
		cout << "Customer id " << id << " added" << endl;
	}
	else
		cout << "Customer addition canceled" << endl;
}

void removeCustomer(stringstream &command, LinkedList<Customer> &customers)
{
	int id;

	if (command.eof())
		cout << "Removes a customer's information\n"
		"remove_customer [customerID]" << endl;
	else if (command >> id)
	{
		int position = getCustomerPosition(customers, id);
		if (position == -1)
			cout << "Customer id " << id << " does not exist" << endl;
		else
		{
			//confirm removal
			displayCustomer(customers.getEntry(position));

			cout << "Confirm removal? (Y/N): ";
			char c = std::cin.get();
			std::cin.ignore(maxStreamLength, '\n');

			if (c == 'y' || c == 'Y')
			{
				customers.remove(position);
				saveCustomers(CUSTOMERS_PATH, customers);
				cout << "Customer id " << id << " is removed" << endl;
			}
			else
				cout << "Customer removal canceled" << endl;
		}
	}
	else
		cout << "Error. Failed to parse customer ID" << endl;
}

void customerDetails(stringstream &command, const LinkedList<Customer> &customers)
{
	int id;

	if (command.eof())
		cout << "Displays more information about a customer\n"
		"customer_details [customerID]" << endl;
	else if (command >> id)
	{
		int position = getCustomerPosition(customers, id);
		if (position == -1)
			cout << "Customer id " << id << " does not exist" << endl;
		else
		{
			const Customer &customer = customers.getEntry(position);
			displayCustomer(customer);
			cout << "phone: " << customer.getPhoneNumber() << endl;
			cout << "city: " << customer.getCity() << endl;
			cout << "email: " << customer.getEmail() << endl;
		}
	}
	else
		cout << "Error. Failed to parse customer ID" << endl;
}

void listCustomers(const LinkedList<Customer> &customers)
{
	for (int i = 1; i <= customers.getLength(); ++i)
		displayCustomer(customers.getEntry(i));
}

void customerHistory(stringstream &command, const LinkedList<Customer> &customers, const vector<Car> &inventory)
{
	string historyScope;

	if (command >> historyScope)
	{
		if (historyScope == "all")
		{
			for (int i = 1; i <= customers.getLength(); ++i)
			{
				const Customer &customer = customers.getEntry(i);
				displayCustomer(customer);

				for (int carID : customer.getRentalHistory())
				{
					int position = getCarPosition(inventory, carID);
					displayCar(inventory[position]);
				}
			}
		}
		else
		{
			//try to parse the second argument as an id (int)
			try
			{
				int id = std::stoi(historyScope);
				int position = getCustomerPosition(customers, id);

				if (position == -1)
					cout << "Customer id " << id << " does not exist" << endl;
				else
				{
					const Customer &customer = customers.getEntry(position);
					displayCustomer(customer);

					for (int carID : customer.getRentalHistory())
					{
						int position = getCarPosition(inventory, carID);
						displayCar(inventory[position]);
					}
				}
			}
			catch (std::invalid_argument error)
			{
				std::cout << "Error. Unrecognized history scope" << endl;
			}
		}
	}
	else //no second argument
		cout << "Lists the history of the given customer or all customers\n"
			"customer_history [ID | all]" << endl;
}