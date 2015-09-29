/****************************************************************************************
*  Program Name:		lab3333_13_head.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 13:				Header file for Lab 13
*  Date:				08/29/2013
*  Description: This file contains the prototype of the class template AVLTree
*****************************************************************************************/

#ifndef H_BST
#define H_BST

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std; 


template <class Type> 
class AVLTree;									//forward declaration

template<class Type>
class AVLTreeNode
{
public: 
	friend class AVLTree<Type>; 
	//constructor
	AVLTreeNode(const Type & info, AVLTreeNode<Type> *lp, AVLTreeNode<Type> *rp, int h=0)
		:element(info), left(lp), right(rp), height(h){ } 

private: 
	Type element;								//store info
	int height;									//store height of the tree rooted at the node
	AVLTreeNode<Type> *left;					//left child node pointer
	AVLTreeNode<Type> *right;					//right child node pointer
}; 

template<class Type>
class AVLTree
{
public: 
	//default constructor
	explicit AVLTree(); 
	//copy constructor
	AVLTree(const AVLTree<Type> & rhs); 
	//destructor
	~AVLTree(); 

	AVLTreeNode<Type> * findMin() const;		//find minimum element in the tree
	AVLTreeNode<Type> * findMax() const;		//find maximum element in the tree
	bool find (const Type & x) const;	//find x in the tree or not
	bool isEmpty();						//check if the tree is empty or not

	void destroyTree();					//delete the tree
	void insert(const Type & x);		//insert x into the tree
	void remove(const Type & x);		//remove x from the tree

	//overload operator =
	const AVLTree & operator=(const AVLTree<Type> & rhs); 

	//tree traversal
	void inOrderTraversal();			//print tree in in-order
	void preOrderTraversal();			//print tree in pre-order
	void postOrderTraversal();			//print tree in post-order

	int treeHeight();					//get the height of the tree
	int treeNodeCount();				//get the node count (size) of the tree
	int treeLeaveCount();				//get the leave count of the tree

protected: 
	AVLTreeNode<Type> * root; 

	//auxillary methods
private: 
	//copy tree rhs to rt
	AVLTreeNode<Type> * copyTree(AVLTreeNode<Type> * & rt, AVLTreeNode<Type> *rhs); 
	//delete tree p
	void destroyTree(AVLTreeNode<Type> * & p); 
	//insert x into tree p
	void insert(AVLTreeNode<Type> * & p, const Type & x); 
	//remove x from tree p
	void remove(AVLTreeNode<Type> * & p, const Type & x); 
	//inorder traveral tree p
	void inOrderTraversal(AVLTreeNode<Type> * p); 
	//preorder traveral tree p
	void preOrderTraversal(AVLTreeNode<Type> * p); 
	//postorder traveral tree p
	void postOrderTraversal(AVLTreeNode<Type> * p); 
	//get height of tree p
	int treeHeight(AVLTreeNode<Type> * p);	
	//get node count of tree p
	int treeNodeCount(AVLTreeNode<Type> * p);
	//get leave count of tree p
	int treeLeaveCount(AVLTreeNode<Type> * p);		
	//find min of tree p
	AVLTreeNode<Type> * findMin(AVLTreeNode<Type> *p) const; 
	//find max of tree p
	AVLTreeNode<Type> * findMax(AVLTreeNode<Type> *p) const; 
	//find x in tree p
	bool find(const AVLTreeNode<Type> *p, const Type & x) const; 
	int larger (int x, int y); 
	void rotateWithLeftChild(AVLTreeNode<Type> * & p); 
	void doubleWithLeftChild(AVLTreeNode<Type> * & p);
	void rotateWithRightChild(AVLTreeNode<Type> * & p); 
	void doubleWithRightChild(AVLTreeNode<Type> * & p);

}; 

//default constructor
template <class Type>
AVLTree<Type>::AVLTree()
{
	root = NULL; 
}

//copy constructor
template<class Type>
AVLTree<Type>::AVLTree(const AVLTree<Type> & rhs)
{
	if (this != & rhs)
	{
		root = copyTree(root, rhs.root);//actual copy
	}
}
	
//destructor
template<class Type> 
AVLTree<Type>::~AVLTree()
{
	destroyTree();  
}

//find minimum element in the tree
template<class Type>
AVLTreeNode<Type> * AVLTree<Type>::findMin() const
{
	return findMin(root); 
}

//find maximum element in the tree
template <class Type>
AVLTreeNode<Type> * AVLTree<Type>::findMax() const
{
	return findMax(root); 
}
//find x in the tree or not
template<class Type>
bool AVLTree<Type>::find (const Type & x) const
{
	return find (root, x); 
}

//check whether the tree is empty or not
template <class Type>
bool AVLTree<Type>::isEmpty()
{
	return root == NULL; 
}

//delete the tree
template<class Type>
void AVLTree<Type>::destroyTree()
{
	destroyTree(root); 
}

