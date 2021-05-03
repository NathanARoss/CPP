//QueueInterface.h
#pragma once

template <class T>
class QueueInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool isFull() const = 0;
	virtual bool dequeue() = 0;
	virtual bool enqueue(const T& queueElement) = 0;

	virtual T front() const = 0;
	virtual T back() const = 0;
	virtual void display() const = 0;
	virtual int getNumberOfEntries() const = 0;
};