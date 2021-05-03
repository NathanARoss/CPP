//Car.h
#pragma once
#include <string>

using std::string;

class Car
{
	int id; //needed for records
	string make;
	string model;
	unsigned char doorCount;
	bool isAutomatic;

public:
	Car() : id(0), doorCount(0), isAutomatic(false)
	{ }

	Car(int id, string make, string model, int doorCount, bool isAutomatic)
		: id(id), make(make), model(model), doorCount(doorCount), isAutomatic(isAutomatic)
	{ }

	int getID() const;
	string getMake() const;
	string getModel() const;
	unsigned char getDoorCount() const;
	bool getIsAutomatic() const;
};