//insert x into the tree
template<class Type>
void AVLTree<Type>::insert(const Type & x)
{
	insert(root, x); 
}

//remove x from the tree
template<class Type>
void AVLTree<Type>::remove(const Type & x)	
{
	remove(root, x); 
}

//overload operator =
template<class Type>
const AVLTree<Type> & AVLTree<Type>::operator=(const AVLTree<Type> & rhs)
{
	if (this != &rhs)
		copyTree(root, rhs); 

	return this; 
}

//print tree in in-order
template<class Type>
void AVLTree<Type>::inOrderTraversal()
{
	inOrderTraversal(root); 
}
//print tree in pre-order
template<class Type>
void AVLTree<Type>::preOrderTraversal()
{
	preOrderTraversal(root); 
}
//print tree in post-order
template<class Type>
void AVLTree<Type>::postOrderTraversal()
{
	postOrderTraversal(root); 
}

//get the height of the tree
template<class Type>
int AVLTree<Type>::treeHeight()
{
	return treeHeight(root); 
}

//get the node count (size) of the tree
template<class Type>
int AVLTree<Type>::treeNodeCount()
{
	return treeNodeCount(root); 
}

//get the leave count of the tree
template<class Type>
int AVLTree<Type>::treeLeaveCount()
{
	return treeLeaveCount(root);
}

/*****************************************************************
 auxillary functions
 *****************************************************************/

//copy tree rhs to rt
template<class Type>
AVLTreeNode<Type> * AVLTree<Type>::copyTree(AVLTreeNode<Type> * & rt, AVLTreeNode<Type> *rhs)
{
	if (rt != NULL)
		destroty(rt); 
	
	if (rhs == NULL)
	{
		rt = NULL;  
	}
	else 
	{
		rt = new AVLTreeNode(rhs->info, 
								copyTree(rt->left, rhs->left), 
								copyTree(rt->right, rhs->right), treeHeight(rhs)); 
	}
	
	return rt; 
}

//delete tree p
template<class Type>	
void AVLTree<Type>::destroyTree(AVLTreeNode<Type> * & p)
{
	AVLTreeNode<Type> * tmp; 
	tmp = p; 
	if (p!=NULL)
	{
		destroyTree(p->left); 
		destroyTree(p->right); 
		delete p; 
	}
}
	
//insert x into tree p
template<class Type>	
void AVLTree<Type>::insert(AVLTreeNode<Type> * & p, const Type & x)
{
	if (p == NULL) 
		p = new AVLTreeNode<Type>(x, NULL, NULL); 
	else if (x < p->element)				//insert to the left subtree
	{
		insert(p->left, x); 
		if (treeHeight(p->left) - treeHeight(p->right) == 2)
		{
			if (x < p->left->element)
			{
				cout<<" rotate with left child at " << p->element <<endl;
				rotateWithLeftChild(p); 
			}
			else
			{
				cout<<" double rotate with left child at " << p->element <<endl;
				doubleWithLeftChild(p);
			}
		}
	}	
	else if (p->element < x)
	{
		insert(p->right, x); 
		if (treeHeight(p->right) - treeHeight(p->left) == 2)
		{
			if (x > p->right->element)
			{
				cout<<" rotate with right child at " << p->element <<endl;
				rotateWithRightChild(p); 
			}
			else
			{
				cout<<" double rotate with right child at " << p->element <<endl;
				doubleWithRightChild(p);
			}
		}
	}
	else;	//do nothing. the element is already in the tree
	
	p->height = larger(treeHeight(p->left), treeHeight(p->right)) + 1; 
}

template<class Type>	
void AVLTree<Type>::rotateWithLeftChild(AVLTreeNode<Type> * & k2)
{
	AVLTreeNode<Type> *k1 = k2->left; 
	k2->left = k1->right;
	k1->right = k2; 
	k2->height = larger(treeHeight(k2->left), treeHeight(k2->right)) + 1; 
	k1->height = larger(treeHeight(k1->left), k2->height) + 1; 
	k2 = k1; 
}

template<class Type>	
void AVLTree<Type>:: doubleWithLeftChild(AVLTreeNode<Type> * & k3)
{
	rotateWithRightChild(k3->left); 
	rotateWithLeftChild(k3); 
}

template<class Type>	
void AVLTree<Type>::rotateWithRightChild(AVLTreeNode<Type> * & k2)
{
	AVLTreeNode<Type> *k1 = k2->right; 
	k2->right = k1->left;
	k1->left = k2; 
	k2->height = larger(treeHeight(k2->left), treeHeight(k2->right)) + 1; 
	k1->height = larger(treeHeight(k1->right), k2->height) + 1; 
	k2 = k1; 
}

template<class Type>	
void AVLTree<Type>::doubleWithRightChild(AVLTreeNode<Type> * & k3)
{
	rotateWithLeftChild(k3->right); 
	rotateWithRightChild(k3); 
}

