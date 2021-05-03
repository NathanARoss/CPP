//lab 14.cpp
//implement LinkQueue<>'s copy constructor, destructor,
//and assignment operator

#include <iostream>
#include <iomanip>
#include "linkedQueue.h"

void displayQueue(LinkedQueue<int> &queue);

int main()
{
	LinkedQueue<int> originalQueue;

	originalQueue.addQueue(3);
	originalQueue.addQueue(1);
	originalQueue.addQueue(10);
	originalQueue.addQueue(8);
	originalQueue.addQueue(44);

	LinkedQueue<int> copiedQueue(originalQueue);
	std::cout << std::setw(16) << "Copied queue: ";
	displayQueue(copiedQueue);

	copiedQueue = originalQueue;
	std::cout << std::setw(16) << "Assigned queue: ";
	displayQueue(copiedQueue);

	std::cout << std::setw(16) << "Original queue: ";
	displayQueue(originalQueue);

	system("pause");
	return 0;
}

void displayQueue(LinkedQueue<int> &queue)
{
	while (!queue.isEmptyQueue())
	{
		std::cout << queue.front() << "  ";
		queue.deleteQueue();
	}
	std::cout << std::endl;
}