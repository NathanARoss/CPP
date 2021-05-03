//Question 2:
//input an input file, output file, and letters to remove from contents
//read contents of input file and remove selected letters
//save modified contents to output file

#include <iostream> // std::cin, std::cout, std::getline
#include <fstream> // std::ifstream, std::ofstream
#include <cstdlib> // EXIT_SUCCESS
#include <string> // std::string

//in a loop, ask for an input file name until a valid input file can be opened
void getExistingFile(std::ifstream &inputFile);

//return originalText with all characters in filter removed
std::string getFilteredText(std::string originalText, std::string filter);

//entry point
int main()
{
	//declarations
	std::string outputFilename;
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::string filter;
	std::string originalText;
	std::string filteredText;

	//user greeting
	std::cout << "This program inputs a filename to read, a filename," << std::endl;
	std::cout << "to write, and a string of letters to filter out." << std::endl;
	std::cout << std::endl;

	//pesters the user for an input file name until they enter a valid one
	getExistingFile(inputFile);

	//read the whole file into memory and close it
	std::getline(inputFile, originalText, '\0');
	inputFile.close();

	//input the string of characters to filter out
	std::cout << "Enter a string of characters to filter out: ";
	std::getline(std::cin, filter, '\n');
	std::cout << std::endl;

	//filter out the unwanted characters
	filteredText = getFilteredText(originalText, filter);

	//display the results, lets the user see what's being saved
	std::cout << "Original text:" << std::endl;
	std::cout << originalText << std::endl;
	std::cout << std::endl;
	std::cout << "Filtered text:" << std::endl;
	std::cout << filteredText << std::endl;
	std::cout << std::endl;

	//get a file name to create an overwriting file with
	std::cout << "Enter output file name: ";
	std::getline(std::cin, outputFilename);
	outputFile.open(outputFilename, std::ofstream::trunc);
	
	//write the filtered message to it and close it
	outputFile << filteredText;
	outputFile.close();

	//pause before returning success
	system("pause");
	return EXIT_SUCCESS;
}

//in a loop, input a file name string until one can
//open an existing input file
void getExistingFile(std::ifstream &inputFile)
{
	std::string fileName;
	std::cout << "Enter input file name: ";
	std::getline(std::cin, fileName);
	inputFile.open(fileName);

	//keep asking until you find a valid file
	while (!inputFile.is_open())
	{
		std::cout << "Failed to open file.  Re-enter file name: ";
		std::getline(std::cin, fileName);
		inputFile.open(fileName);
	}
}

//loops through all characters in a string and moves some backward
//to fill in gaps created by ignoring filtered characters
//returns the filtered string
std::string getFilteredText(std::string text, std::string filter)
{
	//size of filtered string AND position to move kept characters
	size_t newSize = 0;

	//loop through all characters ignoring filtered characters
	size_t range = text.size();
	for (size_t i = 0; i < range; ++i)
	{
		//overwrite filtered chars with chars later in the string
		char c = text[i];
		if (filter.find(c) == std::string::npos)
			text[newSize++] = c;
	}

	//place a null at the end of the string and hopefully reallocate
	text.resize(newSize);

	return text;
}