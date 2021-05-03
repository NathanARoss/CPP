//Triangle.cpp
#include "Triangle.h"
#include <math.h>

//returns if the given sides make a valid triangle
bool Triangle::isValidTriangle(double side1, double side2, double side3)
{
	//the current triangle side lengths make a valid triangle
	bool isValid = true;

	//check for negative lengths
	if (side1 < 0.0)
		isValid = false;

	//check if smaller than sum of other 2 sides
	if (side3 > side1 + side2)
			isValid = false;

	return isValid;
}

//configured consturctor
Triangle::Triangle(double side1, double side2, double side3)
	: side1(0.0), side2(0.0), side3(0.0)
{
	setSides(side1, side2, side3);
}

//verify then set side lengths
void Triangle::setSides(double side1, double side2, double side3)
{
	//sort sides by numeric order first
	//bubble sort
	if (side1 > side2)
	{
		double temp = side1;
		side1 = side2;
		side2 = temp;
	}

	if (side2 > side3)
	{
		double temp = side2;
		side2 = side3;
		side3 = temp;
	}

	if (side1 > side2)
	{
		double temp = side1;
		side1 = side2;
		side2 = temp;
	}

	//make sure the triangle config is valid before using
	if (isValidTriangle(side1, side2, side3))
	{
		this->side1 = side1;
		this->side2 = side2;
		this->side3 = side3;
	}
}

//return side lengths in a vector
std::vector<double> Triangle::getSides() const
{
	//allocate memory before hand, avoid default constructors
	std::vector<double> sides;
	sides.reserve(3);

	//cannot loop, sides are not in array
	sides.push_back(side1);
	sides.push_back(side2);
	sides.push_back(side3);

	return sides;
}

//returns the area
double Triangle::getArea() const
{
	//using Heron's formula
	double p = getPerimeter() / 2.0;
	double area = sqrt(p * (p - side1) * (p - side2) * (p - side3));
	return area;
}

//distance around triangle
double Triangle::getPerimeter() const
{
	return side1 + side2 + side3;
}

//2 sides are equal and 3rd is sqrt(s1+s2)
bool Triangle::isRightTriangle() const
{
	//again, lengths are sorted by value
	//check if the calculated hypotunuse == side3
	double hypotenuse = sqrt(side1 * side1 + side2 * side2);
	double difference = side3 - hypotenuse;
	return (abs(difference) < 0.01);
}

//all sides are equal
bool Triangle::isEquilateral() const
{
	//if smallest == largest, middle must be equal too
	return (side1 == side3);
}

//2 sides are equal, but not third
bool Triangle::isIsosceles() const
{
	//side lengths are sorted smallest to largest
	bool isosceles = false;

	if (side1 == side2)
		isosceles = true;

	if (side2 == side3)
		isosceles = true;

	//if smallest == largest, all sides are equal
	if (side1 == side3)
		isosceles = false;

	return isosceles;
}