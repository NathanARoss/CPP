//Assignment 4.cpp
//implement LinkQueue<>'s copy constructor, display(), and getNumberOfEntries()

#include <iostream>
#include <iomanip>
#include "linkedQueue.h"
#include "ArrayQueue.h"

template<class T>
void displayQueue(QueueInterface<T> &queue);

int main()
{
	LinkedQueue<int> originalQueue;

	for (int i : { 5, 6, 3, 4, 8, 6, 2 })
		originalQueue.enqueue(i);

	LinkedQueue<int> copiedQueue(originalQueue);
	std::cout << std::setw(18) << "Copied queue: ";
	displayQueue(copiedQueue);

	copiedQueue = originalQueue;
	std::cout << std::setw(18) << "Assigned queue: ";
	displayQueue(copiedQueue);

	std::cout << std::setw(18) << "Original queue: ";
	displayQueue(originalQueue);

	std::cout << std::endl;
	ArrayQueue<int> arrayQueue;

	for (int i : { 1, 5, 3, 5, 8, 3, 5, 7, 2 })
		arrayQueue.enqueue(i);

	std::cout << std::setw(18) << "Array queue: ";
	displayQueue(arrayQueue);


	system("pause");
	return 0;
}

template<class T>
void displayQueue(QueueInterface<T> &queue)
{
	queue.display();
	std::cout << std::setw(18) << "size: ";
	std::cout << queue.getNumberOfEntries() << std::endl;
}