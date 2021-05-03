//Question 1:
//this program inputs a message and outputs the same message
//with each character's position offset by an input number
//outputs resulting encoded message

#include <iostream> // std::cin std::cout
#include <string> // std::string, std::getline()
#include <cstdlib> // EXIT_SUCCESS
#include <ctype.h> // isupper(), is lower()

//adds shift to all letters in str, wraps within letter case
std::string encodeCeasarCipher(std::string str, char shift);

//entrypoint
int main()
{
	//greet the user, just copying the example output
	std::cout << "This program encodes a message using Ceasar cipher." << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;

	//set message to encode
	std::string plainText;
	std::cout << "Enter a message: ";
	std::getline(std::cin, plainText);

	std::cout << std::endl;

	//input encoding configuration
	int characterShift;
	std::cout << "Enter the number of character positions to shift: ";
	std::cin >> characterShift;

	std::cout << std::endl;
	std::cout << std::endl;

	//display encoded message
	std::string cipherText = encodeCeasarCipher(plainText, static_cast<char>(characterShift));
	std::cout << "Encoded message: " << cipherText << std::endl;

	//pause and return success
	system("pause");
	return EXIT_SUCCESS;
}

//shifts each letter in a string and wraps within the letter's case
//e.g. ("xyz", 1) = "yza", ("ABC", -1) = "ZAB"
std::string encodeCeasarCipher(std::string str, char shift)
{
	for (char &c : str)
	{
		//c += shift; //does not work on my compiler

		//shifts the character position and wraps within a letter's case
		//assumes letters a-z and A-Z are stored in ascending order
		if (islower(c))
		{
			int offset = (c - 'a' + shift) % 26;
			if (offset < 0) //wrap negative offsets
				offset += 26;
			c = static_cast<char>('a' + offset);
		}
		else if (isupper(c))
		{
			int offset = (c - 'A' + shift) % 26;
			if (offset < 0) //wrap negative offsets
				offset += 26;
			c = static_cast<char>('A' + offset);
		}
	}
	return str;
}