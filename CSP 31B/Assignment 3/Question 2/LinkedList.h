//LinkedList.h
//linked node implementation of ListInterface
#pragma once

#include <assert.h>
#include <stdexcept>

#include "Node.h"

template <class ItemType>
class LinkedList
{
private:
	Node<ItemType>* pHead;
	int itemCount;
	Node<ItemType>* getNodeAt(int position) const;

public:
	LinkedList();
	LinkedList(const LinkedList<ItemType>& aList);
	virtual ~LinkedList();

	bool isEmpty() const;
	int getLength() const;
	bool insert(int position, const ItemType& entry);
	bool remove(int position);
	bool contains(const ItemType& entry) const;
	int find(const ItemType& entry) const;
	void clear();
	ItemType getEntry(int position) const;
	void replace(int position, const ItemType& newEntry);
}; // end LinkedList



template <class ItemType>
LinkedList<ItemType>::LinkedList() : pHead(nullptr), itemCount(0)
{
} // end default constructor



  //copy constructor
template <class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
	: pHead(nullptr), itemCount(aList.getLength())
{
	//add the first node to tack the others to
	if (aList.pHead)
	{
		pHead = new Node<ItemType>(aList.pHead->getItem());

		Node<ItemType> *pCurr = pHead;
		Node<ItemType> *pOther = aList.pHead->getNext();

		//while more nodes exist to copy, tack them on the end of the list
		while (pOther != nullptr)
		{
			auto* pNewNode = new Node<ItemType>(pOther->getItem());
			pCurr->setNext(pNewNode);

			pCurr = pCurr->getNext();
			pOther = pOther->getNext();
		}
	}
}



template <class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
} // end destructor



template <class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount == 0;
} // end isEmpty



template <class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
} // end getLength



template <class ItemType>
bool LinkedList<ItemType>::insert(int position, const ItemType& entry)
{
	bool ableToInsert = (position >= 1) && (position <= itemCount + 1);
	if (ableToInsert)
	{
		Node<ItemType>* pNewNode = new Node<ItemType>(entry);

		if (position == 1)
		{
			pNewNode->setNext(pHead);
			pHead = pNewNode;
		}
		else
		{
			Node<ItemType>* pPrev = getNodeAt(position - 1);
			pNewNode->setNext(pPrev->getNext());
			pPrev->setNext(pNewNode);
		} // end if

		++itemCount;
	} // end if

	return ableToInsert;
} // end insert



template <class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<ItemType>* pCurr = nullptr;
		if (position = 1)
		{
			pCurr = pHead;
			pHead = pHead->getNext();
		}
		else
		{
			Node<ItemType>* pPrev = getNodeAt(position - 1);
			pCurr = pPrev->getNext();
			pPrev->setNext(pCurr->getNext());
		} // end if

		pCurr->setNext(nullptr);
		delete pCurr;
		pCurr = nullptr;

		--itemCount;
	} // end if

	return ableToRemove;
} // end remove



template <class ItemType>
bool LinkedList<ItemType>::contains(const ItemType& entry) const
{
	for (int i = 1; i <= itemCount; ++i)
	{
		if (getEntry(i) == entry)
			return true;
	}
	return false;
}



template <class ItemType>
int LinkedList<ItemType>::find(const ItemType& entry) const
{
	for (int i = 1; i <= itemCount; ++i)
	{
		if (getEntry(i) == entry)
			return i;
	}
	return -1;
} // end find



template <class ItemType>
void LinkedList<ItemType>::clear()
{
	while (!isEmpty())
		remove(1);
} // end clear

template <class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
{
	//enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<ItemType>* pNode = getNodeAt(position);
		return pNode->getItem();
	}
	else
	{
		std::logic_error error("getEntry() called with invalid positon "
			+ std::to_string(position) + ".");
		throw(error);
	} // end if
} // end getEntry


template <class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
	assert((position >= 1) && (position <= itemCount));

	Node<ItemType>* pCurr = pHead;
	for (int skip = 1; skip < position; ++skip)
		pCurr = pCurr->getNext();

	return pCurr;
} // end getNodeAt



  //overwrites the entry at the given position with a new entry value
template <class ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType& newEntry)
{
	//enforce precondition
	bool ableToReplace = (position >= 1) && (position <= itemCount);
	if (ableToReplace)
	{
		Node<ItemType>* pNode = getNodeAt(position);
		pNode->setItem(newEntry); //only change from getEntry(int)
	}
	else
	{
		std::logic_error errMessage("replace() called with invalid position "
			+ std::to_string(position) + ".");
		throw(errMessage);
	} // end if
} // end replace