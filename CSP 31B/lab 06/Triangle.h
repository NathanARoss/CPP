//Triangle.h
#pragma once
#include "Triangle Interface.h"
#include <vector>

//implements the virtual functions in TriangleInterface
class Triangle : public TriangleInterface
{
private:
	double side1, side2, side3;

	bool isValidTriangle(double side1, double side2, double side3);

public:
	//unique constructors
	Triangle() : side1(0.0), side2(0.0), side3(0.0) {}

	Triangle(double side1, double side2, double side3);

	//virtual function implementations
	void setSides(double side1, double side2, double side3);

	std::vector<double> getSides() const;

	double getArea() const;

	double getPerimeter() const;

	bool isRightTriangle() const;

	bool isEquilateral() const;

	bool isIsosceles() const;

}; //end Triangle