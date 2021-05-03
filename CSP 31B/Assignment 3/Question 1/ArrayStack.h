// ArrayStack.h
//Implements StackInterface.h with fixed sized arrays

#pragma once
#include <cassert>
#include "StackInterface.h"

const int MAX_STACK = 10;

template <class ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:
	ItemType items[MAX_STACK];
	int top;

public:
	ArrayStack();
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;

	//replace the inherited display() with a more specialized one
	void display();
}; // end ArrayStack

   //default constructor sets default top location
template <class ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1)
{
}

template <class ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
	return top < 0;
} // end default constuctor

template <class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry)
{
	bool result = false;

	//only add the item if there is room in the array
	if (top < MAX_STACK - 1)
	{
		result = true;
		++top;
		items[top] = newEntry;
	}

	return result;
} // end push

template <class ItemType>
bool ArrayStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		--top;
		result = true;
	}

	return result;
} // end pop

template <class ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
	//throw error if trying to peek an empty stack
	assert(!isEmpty());

	return items[top];
} // end pop

template <class ItemType>
void ArrayStack<ItemType>::display()
{
	//signature (for debugging)
	std::cout << "ArrayStack::display()" << std::endl;

	//we can read the contents of the array instead of popping items
	for (int i = top; i >= 0; --i)
		std::cout << items[i] << ' ';
} // end display