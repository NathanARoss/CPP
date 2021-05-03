// StackInterface.h
//Defines the interface for a stack class, used to hide implementation

#pragma once
#include <vector> // std::vector<>
#include <iostream> // std::cout

template <class ItemType>
class StackInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool push(const ItemType& newEntry) = 0;
	virtual bool pop() = 0;
	virtual ItemType peek() const = 0;

	//not virtual to demonstrate default display()
	//ArrayStack and LinkedStack otherwise would override this
	void display();

	//must be defined, called during derived class' destuctors
	virtual ~StackInterface() { }
}; // end StackInterface

   //displays the contents without knowing stack's implementation
template <class ItemType>
void StackInterface<ItemType>::display()
{
	//signature (for debugging)
	std::cout << "StackInterface::display()" << std::endl;

	//keeps track of the items we pop from the stack
	//no functionality is provided to create another stack
	//with the same implementation, but a vector will do
	std::vector<ItemType> copy;

	while (!isEmpty())
	{
		ItemType item = peek();
		pop();
		std::cout << item << ' ';

		//make a copy of the item to add it back later
		copy.push_back(item);
	}

	//add the items back in the order they were removed
	for (int i = copy.size() - 1; i >= 0; --i)
		push(copy[i]);
}