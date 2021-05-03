/* Question 1.cpp
Question 1:
Implement functions union, intersection, and difference to the class LinkedBag

union: return a bag containing the contents of two bags
		e.g. (a, b, b, c).union(b, d, e) == (a, b, b, b, c, d, e)
intersection: return a bag containing only entries found in both bags
		e.g. (a, b, b, c).intersection(b, d, e) == (b)
difference: return a copy of first bag with the second bag's items removed
		e.g. (a, b, b, c).difference(b, d, e) == (a, b, c)

Nathan Ross
Written 10/1/16
*/

#include <iostream>
#include <string>
#include "LinkedBag.h"

//displays the contents of a bag
template<class ItemType>
void displayBag(LinkedBag<ItemType> &bag)
{
	auto bagItems = bag.toVector();
	for (auto &item : bagItems)
		std::cout << item << " ";

	std::cout << std::endl;
}  // end displayBag

int main()
{
	//bags to hold our example data
	LinkedBag<int> hostBag;
	LinkedBag<int> argumentBag;

	//fill bags with example data
	int hostItems[] = { 1, 2, 2, 2, 3 };
	int argumentItems[] = { 1, 1, 2, 4, 5 };

	for (auto &item : hostItems)
		hostBag.add(item);

	for (auto &item : argumentItems)
		argumentBag.add(item);

	//bags to hold the results of operations (using rvalue move assignments)
	LinkedBag<int> unionBag = hostBag.getUnion(argumentBag);
	LinkedBag<int> intersectionBag = hostBag.getIntersection(argumentBag);
	LinkedBag<int> differenceBag = hostBag.getDifference(argumentBag);

	//display results
	std::cout << "Host bag: ";
	displayBag(hostBag);
	std::cout << "Argument bag: ";
	displayBag(argumentBag);
	
	std::cout << std::endl;

	std::cout << "Union bag: ";
	displayBag(unionBag);
	std::cout << "Intersection bag: ";
	displayBag(intersectionBag);
	std::cout << "Difference bag: ";
	displayBag(differenceBag);

	system("pause");
	return 0;
}