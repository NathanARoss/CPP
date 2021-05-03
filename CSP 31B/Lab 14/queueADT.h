//Header file: queueADT.h

#ifndef H_QueueADT
#define H_QueueADT

template <class T>
class QueueADT
{
public:
	virtual bool isEmptyQueue() const = 0;
	virtual bool isFullQueue() const = 0;
	virtual void initializeQueue() = 0;

	virtual T front() const = 0;

	virtual T back() const = 0;

	virtual void addQueue(const T& queueElement) = 0;

	virtual void deleteQueue() = 0;

};


#endif