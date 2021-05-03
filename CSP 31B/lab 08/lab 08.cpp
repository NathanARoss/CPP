#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <iomanip>
#include <sstream>
#include <locale>

//returns if a word is spelled the same backwards
//e.g. isPalindrome("Abcdedcba") == true
bool isPalindrome(const std::string word)
{
	std::stack<char> aStack;
	bool palindrome = true;

	const int length = word.length();
	const int halfLength = length;

	//insert first half of characters into stack
	for (int i = 0; i < halfLength; ++i)
	{
		const char letter = tolower(word[i]);
		aStack.push(letter);
	}

	//if word has an odd length, skips middle char
	int i = length - halfLength;
	while (i < length && palindrome == true)
	{
		const char letter = tolower(word[i]);

		if (aStack.top() == letter)
		{
			aStack.pop();
			++i;
		}
		else
			palindrome = false;
	}

	//if the stack is not empty then palindrome will
	//be false, no need to explicitly test
	return palindrome;
}


class City
{
private:
	char name;
	std::string destinations;

public:
	City() {}

	City(char name, std::string destinations) : name(name), destinations(destinations)
	{}

	char getName();
	std::string getDestinations();
};

char City::getName()
{
	return name;
}

std::string City::getDestinations()
{
	return destinations;
}

//makes a copy of the stack and displays its contents on one line
std::string displayCityStack(std::stack<char> journey)
{
	std::stringstream ss;

	while (!journey.empty())
	{
		ss << journey.top();
		journey.pop();
	}

	return ss.str();
}

void displayFlightStack(char origin, char destination)
{
	if (origin < 'A' || origin > 'H' || destination < 'A' || destination > 'H')
		return;

	std::vector<City> cities {
		City('A', "BC"),
		City('B', "DH"),
		City('C', "BD"),
		City('D', "EFH"),
		City('E', "I"),
		City('F', "IG"),
		City('G', "C"),
		City('H', "G"),
		City('I', "C")
	};
	bool cityVisited[9]{ false };
	std::stack<char> cityStack;

	cityStack.push(origin);
	std::cout << "Action" << '\t' << std::setw(9) << "Stack (t->b)" << "\tReason" << std::endl;
	std::cout << "Push " << origin << '\t' << std::setw(9) << displayCityStack(cityStack) << "\tInitialize" << std::endl;

	while (!cityStack.empty() && cityStack.top() != destination)
	{
		char cityName = cityStack.top();
		City currentCity = cities[cityName - 'A'];
		std::string destinations = currentCity.getDestinations();

		//go to the first unvisited destination city
		bool pathContinues = false;
		for (const char newCity : destinations)
		{
			if (!cityVisited[newCity - 'A'])
			{
				cityVisited[newCity - 'A'] = true;
				pathContinues = true;
				cityStack.push(newCity);
				std::cout << "Push " << newCity << "\t";
				break;
			}
		}

		//if no unvisited destinations exist, back up
		if (!pathContinues)
		{
			std::cout << "Pop  " << cityStack.top() << "\t";
			cityStack.pop();
		}

		std::cout << std::setw(9) << displayCityStack(cityStack);

		if (pathContinues)
			std::cout << "\tNext adjacent city";
		else
			std::cout << "\tNo unvisited cities available";

		std::cout << std::endl;
	}
}


bool checkBraces(std::string aString)
{
	//pattern of matching braces, can be expanded
	static const std::string OPENING_BRACES("{[(");
	static const std::string CLOSING_BRACES("}])");

	std::stack<char> aStack;
	bool balanced = true;

	//look at each character in a string
	for (const char c : aString)
	{
		if (OPENING_BRACES.find(c) != std::string::npos)
		{
			//add opening brace to stack
			aStack.push(c);
		}
		else if (CLOSING_BRACES.find(c) != std::string::npos)
		{
			//closing brace found
			if (aStack.empty())
			{
				//stack is empty, not balanced
				balanced = false;
				break;
			}
			else
			{
				//find corresponding opening brace character
				const int i = CLOSING_BRACES.find(c);
				const char openingBrace = OPENING_BRACES[i];

				if (aStack.top() == openingBrace)
				{
					//remove matching opening brace
					aStack.pop();
				}
				else
				{
					//mismatched braces, not balanced
					balanced = false;
					break;
				}
			}
			
		}
	}

	//if any chars remain in stack, string is not balanced
	//e.g. {{{}} -> {
	if (!aStack.empty())
		balanced = false;

	return balanced;
}


int main()
{
	std::string testString;

	while (true)
	{
		std::getline(std::cin, testString);
		std::cout << "isPalindrome(): " << isPalindrome(testString) << std::endl;
	}


	/*
	while (true)
	{
		char origin, dest;
		std::cout << "Enter origin and destination city: ";
		std::cin >> origin >> dest;
		std::cin.ignore();

		displayFlightStack(origin, dest);
		std::cout << std::endl;
	}
	/**/

	//std::cout << "balanced:  " << checkBraces(testString) << std::endl;

	system("pause");
	return 0;
}
