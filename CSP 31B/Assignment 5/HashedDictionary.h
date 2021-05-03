//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file  HashedDictionary.h */

#ifndef HASHED_DICTIONARY_
#define HASHED_DICTIONARY_

#include "DictionaryInterface.h"
#include "HashedEntry.h"
#include "NotFoundException.h"
#include <memory>
#include <cmath>    // For sqrt
#include <iostream> // For testing
#include <unordered_map>


template <class KeyType, class ItemType>
using hashTableType = std::shared_ptr<HashedEntry<KeyType, ItemType>>[];

template <class KeyType, class ItemType>
class HashedDictionary : public DictionaryInterface<KeyType, ItemType>
{
private:
	// creates a unique pointer to an array of shared HashedEntry pointers
	std::unique_ptr<hashTableType<KeyType, ItemType>> hashTable;  // Array of pointers to entries
	int itemCount;                               // Count of dictionary entries
	int hashTableSize;                           // Table size must be prime
	static const int DEFAULT_CAPACITY = 101;

	void destroyDictionary();
	int getHashIndex(const KeyType& itemKey) const;
	int getNextPrime(int number) const;
	bool isPrime(int number) const;

public:
	HashedDictionary();
	HashedDictionary(int maxNumberOfEntries);
	HashedDictionary(const HashedDictionary<KeyType, ItemType>& dict);

	virtual ~HashedDictionary();

	bool isEmpty() const;
	int getNumberOfItems() const;
	void clear();
	bool add(const KeyType& itemKey, const ItemType& newItem);
	bool remove(const KeyType& itemKey);
	ItemType getItem(const KeyType& itemKey) const;
	bool contains(const KeyType& itemKey) const;
	bool replace(const KeyType& searchKey, const ItemType& replacementItem);
	void traverse(void visit(Entry<int, std::string>&)) const;
}; // end HashedDictionary

   //#include "HashedDictionary.cpp"

   //  Created by Frank M. Carrano and Timothy M. Henry.
   //  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

   /** @file  HashedDictionary.cpp */

   // Separate chaining resolves collisions


   //////////////////////////////////////////////////////////////////////
   // Private helper methods
   //////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::destroyDictionary()
{
	for (int i = 0; i < hashTableSize; i++)
	{
		// If there are hashed entries at this location,
		// we need to delete them
		while (hashTable[i] != nullptr)
		{
			hashTable[i] = hashTable[i]->getNext();
		}  // end while
	}  // end for

	itemCount = 0;
}  // end destroyDictionary

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType& key) const
{
	// We are creating a hash function type called hashFunction that hashes "KeyType"
	// First we create an an unordered_map object for our KeyType and ItemType
	std::unordered_map<KeyType, ItemType> mapper;

	// Then we call the hash_function method to return the hash function
	// for the KeyType and assign it to 'hashFunction'
	typename std::unordered_map<KeyType, ItemType>::hasher hashFunction = mapper.hash_function();

	// static_cast needed since hashFunction returns an unsigned long
	return static_cast<int>(hashFunction(key) % hashTableSize);
} // end getHashIndex

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNextPrime(int number) const
{
	bool foundPrime = false;
	if ((number % 2) == 0)
		number++;

	while (!foundPrime)
	{
		if ((number % 5 == 0) || !isPrime(number))
		{
			number = number + 2;
		}
		else
			foundPrime = true;
	}  // end

	return number;
}  // end getNextPrime

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isPrime(int number) const
{
	bool isPrimeNumber = true;                 // Assume prime, prove otherwise

	if ((number == 2) || (number == 3))        // Smallest primes
		isPrimeNumber = true;
	else
	{
		if ((number % 2 == 0) || (number < 2))  // Even number or ineligible
			isPrimeNumber = false;
		else
		{
			int root = sqrt(number);             // Limit of search
			int i = 3;
			do
			{
				if (number % i == 0)               // Not prime
					isPrimeNumber = false;
				else
					i = i + 2;

			} while ((isPrimeNumber == true) && (i <= root));
		}  // end if
	}  // endif

	return isPrimeNumber;
}  // end isPrime

   //////////////////////////////////////////////////////////////////////
   // Constructors & Destructor
   //////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
	:itemCount(0), hashTableSize(DEFAULT_CAPACITY)
{
	// All shared pointers in array initialized to nullptr & reference count zero
	hashTable = std::make_unique<hashTableType<KeyType, ItemType>>(DEFAULT_CAPACITY);
}  // end

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int maxNumberOfEntries)
	:itemCount(0)
{
	hashTableSize = getNextPrime(maxNumberOfEntries);

	// All shared pointers in array initialized to nullptr & reference count zero
	hashTable = std::make_unique<hashTableType<KeyType, ItemType>>(hashTableSize);
}  // end

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(const
	HashedDictionary<KeyType, ItemType>& dict)
	:itemCount(dict.itemCount), hashTableSize(dict.hashTableSize)
{
	hashTable = std::make_unique<hashTableType<KeyType, ItemType>>(dict.maxItems);
	for (auto index : indices(dict.itemCount))
	{
		hashTable[index] = dict.hashTable[index];
	}  // end for
}  // end

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary()
{
	destroyDictionary();
} // end destructor

  ////////////////////////////////////////////////////////////////////
  // Status and public maintenance (clear) methods
  //////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const
{
	return (itemCount == 0);
} // end isEmpty

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const
{
	return itemCount;
} // end getNumberOfItems

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	destroyDictionary();
} // end clear

  ///////////////////////////////////////////////////////////////////
  // Container methods (add, remove, getItem, contains, traverse)
  //////////////////////////////////////////////////////////////////////

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
	// Create entry to add to dictionary
	auto entryToAddPtr = std::make_shared<HashedEntry<KeyType, ItemType>>(searchKey, newItem);

	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);

	// Add the entry to the chain at itemHashIndex
	if (hashTable[itemHashIndex] == nullptr)
	{
		hashTable[itemHashIndex] = entryToAddPtr;
	}
	else
	{
		entryToAddPtr->setNext(hashTable[itemHashIndex]);
		hashTable[itemHashIndex] = entryToAddPtr;
	} // end if

	return true;
} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
	bool itemFound = false;
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	if (hashTable[itemHashIndex] != nullptr)
	{
		// Special case - first node has target
		if (searchKey == hashTable[itemHashIndex]->getKey()) {
			hashTable[itemHashIndex] = hashTable[itemHashIndex]->getNext();
			itemFound = true;
		}
		else {// Search the rest of the chain      {
			auto prevPtr = hashTable[itemHashIndex];
			auto curPtr = prevPtr->getNext();
			while ((curPtr != nullptr) && !itemFound)
			{
				// Found item in chain so remove that node
				if (searchKey == curPtr->getKey()) {
					prevPtr->setNext(curPtr->getNext());
					itemFound = true;
				}
				else {// Look at next entry in chain
					prevPtr = curPtr;
					curPtr = curPtr->getNext();
				} // end if
			} // end while
		} // end if
	} // end if
	return itemFound;
} // end remove

