#pragma once
template<class ItemType>
class BagInterface
{
public:
	//get a count of items in bag
	virtual int getCurrentSize() const = 0;

	//get if bag holds any items
	virtual bool isEmpty() const = 0;

	//add an entry to the end of the bag
	virtual bool add(const ItemType& newEntry) = 0;

	//remove one of the given entry if possible
	virtual bool remove(const ItemType& anEntry) = 0;

	//remove all items form bag
	virtual void clear() = 0;

	//returns the number of occurances of given item
	virtual int getFrequencyOf(const ItemType& anEntry) const = 0;

	//returns if bag contains given item
	virtual bool contains(const ItemType& anEntry) const = 0;

	//returns a vector containing the contents of this bag
	virtual std::vector<ItemType> toVector() const = 0;

	~BagInterface() {}
};