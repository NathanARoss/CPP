//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <iostream>
#include <string>
#include "ArrayDictionary.h"
#include "BinaryNodeTree.h"

#include <string>

using std::cout;
using std::endl;

void displayInt(int& anItem);
void displayEntry(Entry<int, std::string>& anItem);
void testTreeReplace();
void testIterativeTreeTraversal();
void testDictionaryReplace();


int main()
{
	testTreeReplace();
	cout << endl;
	cout << endl;
	testIterativeTreeTraversal();
	cout << endl;
	cout << endl;
	testDictionaryReplace();
	cout << endl;
	cout << endl;

	system("pause");
	return 0;
}  // end main

void displayEntry(Entry<int, std::string>& anItem)
{
	cout << anItem.getItem() << ", ";
}

void displayInt(int& anItem)
{
	cout << anItem << ", ";
}

void testTreeReplace()
{
	BinaryTreeInterface<int> *tree = new BinaryNodeTree<int>();

	for (int i : { 0, 1, 2, 3, 4, 5, 6, 7 })
		tree->add(i);

	cout << "tree contents:\t\t";
	tree->inorderTraverse(displayInt);
	cout << endl;

	cout << "Replacing 2 with 57\n";
	tree->replace(2, 57);

	cout << "Replacing 6 with 106\n";
	tree->replace(6, 106);

	cout << "tree contents:\t\t";
	tree->inorderTraverse(displayInt);
	cout << endl;

	delete tree;
}

void testIterativeTreeTraversal()
{
	BinaryTreeInterface<int> *tree = new BinaryNodeTree<int>();

	for (int i : { 0, 1, 2, 3, 4, 5, 6, 7 })
		tree->add(i);

	cout << "iterative inorder traversal: ";
	tree->inorderTraverse(displayInt);
	cout << endl;

	delete tree;
}

void testDictionaryReplace()
{
	DictionaryInterface<int, std::string> *arrayDict = new ArrayDictionary<int, std::string>();

	std::pair<int, std::string> entries[]{ { 20, "Nathan" },{ 30, "Kazzy" },{ 746, "Science" } };
	for (auto entry : entries)
		arrayDict->add(entry.first, entry.second);

	cout << "dictionary contents:\t";
	arrayDict->traverse(displayEntry);
	cout << endl;

	cout << "replacing \"Nathan\" with \"Ross\"\n";
	arrayDict->replace(20, "Ross");

	cout << "replacing \"Science\" with \"Math\"\n";
	arrayDict->replace(746, "Math");

	cout << "dictionary contents:\t";
	arrayDict->traverse(displayEntry);
	cout << endl;

	delete arrayDict;
}