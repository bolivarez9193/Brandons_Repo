/****************************************************************************************
*  Program Name:		lab2380_optional_5_head.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 2380, Spring 2009
*  Lab Optional 5:		Header file for Lab Optional 5
*  Date:				01/17/2009
*  Description: This file contains the prototype of the class template binarySearchTree
*****************************************************************************************/

#ifndef H_BST
#define H_BST

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std; 


template <class Type> 
class binarySearchTree;									//forward declaration

template<class Type>
class binarySearchTreeNode
{
public: 
	friend class binarySearchTree<Type>; 
	//constructor
	binarySearchTreeNode(const Type & info, binarySearchTreeNode<Type> *lp, binarySearchTreeNode<Type> *rp)
		:element(info), left(lp), right(rp){ }; 

private: 
	Type element;										//store info
	binarySearchTreeNode<Type> *left;					//left child node pointer
	binarySearchTreeNode<Type> *right;					//right child node pointer
}; 

template<class Type>
class binarySearchTree
{
public: 
	//default constructor
	explicit binarySearchTree(); 
	//copy constructor
	binarySearchTree(const binarySearchTree<Type> & rhs); 
	//destructor
	~binarySearchTree(); 

	binarySearchTreeNode<Type> * findMin() const;		//find minimum element in the tree
	binarySearchTreeNode<Type> * findMax() const;		//find maximum element in the tree
	bool find (const Type & x) const;	//find x in the tree or not
	bool isEmpty();						//check if the tree is empty or not

	void destroyTree();					//delete the tree
	void insert(const Type & x);		//insert x into the tree
	void remove(const Type & x);		//remove x from the tree

	//overload operator =
	const binarySearchTree & operator=(const binarySearchTree<Type> & rhs); 

	//tree traversal
	void inOrderTraversal();			//print tree in in-order
	void preOrderTraversal();			//print tree in pre-order
	void postOrderTraversal();			//print tree in post-order

	int treeHeight();					//get the height of the tree
	int treeNodeCount();				//get the node count (size) of the tree
	int treeLeaveCount();				//get the leave count of the tree

protected: 
	binarySearchTreeNode<Type> * root; 

	//auxillary methods
private: 
	//copy tree rhs to rt
	binarySearchTreeNode<Type> * copyTree(binarySearchTreeNode<Type> * & rt, binarySearchTreeNode<Type> *rhs); 
	//delete tree p
	void destroyTree(binarySearchTreeNode<Type> * & p); 
	//insert x into tree p
	void insert(binarySearchTreeNode<Type> * & p, const Type & x); 
	//remove x from tree p
	void remove(binarySearchTreeNode<Type> * & p, const Type & x); 
	//inorder traveral tree p
	void inOrderTraversal(binarySearchTreeNode<Type> * p); 
	//preorder traveral tree p
	void preOrderTraversal(binarySearchTreeNode<Type> * p); 
	//postorder traveral tree p
	void postOrderTraversal(binarySearchTreeNode<Type> * p); 
	//get height of tree p
	int treeHeight(binarySearchTreeNode<Type> * p);	
	//get node count of tree p
	int treeNodeCount(binarySearchTreeNode<Type> * p);
	//get leave count of tree p
	int treeLeaveCount(binarySearchTreeNode<Type> * p);		
	//find min of tree p
	binarySearchTreeNode<Type> * findMin(binarySearchTreeNode<Type> *p) const; 
	//find max of tree p
	binarySearchTreeNode<Type> * findMax(binarySearchTreeNode<Type> *p) const; 
	//find x in tree p
	bool find(const binarySearchTreeNode<Type> *p, const Type & x) const; 
	int larger (int x, int y); 
}; 

//default constructor
template <class Type>
binarySearchTree<Type>::binarySearchTree()
{
	root = NULL; 
}

//copy constructor
template<class Type>
binarySearchTree<Type>::binarySearchTree(const binarySearchTree<Type> & rhs)
{
	if (this != & rhs)
	{
		root = copyTree(root, rhs.root);//actual copy
	}
}
	
//destructor
template<class Type> 
binarySearchTree<Type>::~binarySearchTree()
{
	destroyTree();  
}

//find minimum element in the tree
template<class Type>
binarySearchTreeNode<Type> * binarySearchTree<Type>::findMin() const
{
	return findMin(root); 
}

//find maximum element in the tree
template <class Type>
binarySearchTreeNode<Type> * binarySearchTree<Type>::findMax() const
{
	return findMax(root); 
}
//find x in the tree or not
template<class Type>
bool binarySearchTree<Type>::find (const Type & x) const
{
	return find (root, x); 
}

//check whether the tree is empty or not
template <class Type>
bool binarySearchTree<Type>::isEmpty()
{
	return root == NULL; 
}

//delete the tree
template<class Type>
void binarySearchTree<Type>::destroyTree()
{
	destroyTree(root); 
}

//insert x into the tree
template<class Type>
void binarySearchTree<Type>::insert(const Type & x)
{
	insert(root, x); 
}

