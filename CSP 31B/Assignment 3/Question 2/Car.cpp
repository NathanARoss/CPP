#include "Car.h"

int Car::getID() const
{
	return id;
}

string Car::getMake() const
{
	return make;
}

string Car::getModel() const
{
	return model;
}

unsigned char Car::getDoorCount() const
{
	return doorCount;
}

bool Car::getIsAutomatic() const
{
	return isAutomatic;
}