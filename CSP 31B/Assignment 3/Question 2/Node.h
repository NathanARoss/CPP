// Node.h
//holds an item and a pointer to the next node
#pragma once

template <class ItemType>
class Node
{
private:
	ItemType item;
	Node<ItemType>* pNext;

public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* pNext);
	void setItem(const ItemType& anItem);
	void setNext(Node<ItemType>* pNext);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
}; // end node



template <class ItemType>
Node<ItemType>::Node() : pNext(nullptr)
{
} // end default constructor



template <class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), pNext(nullptr)
{
} // end constructor



template <class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* pNext)
	: item(anItem), pNext(pNext)
{
} // end constructor



template <class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem



template <class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* pNext)
{
	this->pNext = pNext;
} // end setNext



template <class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
} // end getItem



template <class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return pNext;
} // end getNext