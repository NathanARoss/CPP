#pragma once
#include <vector>

//virtual base class, defines interface through purely virtual functions
class TriangleInterface
{
public:
	virtual void setSides(double side1, double side2, double side3) = 0;

	virtual std::vector<double> getSides() const = 0;

	virtual double getArea() const = 0;

	virtual double getPerimeter() const = 0;

	virtual bool isRightTriangle() const = 0;

	virtual bool isEquilateral() const = 0;

	virtual bool isIsosceles() const = 0;

}; //end TriangleInterface