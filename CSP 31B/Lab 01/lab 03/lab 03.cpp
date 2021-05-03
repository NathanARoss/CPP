/*
Nathan Ross
This program demonstrates class polymorphism by creating bags
that inherit from a bag interface and add objects to those bags
*/

#include <iostream> // std::cout
#include <vector> // std::vector<>
#include <string> // std::string
#include <sstream> // std::stringstream
#include "Bag.h" //BagInterface<> Bag<>

//count and remove all entries matching a given item
template<class ItemType>
int removeAndCount(BagInterface<ItemType> * bag, const ItemType item)
{
	int count = 0;

	while (bag->contains(item))
	{
		bag->remove(item);
		++count;
	}

	return count;
}

//insert items into a stringstream and return string
template<class ItemType>
std::string getBagDistplay (BagInterface<ItemType> * bag)
{
	auto items = bag->toVector();
	std::stringstream ss;

	for (auto &item : items)
		ss << item << ", ";

	return ss.str();
}

int main()
{
	std::cout << std::endl << "*** Question 2 ***" << std::endl;

	//avoid dynamic memory allocation
	Bag<std::string> bags[3];

	//BagInterface can host any type of bag
	BagInterface<std::string> * storeBag = &bags[0];
	BagInterface<std::string> * fragileBag = &bags[1];
	BagInterface<std::string> * groceryBag = &bags[2];

	//add items to storeBag
	storeBag->add("eggs");
	storeBag->add("sugar");
	storeBag->add("bread");
	storeBag->add("eggs");
	storeBag->add("eggs");
	storeBag->add("bread");

	//display storeBag's contents
	std::cout << "storeBag contains: " << getBagDistplay(storeBag) << std::endl;

	//move fragile items to fragileBag
	while (storeBag->contains("eggs"))
	{
		storeBag->remove("eggs");
		fragileBag->add("eggs");
	}

	while (storeBag->contains("bread"))
	{
		storeBag->remove("bread");
		fragileBag->add("bread");
	}

	//move everything else into groceryBag and display the results
	std::cout << "Moving fragile items to fragileBag and the rest to groceryBag." << std::endl;

	auto remainingItems = storeBag->toVector();
	storeBag->clear();

	for (auto &item : remainingItems)
		groceryBag->add(item);

	std::cout << "storeBag contains: " << getBagDistplay(storeBag) << std::endl;

	std::cout << "fragileBag contains: " << getBagDistplay(fragileBag) << std::endl;

	std::cout << "groceryBag contains: " << getBagDistplay(groceryBag) << std::endl;

	//add more items to storeBag
	std::cout << std::endl << "*** Question 3 ***" << std::endl;
	std::cout << "Adding 4 more items to storeBag." << std::endl;

	storeBag->add("eggs");
	storeBag->add("eggs");
	storeBag->add("bread");
	storeBag->add("coffee");

	std::cout << "storeBag contains: " << getBagDistplay(storeBag) << std::endl;

	//count the amount of bread in fragileBag and remove them
	std::cout << std::endl << "*** Question 4 ***" << std::endl;
	int breadCount = removeAndCount<std::string>(fragileBag, "bread");
	std::cout << "fragileBag contained " << breadCount << " bread." << std::endl;

	//pause before returning control
	std::cout << std::endl;
	system("pause");
}

