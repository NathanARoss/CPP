//Header file LinkedQueue.h

#ifndef H_LinkedQueue
#define H_LinkedQueue

#include <iostream>
#include <cassert>
#include "queueADT.h"

using namespace std;

//Definition of the node
template <class T>
struct Node
{
	T info;
	Node<T> *link;
};


template <class T>
class LinkedQueue : public QueueADT<T>
{
private:
	Node<T> *queueFront;
	Node<T> *queueRear;
public:
	const LinkedQueue<T>& operator=
		(const LinkedQueue<T>&);

	bool isEmptyQueue() const;

	bool isFullQueue() const;

	void initializeQueue();
	T front() const;
	T back() const;

	void addQueue(const T& queueElement);
	void deleteQueue();

	LinkedQueue();
	//Default constructor
	LinkedQueue(const LinkedQueue<T>& otherQueue);
	//Copy constructor
	~LinkedQueue();
	//Destructor
};

//Default constructor
template<class T>
LinkedQueue<T>::LinkedQueue()
{
	queueFront = nullptr; //set front to null
	queueRear = nullptr;  //set rear to null
} //end default constructor

template<class T>
bool LinkedQueue<T>::isEmptyQueue() const
{
	return(queueFront == nullptr);
} //end

template<class T>
bool LinkedQueue<T>::isFullQueue() const
{
	return false;
} //end isFullQueue

template <class T>
void LinkedQueue<T>::initializeQueue()
{
	Node<T> *temp;

	while (queueFront != nullptr)  //while there are elements left
								//in the queue
	{
		temp = queueFront;  //set temp to point to the
							//current node
		queueFront = queueFront->link;  //advance first to
										//the next node
		delete temp;    //deallocate memory occupied by temp
	}

	queueRear = nullptr;  //set rear to NULL
} //end initializeQueue


template <class T>
void LinkedQueue<T>::addQueue(const T& newElement)
{
	Node<T> *newNode;

	newNode = new Node<T>;   //create the node

	newNode->info = newElement; //store the info
	newNode->link = nullptr;  //initialize the link field to NULL

	if (queueFront == nullptr) //if initially the queue is empty
	{
		queueFront = newNode;
		queueRear = newNode;
	}
	else        //add newNode at the end
	{
		queueRear->link = newNode;
		queueRear = queueRear->link;
	}
}//end addQueue

template <class T>
T LinkedQueue<T>::front() const
{
	assert(queueFront != nullptr);
	return queueFront->info;
} //end front

template <class T>
T LinkedQueue<T>::back() const
{
	assert(queueRear != nullptr);
	return queueRear->info;
} //end back

template <class T>
void LinkedQueue<T>::deleteQueue()
{
	Node<T> *temp;

	if (!isEmptyQueue())
	{
		temp = queueFront;  //make temp point to the
							//first node
		queueFront = queueFront->link; //advance queueFront

		delete temp;    //delete the first node

		if (queueFront == nullptr) //if after deletion the
								//queue is empty
			queueRear = nullptr;   //set queueRear to NULL
	}
	else
		cout << "Cannot remove from an empty queue" << endl;
}//end deleteQueue


 //Destructor (similar implementation to deleteQueue())
template <class T>
LinkedQueue<T>::~LinkedQueue()
{
	//if the queue is empty, this loop will never start
	while (queueFront != nullptr)
	{
		Node<T> *temp = queueFront;
		queueFront = queueFront->link;
		delete temp;
	}
	queueRear = nullptr;
} //end destructor

 //assignment operator
template <class T>
const LinkedQueue<T>& LinkedQueue<T>::operator= (const LinkedQueue<T>& other)
{
	//deallocate existing nodes
	this->~LinkedQueue();

	//create a copy of the queue and steal its pointers
	LinkedQueue<T>* copy = new LinkedQueue<T>(other);
	this->queueFront = copy->queueFront;
	this->queueRear = copy->queueRear;

	return *this;
} //end assignment operator

  //copy constructor
template <class T>
LinkedQueue<T>::LinkedQueue (const LinkedQueue<T>& other)
{
	if (other.queueFront != nullptr)
	{
		queueFront = queueRear = new Node<T>;
		queueFront->info = other.queueFront->info;

		//loop until we reach the last node
		Node<T> *current = other.queueFront;
		while (current->link != nullptr)
		{
			queueRear->link = new Node<T>;
			queueRear = queueRear->link;

			current = current->link;
			queueRear->info = current->info;
		}

		queueRear->link = nullptr;
	}
	else
		queueFront = queueRear = nullptr;
}//end copy constructor

#endif
