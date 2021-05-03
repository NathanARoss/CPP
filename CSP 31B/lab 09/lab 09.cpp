//lab 09.cpp
//Contains entrypoint, demonstrates multiple implementations of stacks
//and specialized implementations of inherited functions for derived classes
//Also tests a remove(n) function to pop n items from a stack

#include "ArrayStack.h" // ArrayStack, StackInterface
#include "LinkedStack.h" // LinkedStack, StackInterface

int main()
{
	//both use their derived class pointers, StackInterface's display() function
	//is non-virtual for testing purposes, so these cannot be StackInterface pointers
	ArrayStack<int>* pArrayStack = new ArrayStack<int>();
	LinkedStack<int>* pLinkedStack = new LinkedStack<int>();

	//Items added to both stacks because I removed LinkedStack's copy constructor
	int items[] = { 1,2,3,4,5,6 };
	for (int item : items)
	{
		pArrayStack->push(item);
		pLinkedStack->push(item);
	}
	
	//test out StackInterface's display() function
	StackInterface<int>* pStackInterface = pArrayStack;

	pStackInterface->display();
	std::cout << std::endl << std::endl;

	//test ArrayStack and LinkedStack's specialized display() function
	pArrayStack->display();
	std::cout << std::endl << std::endl;

	pLinkedStack->display();
	std::cout << std::endl << std::endl;

	//test LinkStack's remove(n) function
	std::cout << "Removing 3 items from LinkedStack" << std::endl;
	pLinkedStack->remove(3);
	pLinkedStack->display();
	std::cout << std::endl << std::endl;

	//compiled and ran from visual studio, pause before exiting
	system("pause");
	return 0;
}