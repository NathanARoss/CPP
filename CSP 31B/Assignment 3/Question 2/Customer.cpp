//Customer.cpp
#include "Customer.h"

void Customer::rent(int carID)
{
	rentalHistory.push_back(carID);
}

int Customer::getID() const
{
	return id;
}

string Customer::getLastName() const
{
	return lastName;
}

string Customer::getFirstName() const
{
	return firstName;
}

string Customer::getPhoneNumber() const
{
	return phoneNumber;
}

string Customer::getCity() const
{
	return city;
}

string Customer::getEmail() const
{
	return email;
}

const std::vector<int>& Customer::getRentalHistory() const
{
	return rentalHistory;
}