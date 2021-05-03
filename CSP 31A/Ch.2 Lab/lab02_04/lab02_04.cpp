// This program will output the circumference and area
// of the circle with a given radius.
//  Nathan Ross

#include <iostream>

const double PI = acos(-1.0f); //this constant is unfolded during compilation

int main()

{
	//declare variable called area of type float
	float area;
	//declare variable called radius of type float and set value to 10
	float radius = 10.0f;


	// write statement to calculate area. Value of PI is defined as a const
	area = PI * radius * radius;

	// write code to display values for radius and area of circle.
	std::cout << "Radius: " << radius << std::endl;
	std::cout << "Area: " << area << std::endl;

	return EXIT_SUCCESS;
}