//remove x from tree p
template<class Type>	
void AVLTree<Type>::remove(AVLTreeNode<Type> * & p, const Type & x)
{
	int lh, rh; 
	AVLTreeNode<Type> * tmp; 
	//if tree is empty do nothing
	if (p==NULL)
		return;		
	
	if (x < p->element)
		remove(p->left, x);		//remove x from left subtree
	else if (x > p->element)
		remove (p->right, x);	//romve x from right subtree
	else						//remove the curent node containing x
	{
		//p have no children or only one child
		if (p->left == NULL || p->right == NULL)
		{
			tmp = p; 
			p = (p->left == NULL)? p->right: p->left; 
			delete tmp; 
		}
		else //p has two children
		{
			p->element = findMin(p->right)->element; 
			remove(p->right, p->element); 
		}
	}

	if (p != NULL)
		p->height = larger(treeHeight(p->left), treeHeight(p->right)) + 1; 

	//need to decide whether to rotate to balance the tree
	if (p != NULL)
	{		
		if (treeHeight(p->left) - treeHeight(p->right) == 2)
		{
			if (treeHeight(p->left->left) >= treeHeight(p->left->right))
			{
				cout<<" rotate with left child at " << p->element <<endl;
				rotateWithLeftChild(p); 
			}
			else
			{
				cout<<" double rotate with left child at " << p->element <<endl;
				doubleWithLeftChild(p);
			}
		}
		else if (treeHeight(p->right) - treeHeight(p->left) == 2)
		{
			if (treeHeight(p->right->right) >= treeHeight(p->right->left))
			{
				cout<<" rotate with right child at " << p->element <<endl;
				rotateWithRightChild(p); 
			}
			else
			{
				cout<<" double rotate with right child at " << p->element <<endl;
				doubleWithRightChild(p);
			}
		}
		else;	//do nothing. the element is already in the tree
	
		p->height = larger(treeHeight(p->left), treeHeight(p->right)) + 1; 
	}
}
	
//inorder traveral tree p
template<class Type>	
void AVLTree<Type>::inOrderTraversal(AVLTreeNode<Type> * p)
{
	if (p != NULL)
	{
		inOrderTraversal(p->left); 
		cout<< p->element <<" and height = " << p->height<<endl; 
		inOrderTraversal(p->right); 
	}
}
	
//preorder traveral tree p
template<class Type>	
void AVLTree<Type>::preOrderTraversal(AVLTreeNode<Type> * p)
{
	if (p != NULL)
	{
		cout<< p->element  <<" and height = " << p->height <<endl; 
		preOrderTraversal(p->left); 
		preOrderTraversal(p->right); 
	}
}
//postorder traveral tree p
template<class Type>	
void AVLTree<Type>::postOrderTraversal(AVLTreeNode<Type> * p)
{
	if (p != NULL)
	{
		postOrderTraversal(p->left); 
		postOrderTraversal(p->right); 
		cout<< p->element  <<" and height = " << p->height<<endl; 
	}
}
	
//get height of tree p
template<class Type>	
int AVLTree<Type>::treeHeight(AVLTreeNode<Type> * p)
{
	return p==NULL? -1: p->height; 
}
	
//get node count of tree p
template<class Type>	
int AVLTree<Type>::treeNodeCount(AVLTreeNode<Type> * p)
{
	if (p==NULL)
		return 0; 
	else 
		return 1 + treeNodeCount(p->left) + treeNodeCount(p->right);   
}
	
//get leave count of tree p
template<class Type>	
int AVLTree<Type>::treeLeaveCount(AVLTreeNode<Type> * p)
{
	if (p == NULL)
		return 0; 
	else if (p->left == NULL && p->right == NULL)
		return 1; 
	else if (p->left == NULL )
		return treeLeaveCount(p->right); 
	else if (p->right == NULL)
		return treeLeaveCount(p->left); 
	else 
		return treeLeaveCount(p->left) + treeLeaveCount(p->right); 
}
	
//find min of tree p
template<class Type>	
AVLTreeNode<Type> * AVLTree<Type>::findMin(AVLTreeNode<Type> *p) const 
{
	if (p == NULL)
		return NULL; 
	else if (p->left == NULL)
		return p; 
	else 
		return findMin(p->left); 
}
	
//find max of tree p
template<class Type>	
AVLTreeNode<Type> * AVLTree<Type>::findMax(AVLTreeNode<Type> *p) const
{
	if (p == NULL)
		return NULL; 
	else if (p->right == NULL)
		return p; 
	else 
		return findMin(p->right); 

}
	
//find x in tree p
template<class Type>	
bool AVLTree<Type>::find(const AVLTreeNode<Type> *p, const Type & x) const
{
	if (p == NULL)
		return false;
	else if (p->element == x)
		return true; 
	else if (x < p->element)
		return find(p->left, x); 
	else 
		return find (p->right, x); 
}

template<class Type>
int AVLTree<Type>::larger(int x, int y)
{
	return (x >= y)? x : y; 
}

#endif

