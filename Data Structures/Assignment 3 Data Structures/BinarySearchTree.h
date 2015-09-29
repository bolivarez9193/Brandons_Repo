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
//				search tree, and many of the code is derived from
//				the labs from your website. Also, some of this code is 
//				from CS2.
//
////////////////////////////////////////////////////////////////////////
#ifndef H_BST
#define H_BST

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

class binarySearchTree
{
private:
	class node
	{
	public:
		int data, height;
		node * left;
		node * right;

		node (int x)
		{
			data = x;
			left = NULL;
			right = NULL;
			height = 0;
		}
	};
	node * root;

	int larger(int x, int y)
	{
		return (x >= y)? x : y; 
	}


	void rotateLeft(node *& x)
	{
		node *x2 = x->left; 
		x->left = x2->right;
		x2->right = x; 
		x->height = larger(returnHeight(x->left), returnHeight(x->right)) + 1; 
		x2->height = larger(returnHeight(x2->left), x2->height) + 1; 
		x = x2; 
	}

	void rotateRight(node *& x)
	{
		node *x2 = x->right; 
		x->right = x2->left;
		x2->left = x; 
		x->height = larger(returnHeight(x->left), returnHeight(x->right)) + 1; 
		x2->height = larger(returnHeight(x2->right), x->height) + 1; 
		x = x2;
	}

	void doubleRotateLeft(node *& x)
	{
		rotateRight(x->left); 
		rotateLeft(x); 
	}

	void doubleRotateRight(node *& x)
	{
		rotateLeft(x->right); 
		rotateRight(x); 
	}

	int returnHeight(node * r)
	{
		if (r == NULL)
		{
			return 0;
		}

		int left = returnHeight(r->left);
		int right = returnHeight(r->right); 

		if (left > right)
			return 1 + left;
		else
			return 1 + right;
	}

	void insert(node * & r, int x)
	{
		if (r == NULL) 
		r = new node(x); 
	else if (x < r->data)				
	{
		insert(r->left, x); 
		if (returnHeight(r->left) - returnHeight(r->right) == 2)
		{
			if (x < r->left->data)
			{
				rotateLeft(r); 
			}
			else
			{
				doubleRotateLeft(r);
			}
		}
	}	
	else if (r->data < x)
	{
		insert(r->right, x); 
		if (returnHeight(r->right) - returnHeight(r->left) == 2)
		{
			if (x > r->right->data)
			{
				rotateRight(r); 
			}
			else
			{
				doubleRotateRight(r);
			}
		}
	}
	else
	{

	}
	
	r->height = larger(returnHeight(r->left), returnHeight(r->right)) + 1; 
	}

	void display(node * x)
	{
		if (x == NULL)
		{

		}
		else
		{
			if (x->right != NULL)
			{
				display(x->left);
			}
			cout << x->data << endl;
			if (x->left != NULL)
			{
				display(x->right);
			}
			
		}
		
	}

	node * extractMin(node * &r)
	{
		if (r -> left == NULL)
		{
			return r;
		}

		else
		{
			return extractMin(r->left);
		}
	}
	node * findNode( node * &x, int y)
	{
		if (x == NULL)
		{
			cout << "Error. Node not found." << endl;
		}
		else if (x->data == y)
		{
			return x;
		}
		else
		{
			if (x->data > y)
			{
				 findNode(x->left,y);
			}
			else
			{
				 findNode(x->right,y);
			}
		}
	}
	
	void deleteNode(node * &a, int b)
	{ 
		node * c; 
	
		if (a==NULL)
			return;		
	
		if (b < a->data)
			deleteNode(a->left, b);		
		else if (b > a->data)
			deleteNode(a->right, b);	
		else						
		{
			if (a->left == NULL || a->right == NULL)
			{
				c = a; 
				a = (a->left == NULL)? a->right: a->left; 
				delete c; 
			}
			else 
			{
				a->data = extractMin(a->right)->data; 
				deleteNode(a->right, a->data); 
			}
		}

		if (a != NULL)
			a->height = larger(returnHeight(a->left), returnHeight(a->right)) + 1; 

	
		if (a != NULL)
		{		
			if (returnHeight(a->left) - returnHeight(a->right) == 2)
			{
				if (returnHeight(a->left->left) >= returnHeight(a->left->right))
				{
					rotateLeft(a); 
				}
				else
				{
					doubleRotateLeft(a);
				}
			}
			else if (returnHeight(a->right) - returnHeight(a->left) == 2)
			{
				if (returnHeight(a->right->right) >= returnHeight(a->right->left))
				{
					rotateRight(a); 
				}
				else
				{
					doubleRotateRight(a);
				}
			}
			else;	//do nothing. the element is already in the tree
	
			a->height = larger(returnHeight(a->left), returnHeight(a->right)) + 1; 
		}
	}

	void postOrderTraversal(node * x)
	{
		if ( x != NULL)
		{
			postOrderTraversal(x->left);
			postOrderTraversal(x->right);
			cout << x->data << " with height: " << x->height << endl; 
		}
	}

	void preOrderTraversal(node * x)
	{
		if ( x != NULL)
		{
			cout << x->data << " with height: " << x->height << endl; 
			postOrderTraversal(x->left);
			postOrderTraversal(x->right);
		}
	}

	void inOrderTraversal(node * x)
	{
		if ( x != NULL)
		{
			postOrderTraversal(x->left);
			cout << x->data << " with height: " << x->height << endl; 
			postOrderTraversal(x->right);
		}
	}
public:
	binarySearchTree()
	{
		root = NULL;
	}

	void insert(int x)
	{
		insert(root, x);
	}

	void display()
	{
		display(root);
	}
	void deleteNode(int x)
	{
		
		deleteNode(root, x);
		
	}
	void displayNode(int x)
	{
		node * tmp = findNode(root,x);
		cout << tmp->data << endl;
	}
	void extract()
	{
		node * tmp = extractMin(root);
		cout << tmp->data;
	}

	void postOrderTraversal()
	{
		postOrderTraversal(root);
	}

	void preOrderTraversal()
	{
		preOrderTraversal(root);
	}

	void inOrderTraversal()
	{
		inOrderTraversal(root);
	}
	
};

#endif