//LinkedQueue.h
#pragma once

#include <iostream>
#include <cassert>
#include <memory>
#include "QueueInterface.h"

using namespace std;

//Definition of the node
template <class T>
struct Node
{
	T info;
	std::shared_ptr<Node<T>> link;

	Node() {}
	Node(T info) : info(info) {}
	Node(T info, std::shared_ptr<Node<T>> link) : info(info), link(link) {}
};


template <class T>
class LinkedQueue : public QueueInterface<T>
{
private:
	std::shared_ptr<Node<T>> queueFront;
	std::shared_ptr<Node<T>> queueRear;
public:
	LinkedQueue(); //default constructor
	~LinkedQueue(); //Destructor
	LinkedQueue(const LinkedQueue<T>& otherQueue); //Copy constructor
	const LinkedQueue<T>& operator= (const LinkedQueue<T>&);

	bool isEmpty() const override;
	bool isFull() const override;
	bool enqueue(const T& queueElement) override;
	bool dequeue() override;

	T front() const override;
	T back() const override;
	void display() const override;
	int getNumberOfEntries() const override;
};


template <class T>
LinkedQueue<T>::LinkedQueue()
{
} //end default construtor

template <class T>
LinkedQueue<T>::~LinkedQueue()
{
	queueFront.reset();
	queueRear.reset();
} //end destructor

template <class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
{
	if (other.queueFront)
	{
		queueFront = std::make_shared<Node<T>>(other.queueFront->info);
		queueRear = queueFront;

		//loop until we reach the last node
		auto current = other.queueFront->link;
		while (current)
		{
			queueRear->link = std::make_shared<Node<T>>(current->info);
			queueRear = queueRear->link;
			current = current->link;
		}
	}
}//end copy constructor

template <class T>
const LinkedQueue<T>& LinkedQueue<T>::operator= (const LinkedQueue<T>& other)
{
	//check for self assignment
	if (this != &other)
	{
		//create a copy of the queue and steal its pointers
		LinkedQueue<T> copy(other);
		this->queueFront = copy.queueFront;
		this->queueRear = copy.queueRear;
	}

	return *this;
} //end assignment operator


template<class T>
bool LinkedQueue<T>::isEmpty() const
{
	return(!queueFront);
} //end

template<class T>
bool LinkedQueue<T>::isFull() const
{
	return false;
} //end isFullQueue


template <class T>
bool LinkedQueue<T>::enqueue(const T& newElement)
{
	auto newNode = std::make_shared<Node<T>>(newElement);

	if (!queueFront) //if initially the queue is empty
	{
		queueFront = newNode;
		queueRear = newNode;
	}
	else        //add newNode at the end
	{
		queueRear->link = newNode;
		queueRear = queueRear->link;
	}

	return true;
}//end addQueue

template <class T>
bool LinkedQueue<T>::dequeue()
{
	if (queueFront)
	{
		queueFront = queueFront->link;
		if (!queueFront)
			queueRear.reset();
	}
	else
		std::cout << "Cannot dequeue an empty queue" << std::endl;

	return true;
}//end deleteQueue


template <class T>
T LinkedQueue<T>::front() const
{
	assert(queueFront);
	return queueFront->info;
} //end front

template <class T>
T LinkedQueue<T>::back() const
{
	assert(queueRear);
	return queueRear->info;
} //end back

template <class T>
void LinkedQueue<T>::display() const
{
	std::shared_ptr<Node<T>> current = queueFront;
	while (current)
	{
		std::cout << current->info << ' ';
		current = current->link;
	}
	std::cout << std::endl;
}


template <class T>
int LinkedQueue<T>::getNumberOfEntries() const
{
	int entryCount = 0;

	std::shared_ptr<Node<T>> current = queueFront;
	while (current)
	{
		++entryCount;
		current = current->link;
	}

	return entryCount;
}