//remove x from the tree
template<class Type>
void binarySearchTree<Type>::remove(const Type & x)	
{
	remove(root, x); 
}

//overload operator =
template<class Type>
const binarySearchTree<Type> & binarySearchTree<Type>::operator=(const binarySearchTree<Type> & rhs)
{
	if (this != &rhs)
		copyTree(root, rhs); 

	return this; 
}

//print tree in in-order
template<class Type>
void binarySearchTree<Type>::inOrderTraversal()
{
	inOrderTraversal(root); 
}
//print tree in pre-order
template<class Type>
void binarySearchTree<Type>::preOrderTraversal()
{
	preOrderTraversal(root); 
}
//print tree in post-order
template<class Type>
void binarySearchTree<Type>::postOrderTraversal()
{
	postOrderTraversal(root); 
}

//get the height of the tree
template<class Type>
int binarySearchTree<Type>::treeHeight()
{
	return treeHeight(root); 
}

//get the node count (size) of the tree
template<class Type>
int binarySearchTree<Type>::treeNodeCount()
{
	return treeNodeCount(root); 
}

//get the leave count of the tree
template<class Type>
int binarySearchTree<Type>::treeLeaveCount()
{
	return treeLeaveCount(root);
}

/*****************************************************************
 auxillary functions
 *****************************************************************/

//copy tree rhs to rt
template<class Type>
binarySearchTreeNode<Type> * binarySearchTree<Type>::copyTree(binarySearchTreeNode<Type> * & rt, binarySearchTreeNode<Type> *rhs)
{
	if (rt != NULL)
		destroty(rt); 
	
	if (rhs == NULL)
	{
		rt = NULL;  
	}
	else 
	{
		rt = new binarySearchTreeNode(rhs->info, 
								copyTree(rt->left, rhs->left), 
								copyTree(rt->right, right->right)); 
	}
	
	return rt; 
}

//delete tree p
template<class Type>	
void binarySearchTree<Type>::destroyTree(binarySearchTreeNode<Type> * & p)
{
	binarySearchTreeNode<Type> * tmp; 
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
void binarySearchTree<Type>::insert(binarySearchTreeNode<Type> * & p, const Type & x)
{
	if (p == NULL) 
		p = new binarySearchTreeNode<Type>(x, NULL, NULL); 
	else if (p->element <= x)
		insert(p->right, x); 
	else 
		insert(p->left, x); 
}
	
//remove x from tree p
template<class Type>	
void binarySearchTree<Type>::remove(binarySearchTreeNode<Type> * & p, const Type & x)
{
	binarySearchTreeNode<Type> * tmp; 
	//if tree is empty do nothing
	if (p==NULL)
		return;		
	
	if (x < p->element)
		remove(p->left, x);		//remove x from left subtree
	else if (x < p->element)
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
}
	
//inorder traveral tree p
template<class Type>	
void binarySearchTree<Type>::inOrderTraversal(binarySearchTreeNode<Type> * p)
{
	if (p != NULL)
	{
		inOrderTraversal(p->left); 
		cout<< p->element <<endl; 
		inOrderTraversal(p->right); 
	}
}
	
//preorder traveral tree p
template<class Type>	
void binarySearchTree<Type>::preOrderTraversal(binarySearchTreeNode<Type> * p)
{
	if (p != NULL)
	{
		cout<< p->element <<endl; 
		preOrderTraversal(p->left); 
		preOrderTraversal(p->right); 
	}
}
//postorder traveral tree p
template<class Type>	
void binarySearchTree<Type>::postOrderTraversal(binarySearchTreeNode<Type> * p)
{
	if (p != NULL)
	{
		postOrderTraversal(p->left); 
		postOrderTraversal(p->right); 
		cout<< p->element <<endl; 
	}
}
	
//get height of tree p
template<class Type>	
int binarySearchTree<Type>::treeHeight(binarySearchTreeNode<Type> * p)
{
	if (p==NULL)
		return -1; 
	else 
		return 1 + larger(treeHeight(p->left), treeHeight(p->right)); 
}
	
//get node count of tree p
template<class Type>	
int binarySearchTree<Type>::treeNodeCount(binarySearchTreeNode<Type> * p)
{
	if (p==NULL)
		return 0; 
	else 
		return 1 + treeNodeCount(p->left) + treeNodeCount(p->right);   
}
	
//get leave count of tree p
template<class Type>	
int binarySearchTree<Type>::treeLeaveCount(binarySearchTreeNode<Type> * p)
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
binarySearchTreeNode<Type> * binarySearchTree<Type>::findMin(binarySearchTreeNode<Type> *p) const 
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
binarySearchTreeNode<Type> * binarySearchTree<Type>::findMax(binarySearchTreeNode<Type> *p) const
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
bool binarySearchTree<Type>::find(const binarySearchTreeNode<Type> *p, const Type & x) const
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
int binarySearchTree<Type>::larger(int x, int y)
{
	return (x >= y)? x : y; 
}

#endif

