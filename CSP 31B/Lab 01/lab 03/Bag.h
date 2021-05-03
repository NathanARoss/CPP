#pragma once
#include <vector>
#include "BagInterface.h"

//Bag interface
template<class ItemType>
class Bag : public BagInterface<ItemType>
{
private:
	std::vector<ItemType> items;

	//returns the position of the specified item, or -1 if not found
	int getIndexOf(const ItemType& target) const;

public:
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	std::vector<ItemType> toVector() const;
};

//Bag implementation
//full definition of all template functions must be visible to all calls to these functions
template<class ItemType>
int Bag<ItemType>::getCurrentSize() const
{
	return items.size();
}

template<class ItemType>
bool Bag<ItemType>::isEmpty() const
{
	return items.size() == 0;
}

template<class ItemType>
bool Bag<ItemType>::add(const ItemType& newEntry)
{
	items.push_back(newEntry);
	return true;

}

template<class ItemType>
bool Bag<ItemType>::remove(const ItemType& anEntry)
{
	size_t locatedIndex = getIndexOf(anEntry);
	bool canRemoveItem = locatedIndex != -1;
	if (canRemoveItem)
	{
		items[locatedIndex] = items[items.size() - 1];
		items.resize(items.size() - 1);
	}

	return canRemoveItem;
}

template<class ItemType>
void Bag<ItemType>::clear()
{
	//call item destructors and set size to 0
	items.clear();
}

template<class ItemType>
int Bag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;

	for (auto& item : items)
	{
		if (item == anEntry)
			++frequency;
	}

	return frequency;
}

template<class ItemType>
bool Bag<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry) > -1;
}

template<class ItemType>
int Bag<ItemType>::getIndexOf(const ItemType& target) const
{
	size_t result = -1;
	size_t searchIndex = 0;

	while (result == -1 && (searchIndex < items.size()))
	{
		if (items[searchIndex] == target)
			result = searchIndex;
		else
			++searchIndex;
	}

	return result;
}

template<class ItemType>
std::vector<ItemType> Bag<ItemType>::toVector() const
{
	return items;
}