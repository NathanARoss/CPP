//ArrayQueue.h
#pragma once

#include "QueueInterface.h"
#include <stdexcept>
#include <iostream>

template <class T>
class ArrayQueue : public QueueInterface<T>
{
private:
	static const int DEFAULT_CAPACITY = 100;
	T items[DEFAULT_CAPACITY];
	int frontSubscript, count;

public:
	ArrayQueue();
	//copy constructor and destructor supplied by compiler
	bool isEmpty() const override;
	bool isFull() const override;
	bool enqueue(const T& newEntry) override;
	bool dequeue() override;

	T front() const override;
	T back() const override;
	void display() const override;
	int getNumberOfEntries() const override;
};

template <class T>
ArrayQueue<T>::ArrayQueue() : frontSubscript(0), count(0)
{ } // end default constructor

template <class T>
bool ArrayQueue<T>::isEmpty() const
{
	return count == 0;
} // end isEmpty

template <class T>
bool ArrayQueue<T>::isFull() const
{
	return count == DEFAULT_CAPACITY;
} // end isEmpty

template <class T>
bool ArrayQueue<T>::enqueue(const T& newEntry)
{
	bool result = false;
	if (count < DEFAULT_CAPACITY)
	{
		int position = (frontSubscript + count) % DEFAULT_CAPACITY;
		items[position] = newEntry;
		++count;
		result = true;
	}

	return result;
} // end enqueue

template <class T>
bool ArrayQueue<T>::dequeue()
{
	bool result = false;
	if (!isEmpty())
	{
		frontSubscript = (frontSubscript + 1) % DEFAULT_CAPACITY;
		--count;
		result = true;
	}

	return result;
} // end dequeue

template <class T>
T ArrayQueue<T>::front() const
{
	//throw an error if the user tries to read an empty queue
	if (isEmpty())
		throw std::logic_error("front() called with empty queue");

	return items[frontSubscript];
} // end peekFront

template <class T>
T ArrayQueue<T>::back() const
{
	//throw an error if the user tries to read an empty queue
	if (isEmpty())
		throw std::logic_error("back() called with empty queue");

	int subscript = (frontSubscript + count) % DEFAULT_CAPACITY;
	return items[subscript];
} // end peekFront

template <class T>
void ArrayQueue<T>::display() const
{
	if (!isEmpty())
	{
		for (int i = 0; i < count; ++i)
		{
			int subscript = (frontSubscript + i) % DEFAULT_CAPACITY;
			std::cout << items[subscript] << ' ';
		}
	}
	std::cout << std::endl;
}

template <class T>
int ArrayQueue<T>::getNumberOfEntries() const
{
	return count;
}