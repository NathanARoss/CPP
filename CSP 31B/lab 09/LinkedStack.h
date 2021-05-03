// LinkedStack.h
//Implements StackInterface.h using a linked list

#pragma once
#include <cassert> // assert()
#include "StackInterface.h" // StackInterface
#include "Node.h" // Node

template <class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
private:
	//pointer to the first node
	Node<ItemType>* pTop;

public:
	LinkedStack();
	virtual ~LinkedStack();

	bool isEmpty() const;
	bool push(const ItemType& newItem);
	bool pop();
	ItemType peek() const;

	//replace inherited with specialized function
	void display();

	//unique to LinkedStack, removes n items from top of stack
	void remove(int count);
}; // end LinkedStack

template <class ItemType>
LinkedStack<ItemType>::LinkedStack() : pTop(nullptr)
{
} //end default constructor

template <class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	while (!isEmpty())
		pop();
} // end destructor

template <class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return pTop == nullptr;
} // end isEmpty

template <class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	pTop = new Node<ItemType>(newItem, pTop);

	//always room to add more items
	return true;
} // end push

template <class ItemType>
bool LinkedStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		Node<ItemType>* pOldTop = pTop;
		pTop = pTop->getNext();

		pOldTop->setNext(nullptr);
		delete pOldTop;
		pOldTop = nullptr;

		result = true;
	}

	return result;
} // end pop

template <class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
	//throw error if peeking empty stack
	assert(!isEmpty());

	return pTop->getItem();
} // end peek

template <class ItemType>
void LinkedStack<ItemType>::display()
{
	//signature (for debugging)
	std::cout << "LinkedStack::display()" << std::endl;

	//we can follow the node chain instead of popping items
	Node<ItemType>* pNode = pTop;
	while (pNode != nullptr)
	{
		std::cout << pNode->getItem() << ' ';
		pNode = pNode->getNext();
	}
} // end display

template <class ItemType>
void LinkedStack<ItemType>::remove(int count)
{
	bool result = true;
	while (count > 0 && result)
	{
		result = pop();
		--count;
	}
} // end remove