/*
Nathan Ross
9-14-16

Demonstrates polymorphism by creating a triangle class that
implements a triangle interface virtual base class and it's
functions

Input:
	The lengths of sides of a triangle

Processing:
	Verify that triangle side lengths make a valid triangle

Output:
	triangle area
	triangle perimeter
	if triangle is right triangle
	if triangle is equilatertal
	if triangle is isosceles
*/

#include <iostream>
#include "Triangle.h"
#include <cstdlib>

//entry point
int main()
{
	while (true)
	{
		//input
		double side1, side2, side3;
		std::cout << "Enter 3 sides separated by spaces: ";
		std::cin >> side1 >> side2 >> side3;

		//display info about triangle
		TriangleInterface *tri = new Triangle(side1, side2, side3);

		std::cout << "sides: ";
		auto sides = tri->getSides();
		for (auto s : sides)
			std::cout << ' ' << s;
		std::cout << std::endl;

		std::cout << "perimeter: " << tri->getPerimeter() << std::endl;
		std::cout << "isRightTriangle(): " << tri->isRightTriangle() << std::endl;
		std::cout << "isEquilateral(): " << tri->isEquilateral() << std::endl;
		std::cout << "isIsosceles(): " << tri->isIsosceles() << std::endl;

		delete tri;
	}

	return EXIT_SUCCESS;
}