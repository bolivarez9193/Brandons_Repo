#include<iostream>
#include "AVL Tree.h"
using namespace std;

int main()
{
	avlTree tree;
	/*
	tree.insert(2);
	tree.insert(50);
	tree.insert(23);
	tree.insert(7);
	tree.insert(18);
	tree.insert(42);
	tree.insert(-10);
	tree.insert(60);
	tree.display();
	*/
	for (int i = 0; i < 1000000; i++)
	{
		tree.insert(rand());
	}
	cout <<"Height of tree is: " << tree.height() << endl;
	return 0;
}