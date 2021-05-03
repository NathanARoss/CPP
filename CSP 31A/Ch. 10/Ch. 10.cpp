/*
Purpose:
	Format a run-together string into a property formated string and Pig Latin

Input:
	A run together string, such as "StopAndSmellTheRoses."

Processing:
	Treat uppercase letters as word separators and insert spaces between words, leave only the first letter capitalized
	For each word, move the first letter to the end and append "ay"

Output:
	Properly formatting string, such as "Stop and smell the roses"
	Pig Latin string, such as "topSay ndaay mellsay hetay osesray"

Written by Nathan Ross
Last modified 5/1/16
*/

#include <iostream> // std::cout std::cin
#include <string>   // std::string
#include <ctype.h>  // tolower() isupper()
#include <cstdlib>  // EXIT_SUCCESS

//convert a mushed together string into a sentence formatted string
std::string getSeparatedString(std::string mushedString);

//convert a sentence into pig latin
std::string getPigLatinString(std::string formattedString);

int main()
{
	std::cout << "Enter a sentence with no whitespace and all capitalized words: ";
	std::string mushedString;
	std::getline(std::cin, mushedString); //get a whole line including whitespace

	std::string separatedString = getSeparatedString(mushedString);
	std::string pigLatinString = getPigLatinString(separatedString);

	std::cout << "Separated sentence: " << separatedString << std::endl;
	std::cout << "Pig Latin sentence: " << pigLatinString << std::endl;

	return EXIT_SUCCESS;
}

std::string getSeparatedString(std::string mushedString)
{
	int i = 1; //ignore the first letter

	while (i < mushedString.length())
	{
		if (isupper(mushedString[i]))
		{
			mushedString[i] = tolower(mushedString[i]);
			mushedString.insert(i, 1, ' ');
			i += 2;
		}
		else
			++i;
	}

	return mushedString;
}

std::string getPigLatinString(std::string formattedString)
{
	//change the first letter to lowercase because it is likely to be moved
	formattedString[0] = tolower(formattedString[0]);

	int i = 0;

	while (i < formattedString.length())
	{
		std::string wordEnding = "0ay";
		wordEnding[0] = formattedString[i];
		formattedString.erase(i, 1);

		//look for the next non-alphabetical character or end of string
		while (isalpha(formattedString[i]) && i < formattedString.length())
			++i;

		formattedString.insert(i, wordEnding);
		i += 4;
	}

	//make the Pig Latin sentence have sentence capitalization again
	formattedString[0] = toupper(formattedString[0]);

	return formattedString;
}