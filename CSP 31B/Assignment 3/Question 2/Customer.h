//Customer.h
//holds information related to customer
#pragma once
#include <string>
#include <vector>

using std::string;

class Customer
{
private:
	int id;
	string lastName;
	string firstName;
	string phoneNumber;
	string city;
	string email;

	//vector of ids of cars rented, in order
	std::vector<int> rentalHistory;

public:
	Customer() : id(0LL)
	{ }

	Customer(int id, string lastName, string firstName, string phoneNumber, string city, string email)
		: id(id), lastName(lastName), firstName(firstName), phoneNumber(phoneNumber), city(city), email(email)
	{ }

	void rent(int carID);

	int getID() const;
	string getLastName() const;
	string getFirstName() const;
	string getPhoneNumber() const;
	string getCity() const;
	string getEmail() const;
	const std::vector<int>& getRentalHistory() const;
};