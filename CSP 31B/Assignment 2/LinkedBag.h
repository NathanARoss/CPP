#pragma once
//Â  Created by Frank M. Carrano and Timothy M. Henry.
//Â  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
@file LinkedBag.h
Listing 4-3 */
#ifndef LINKED_BAG_
#define LINKED_BAG_

#include "Node.h"
#include <vector>
#include <cstddef>

template<class ItemType>
class LinkedBag
{
private:
	Node<ItemType>* headPtr; // Pointer to first node
	size_t itemCount;           // Current count of bag items
	Node<ItemType>* getPointerTo(const ItemType& target) const;

public:
	LinkedBag();
	LinkedBag(const LinkedBag<ItemType>& aBag); // Copy constructor
	LinkedBag(LinkedBag<ItemType> &&bagToSteal); // Move constructor
	virtual ~LinkedBag();                       // Destructor should be virtual

	// Assignment operator
	//uses move constructor to create bagToSteal when using rvalues
	//allows code reuse between move constructor and move assignment
	LinkedBag<ItemType>& operator=(LinkedBag<ItemType> bagToSteal);

	size_t getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	std::vector<ItemType> toVector() const;

	//bag combining functions
	LinkedBag<ItemType> getUnion(const LinkedBag<ItemType> &aBag) const;
	LinkedBag<ItemType> getIntersection(const LinkedBag<ItemType> &aBag) const;
	LinkedBag<ItemType> getDifference(const LinkedBag<ItemType> &aBag) const;
}; // end LinkedBag


   /* class implementation, must be inside header file */

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) : headPtr(nullptr), itemCount(0)
{
	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty
	else {
		// Copy first node
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());

		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
		origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer

		while (origChainPtr != nullptr) {
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();
			// Create a new node containing the next item
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);
			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();
			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}  // end while
		newChainPtr->setNext(nullptr);              // Flag end of chain
	}  // end if
}  // end copy constructor

//move constructor, called during assignment opperator when using rvalues as arguments
template<class ItemType>
LinkedBag<ItemType>::LinkedBag(LinkedBag<ItemType>&& bagToSteal) : headPtr(nullptr), itemCount(0)
{
	//take over data and memory objects
	headPtr = bagToSteal.headPtr;
	itemCount = bagToSteal.itemCount;

	//prevent the pointer chain from deallocating
	bagToSteal.headPtr = nullptr;
	bagToSteal.itemCount = 0;
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
	clear();
}  // end destructor

//swap non-dynamic memory (and addresses) between host and temp object
template<class ItemType>
LinkedBag<ItemType>& LinkedBag<ItemType>::operator=(LinkedBag<ItemType> bagToSteal)
{
	std::swap(headPtr, bagToSteal.headPtr);
	std::swap(itemCount, bagToSteal.itemCount);
	return *this;
}

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return (headPtr == nullptr);
}  // end isEmpty

template<class ItemType>
size_t LinkedBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
	// replace the head of the chain with a new link connected to the old head
	headPtr = new Node<ItemType>(newEntry, headPtr);

	//always able to add items
	itemCount++;
	return true;
}  // end add

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const
{
	std::vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while (curPtr != nullptr)
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while

	return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem)
	{
		// Copy data from first node to located node
		entryNodePtr->setItem(headPtr->getItem());

		// Delete first node
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	} // end if

	return canRemoveItem;
}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear()
{
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr)
	{
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;

		nodeToDeletePtr = headPtr;
	}  // end while
	   // headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while (curPtr != nullptr)
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		} // end if

		counter++;
		curPtr = curPtr->getNext();
	} // end while

	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
	bool found = false;
	Node<ItemType>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	} // end while

	return curPtr;
} // end getPointerTo

#endif

//return a new bag containing items from host bag and aBag
template<class ItemType>
LinkedBag<ItemType> LinkedBag<ItemType>::getUnion(const LinkedBag<ItemType> &aBag) const
{
	//make a copy of the host bag, unionBag contains all of host bag
	LinkedBag<ItemType> unionBag(*this);

	//copy items from aBagContents to unionBag
	auto aBagContents = aBag.toVector();
	for (auto &item : aBagContents)
	{
		unionBag.add(item);
	}

	//return as rvalue
	return unionBag;
}

//return bag containing items held by both host bag and aBag
template<class ItemType>
LinkedBag<ItemType> LinkedBag<ItemType>::getIntersection(const LinkedBag<ItemType> &aBag) const
{
	//make a copy of host bag, items must exist in host to exist in intersection
	LinkedBag<ItemType> intersectionBag(*this);

	//a modifiable copy of aBag
	LinkedBag<ItemType> aBagCopy(aBag);

	//loop through all items in host bag, remove items not found in parameter bag
	auto possibleItems = intersectionBag.toVector();
	for (auto &item : possibleItems)
	{
		if (aBagCopy.contains(item))
			//preserve duplicate items in intersectionBag
			aBagCopy.remove(item);
		else
			//item not found in both bags
			intersectionBag.remove(item);
	}

	//return as rvalue
	return intersectionBag;
}

//return bag containing items held by host bag but not by aBag
template<class ItemType>
LinkedBag<ItemType> LinkedBag<ItemType>::getDifference(const LinkedBag<ItemType> &aBag) const
{
	//make a copy of host bag, items must exist in host to exist in difference
	LinkedBag<ItemType> differenceBag(*this);

	//a modifiable copy of aBag
	LinkedBag<ItemType> aBagCopy(aBag);

	//loop through all items in host bag, remove items found in parameter bag
	auto possibleItems = differenceBag.toVector();
	for (auto &item : possibleItems)
	{
		if (aBagCopy.contains(item))
		{
			//preserve duplicate items in differenceBag
			aBagCopy.remove(item);

			//we don't want items found in both bags
			differenceBag.remove(item);
		}
	}

	//return as rvalue
	return differenceBag;
}