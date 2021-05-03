//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 18-4.

/** A binary search tree implementation of the ADT dictionary
that organizes its data items in sorted search-key order.
Search keys in the dictionary are unique.
@file TreeDictionary.h */

#ifndef TREE_DICTIONARY_
#define TREE_DICTIONARY_

#include <iostream>
#include "DictionaryInterface.h"
#include "Entry.h"
#include "NotFoundException.h"
#include "BinarySearchTree.h"

template <class KeyType, class ItemType>
class TreeDictionary : public DictionaryInterface<KeyType, ItemType>
{
private:
	// Binary search tree of dictionary entries
	BinarySearchTree<Entry<KeyType, ItemType>> itemTree;

public:
	TreeDictionary();
	TreeDictionary(const TreeDictionary<KeyType, ItemType>& dict);
	virtual ~TreeDictionary();

	// The declarations of the public methods appear here and are the
	// same as given in Listing 18-3 for the class ArrayDictionary.

	bool isEmpty() const;
	int getNumberOfItems() const;
	bool add(const KeyType& searchKey, const ItemType& newItem);
	bool remove(const KeyType& searchKey);
	void clear();
	ItemType getItem(const KeyType& searchKey) const;
	bool contains(const KeyType& searchKey) const;
	bool replace(const KeyType& searchKey, const ItemType& replacementItem);

	/** Traverses the items in this dictionary in sorted search-key order
	and calls a given client function once for each item. */
	void traverse(void visit(Entry<int, std::string>&)) const;
}; // end TreeDictionary

   //#include "TreeDictionary.cpp"

   //  Created by Frank M. Carrano and Timothy M. Henry.
   //  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

   /** @file TreeDictionary.cpp */




template <class KeyType, class ItemType>
TreeDictionary<KeyType, ItemType>::TreeDictionary()
{
}  // end default constructor

template <class KeyType, class ItemType>
TreeDictionary<KeyType, ItemType>::TreeDictionary(const TreeDictionary<KeyType, ItemType>& dict) : itemTree(dict.itemTree)
{
}  // end copy constructor

template <class KeyType, class ItemType>
TreeDictionary<KeyType, ItemType>::~TreeDictionary()
{
	itemTree.clear();
}  // end destructor

template <class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::isEmpty() const
{
	return itemTree.isEmpty();
}  // end isEmpty

template <class KeyType, class ItemType>
int TreeDictionary<KeyType, ItemType>::getNumberOfItems() const
{
	return itemTree.getNumberOfNodes();
}  // end getNumberOfItems

template <class KeyType, class ItemType>
void TreeDictionary<KeyType, ItemType>::clear()
{
	itemTree.clear();
}  // end clear

template <class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::add(const KeyType& searchKey,
	const ItemType& newItem)
{
	return itemTree.add(Entry<KeyType, ItemType>(searchKey, newItem));
} // end add

template <class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::remove(const KeyType& itemKey)
{
	return itemTree.remove(Entry<KeyType, ItemType>(itemKey, ItemType()));
}  // end remove

template <class KeyType, class ItemType>
ItemType TreeDictionary<KeyType, ItemType>::getItem(const KeyType& itemKey) const
{
	Entry<KeyType, ItemType> theEntry = itemTree.getEntry(Entry<KeyType, ItemType>(itemKey, ItemType()));
	return theEntry.getItem();
}  // end getItem

template <class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::contains(const KeyType& searchKey) const
{
	return itemTree.contains(Entry<KeyType, ItemType>(searchKey, ItemType()));
}  // end contains

template <class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::replace(const KeyType& searchKey, const ItemType& replacementItem)
{
	Entry<KeyType, ItemType> replacementEntry(searchKey, replacementItem);

	//entries are equal if the search keys are equal
	//the tree will find the item by replacementItem's key
	return itemTree.replace(replacementEntry, replacementEntry);
}

template <class KeyType, class ItemType>
void TreeDictionary<KeyType, ItemType>::traverse(void visit(Entry<int, std::string>&)) const
{
	itemTree.inorderTraverse(visit);
}  // end traverse



#endif