template <class KeyType, class ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType& searchKey) const
{
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	auto chainPtr = hashTable[itemHashIndex];

	// Short circuit evaluation is important here
	while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey()))
	{
		chainPtr = chainPtr->getNext();
	} // end while

	if (chainPtr == nullptr)
		throw NotFoundException("\n\nItem not found in Dictionary!\n\n");

	return chainPtr->getItem();
} // end getItem

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType& searchKey) const
{
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	auto chainPtr = hashTable[itemHashIndex];

	// Short circuit evaluation is important here
	while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey()))
	{
		chainPtr = chainPtr->getNext();
	} // end while

	return (chainPtr != nullptr);
} // end contains

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::replace(const KeyType& searchKey, const ItemType& replacementItem)
{
	// Compute the hashed index into the array
	int itemHashIndex = getHashIndex(searchKey);
	auto chainPtr = hashTable[itemHashIndex];

	// Short circuit evaluation is important here
	while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey()))
	{
		chainPtr = chainPtr->getNext();
	} // end while

	bool found = (chainPtr == nullptr);
	if (found)
		chainPtr->setItem(replacementItem);

	return found;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void visit(Entry<int, std::string>&)) const
{
	// Simple because the array is sorted.
	for (int index = 0; index<hashTableSize; index++)
	{
		// cout<<"\n Index: " << index << "  :"; // for testing
		auto chainPtr = hashTable[index];
		while (chainPtr != nullptr)
		{
			ItemType currentItem = chainPtr->getItem();
			visit(Entry<int, std::string>(index, currentItem));
			chainPtr = chainPtr->getNext();
		} // end while
	}  // end for
}  //end traverse

#endif
