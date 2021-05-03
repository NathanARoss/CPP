//Question 1.cpp
//Converts binary notation to decimal notation 64 bits at a time

#include <iostream>
#include <cstdint>
#include <string>
#include <sstream>

#include "ArrayStack.h"

//inputs string of '1's and '0's from user
//packs bits into uint64_ts and pushes them into the given stack
//in LITTLE_ENDIAN order
void inputBinaryStack(StackInterface<uint64_t>* binaryStack);

//verifies that a string only contains 1s and 0s
bool isBinaryString(const std::string &str);

//takes a stack of uint64_t in LITTLE_ENDIAN order and returns a string
//containing a decimal number and a newline for each uint64_t in the stack
//argument stack is emptied in the process
std::string getDecimalString(StackInterface<uint64_t>* binaryStack);

int main()
{
	StackInterface<uint64_t> *binaryStack = new ArrayStack<uint64_t>();

	while (true)
	{
		//fills the stack
		inputBinaryStack(binaryStack);

		//empties the stack
		std::cout << getDecimalString(binaryStack);
		std::cout << std::endl;
	}

	delete binaryStack;
	return 0;
}

//verify user input is in base 2, then, starting from the end
//of the string, pack each char/bit into a uint64 and .push() it
void inputBinaryStack(StackInterface<uint64_t>* binaryStack)
{
	std::string binaryString;

	//input validation
	std::cout << "Enter a binary number: ";
	std::getline(std::cin, binaryString);

	while (!isBinaryString(binaryString))
	{
		std::cout << "Error. Enter a number with only 0s and 1s: ";
		std::getline(std::cin, binaryString);
	}

	//digits are written with highest significance first
	//start from the end of the string to convert to least significant bit
	for (int i = binaryString.length() - 1; i >= 0; i -= 64)
	{
		uint64_t bigInt = 0;
		for (uint64_t bit = 0; bit < __min(64, i + 1); ++bit)
		{
			if (binaryString[i - bit] == '1')
				bigInt |= 1LL << bit;
		}

		binaryStack->push(bigInt);
	}
}

//each character should be a '0' or '1'
bool isBinaryString(const std::string &str)
{
	for (char c : str)
	{
		if (c != '0' && c != '1')
			return false;
	}

	return true;
}

//display decimal numbers in groups of 64 bits because I do not know
//how to convert a number larger than 8 bytes into decimal
std::string getDecimalString(StackInterface<uint64_t>* binaryStack)
{
	std::stringstream ss;

	int bits = 0;
	while (!binaryStack->isEmpty())
	{
		std::cout << "bits " << bits << '-' << bits + 63 << ": ";
		std::cout << binaryStack->peek() << std::endl;

		binaryStack->pop();
		bits += 64;
	}

	return ss.str();
}