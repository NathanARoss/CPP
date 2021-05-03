//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 18-5.

/** A class of entry objects for a hashing implementation of the
ADT dictionary.
@file HashedEntry.h */

#ifndef HASHED_ENTRY_
#define HASHED_ENTRY_

#include <memory>
#include "Entry.h"

template<class KeyType, class ItemType>
class HashedEntry : public Entry<KeyType, ItemType>
{
private:
	std::shared_ptr<HashedEntry<KeyType, ItemType>> nextPtr;

public:
	HashedEntry();
	HashedEntry(KeyType itemKey, ItemType newEntry);
	HashedEntry(KeyType itemKey, ItemType newEntry,
		std::shared_ptr<HashedEntry<KeyType, ItemType>> nextEntryPtr);

	void setNext(std::shared_ptr<HashedEntry<KeyType, ItemType>> nextEntryPtr);
	auto getNext() const;
}; // end HashedEntry

   //#include "HashedEntry.cpp"

   //  Created by Frank M. Carrano and Timothy M. Henry.
   //  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

   /** @file  HashedEntry.cpp */

   //#include "HashedEntry.h"

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry()
{
	Entry<KeyType, ItemType>();
	nextPtr = nullptr;
}  // end

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType itemKey, ItemType newEntry)
{
	Entry<KeyType, ItemType>::setItem(newEntry);
	Entry<KeyType, ItemType>::setKey(itemKey);
	nextPtr = nullptr;
}  // end

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>::HashedEntry(KeyType itemKey, ItemType newEntry,
	std::shared_ptr<HashedEntry<KeyType, ItemType>> nextEntryPtr)
{
	Entry<KeyType, ItemType>::setItem(newEntry);
	Entry<KeyType, ItemType>::setKey(itemKey);
	nextPtr = nextEntryPtr;
}  // end

template<class KeyType, class ItemType>
void HashedEntry<KeyType, ItemType>::setNext(std::shared_ptr<HashedEntry<KeyType, ItemType>> nextEntryPtr)
{
	nextPtr = nextEntryPtr;
}  // end

template<class KeyType, class ItemType>
auto HashedEntry<KeyType, ItemType>::getNext() const
{
	return nextPtr;
}  // end



#endif