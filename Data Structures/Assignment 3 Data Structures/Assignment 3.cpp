///////////////////////////////////////////////////////////////////////
// Name: Brandon Olivarez
//
// ID#: 20028785
//
// Class: CSCI 3333.02
//
// Professor: Zhixiang Chen
//
// Date: 4/22/2014
//
// Description: For this assignment, we will delete a node from a binary
//				search tree, and much of this code is derived
//				from the labs from your website. Also, some of this code
//				is from CS2.
//
////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
	binarySearchTree tree;
	tree.insert(2);
	tree.insert(5);
	tree.insert(-4);
	tree.insert(-5);
	tree.insert(-3);
	tree.insert(6);
	tree.deleteNode(5);
	tree.display();
	cout << endl << "Here's InOrder Traversal" << endl;
	tree.inOrderTraversal();
	cout << endl << "Here's PreOrder Traversal" << endl;
	tree.preOrderTraversal();
	cout << endl << "Here's PostOrder Traversal" << endl;
	tree.postOrderTraversal();
	return 0;
}