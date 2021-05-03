// This program will output the area
// of rectangle with given length and width

//  Nathan Ross

#include <iostream> //std::cout and std::cin
#include <string> //std::string
#include <sstream> //std::stringstream

//return the number of characters needed to represent the given float value
int getCharsNeeded(float valueToRepresent)
{
	std::stringstream ss;
	ss << valueToRepresent;
	return ss.str().length();
}

//display asci art representing the problem
std::string getFormattedBox(float length, float width, float area)
{
	//is constructed with an empty string
	std::stringstream output;

	//calculate how many characters the area value needs to draw it inside a box
	int lengthChars = getCharsNeeded(length);
	int areaChars = getCharsNeeded(area);

	//display blankspace before the length to display it in the centered
	for (int i = 0; i < (areaChars - lengthChars) / 2 + 1; ++i)
	{
		output << " ";
	}
	output << length << std::endl;

	//display the top face of the boxx ex "+-----+"
	output << "+";
	for (int i = 0; i < areaChars; ++i)
	{
		output << "-";
	}
	output << "+" << std::endl;

	//display the walls, area value, and box width, ex "|48|4"
	output << "|" << area << "|" << width << std::endl;

	//display the bottom of the box
	output << "+";
	for (int i = 0; i < areaChars; ++i)
	{
		output << "-";
	}
	output << "+" << std::endl;

	return output.str();
}

int main()
{
	float length, width;
	//write statement to declare variable called area of type float
	float area;

	//these values can be anything, but the problem dictates that they must be hard coded
	length = static_cast<float>(12);
	width = static_cast<float>(4);

	//write statement here to compute area.
	area = length * width;

	// Write code here to display value of length, width and area
	// Add text to make displayed information meaningfule
	std::cout << "Length: " << length << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Area: " << area << std::endl;
	std::cout << std::endl;
	std::cout << getFormattedBox(length, width, area);

	return EXIT_SUCCESS;
}