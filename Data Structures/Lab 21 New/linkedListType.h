/****************************************************************************************
*  Program Name:		linkedListType.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 13
*  Lab 20:				Header file for Lab 12
*  Date:				11/07/2013
*  Description: This file contains the prototype of the class linkedListType
*  and the linked-list's node struct definition.
*****************************************************************************************/

#ifndef H_linkedListType
#define H_linkedListType

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std; 

template <class Type> 
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};

template <class Type> 
class linkedListType
{
	friend ostream & operator<<<>(ostream &,  linkedListType<Type> & ); 
public:
	  linkedListType<Type> & operator=	// overloading assignment operator
					(  linkedListType<Type>&); 
	void initializeList();					// initialize the list to an empty list
	bool isEmpty();							// chech whether list is empty
	int  length();							// read the number of nodes in list
	void destroyList();						// to delete all nodes from the list
	Type front();							// return the first element in the list
	Type back();							// return the last element in the list
	bool search(  Type & searchItem);	// to determine the searchItem is in the list
											// return true if yes or no otherwise
	void insertFirst(  Type & newItem);	// insert the newItem to the beginning of the list
	void insertLast(  Type & newItem);	// insert the newItem to the end of the list
	void deleteNode(  Type & deleteItem);		// delete the node containing the input item from the list
	void print();							// print the list  
	linkedListType();						// default  ructor
	linkedListType(  linkedListType<Type>&);	// copy  ructor 
	~linkedListType();						// the destructor
	bool getNext( Type & ); 

protected: 
	int count;								// store the number of nodes in the list
	nodeType<Type> *first;					// the pointer to the first node
	nodeType<Type> *last;					// the pointer to the last node
	nodeType<Type> *next; 

private: 
	void copyList(  linkedListType<Type> & otherList); 
											//copy other list to the invoking list
};

template <class Type>
bool linkedListType<Type>::getNext(Type & out)
{
	if (next==NULL)
	{
		next = first; 
		return false; 
	}
	else
	{
		out = next->info; 
		next = next->link; 
		return true; 
	}
}

// print the list
template<class Type>
ostream &  operator<<<>(ostream& os,  linkedListType<Type> & rhs)
{
		nodeType<Type> *current;			//point to current node
		current = rhs.first; 

		while(current != NULL)
		{
			os<<current->info; 			
			current = current->link; 
		}
		return os; 
}


// print the list
template <class Type>
void linkedListType<Type>::print( )
{
		nodeType<Type> *current;			//point to current node
		current = first; 

		while(current != NULL)
		{
			cout<<current->info; 			
			current = current->link; 
		}

}

// initialize the list to an empty list
template <class Type> 
void linkedListType<Type> :: initializeList()
{
	destroyList();							//destroy the list to an empty one
}

// chech whether list is empty
template <class Type> 
bool linkedListType<Type>::isEmpty()
{
	return count == 0; 
}

// read the number of nodes in list
template <class Type>
int  linkedListType<Type>::length()
{
	return count; 
}
	
// to delete all nodes from the list
template <class Type>
void linkedListType<Type>::destroyList()
{
	nodeType<Type> *tmp;			//local node ptr to help to delete a node
	
	while (first!=NULL)				//loop until no more nodes are in the list
	{
		tmp = first;				//get the current node
		first = first->link;		//move to the next node
		delete tmp;					//delete the current node
	}

	next = first = last = NULL; 
	count = 0; 
}

// return the first element in the list
template <class Type> 
Type linkedListType<Type>::front()
{
	assert(first!=NULL);			//to make sure the list is not empty
	return first->info; 
}

// return the last element in the list
template <class Type> 
Type linkedListType<Type>::back()
{
	assert(last!=NULL);				//to make sure the list is not empty
	return last->info; 
}

// to determine the searchItem is in the list
// return true if yes or no otherwise
template <class Type> 
bool linkedListType<Type>::search(  Type & searchItem)
{
	nodeType<Type> *current;		//ptr to current node 
	bool found = false;				//flag for founding status
	
	current = first;				//point to first
	while (!found && current!=NULL)		
	{
		if (current->info == searchItem)
			found = true;			//find the searchItem
		else						//otherwise move to the next node
			current = current->link; 
	}

	return found; 
}

// insert the newItem to the beginning of the list
template <class Type>
void linkedListType<Type>::insertFirst(  Type & newItem)
{
		nodeType<Type> *newNode;		//for creating a new new
		newNode = new nodeType<Type>;	//create a new node

		assert(newNode != NULL);		//make sure the new node in indeed created
		
		newNode->info = newItem;		//load info to new node	 
		newNode->link = first;			//add new node the front of the list
		first = newNode;				//reset first 
		count++;						//increase the count 
		if (last == NULL)				//reset last if it is empty
			last = newNode;
		next = first; 
}

// insert the newItem to the end of the list
template <class Type> 
void linkedListType<Type>::insertLast(  Type & newItem)
{
		nodeType<Type> *newNode;		//for creating a new new
		newNode = new nodeType<Type>;	//create a new node

		assert(newNode != NULL);		//make sure the new node in indeed created
		
		newNode->info = newItem;		//load info to new node	 
		newNode->link = NULL;			//make sure the new node is the last one
		count++;						//increase the count 
		if (first == NULL)				//when the list is empty
		{
			first = last = newNode; 
		}
		else 
		{
			last->link = newNode; 
			last = newNode;
		}
		next = first; 
}

// delete the node containing the input item from the list	
template <class Type>
void linkedListType<Type>::deleteNode(  Type & deleteItem)
{
	nodeType<Type>	*current,			//point to current node
					*previous;			//point to next node
	bool found;							//flag for finding the node containing deleteItem
	
	//case 1: the list is empty
	if(isEmpty())
		return; 
	//case 2: the first is to be deleted
	else if (first->info == deleteItem)
	{
		current = first->link;			//get the second node if there is one
		delete first;					//delete the first node
		if (current == NULL)			//there is only one node
		{
			first = last = NULL; 
		}	
		else
		{
			first = current; 
		}
		count--; 
		return; 
	}
	//case 3: find the node after the first one
	else 
	{
		previous = first; 
		current = first->link;  
		found = false; 
		while (!found && current!=NULL)
		{
			if (current->info == deleteItem)
			{
				found = true; 
			}
			else
			{
				previous = current; 
				current = current->link; 
			}
		}
		if (found)
		{
			previous->link = current->link;	//skip the current node
			count--; 
			if (last == current)			//delete the last node
				last = previous; 
			delete current; 
		}	
	}
	next = first; 
}

// default  ructor	
template <class Type>
linkedListType<Type>::linkedListType()
{
	count = 0; 
	next = first = last = NULL;
}

// copy  ructor 
template <class Type>
linkedListType<Type>::linkedListType(  linkedListType<Type>& otherList)
{
	next = first = NULL; 
	copyList(otherList); 
}

//destructor
template <class Type>
linkedListType<Type>::~linkedListType()
{
	destroyList(); 
}

//copy list
template <class Type>
void linkedListType<Type>::copyList(  linkedListType<Type> & otherList)
{
	nodeType<Type>	*newNode,	//for creating a new node 
					*current;	//point to current node
	
	
	if (!isEmpty())				//if list is not empty then destroy it
		destroyList(); 
	
	if (otherList.isEmpty())	//otherList is empty
	{
		next = first = last = NULL; 
		count = 0; 
		return; 
	}
	count = otherList.count;	//copy the count
	//otherList is not empty. first take care of the first node	
	first = new nodeType<Type>;
	first->info = otherList.first->info; 
	first->link = NULL; 
	last = first; 
	next = first; 
	//now take care of additional nodes if any
	current = otherList.first->link;  
	while (current != NULL)
	{
		newNode = new nodeType<Type>; 
		newNode -> info = current->info; 
		newNode -> link = NULL; 
		last->link = newNode; 
		last = newNode; 

		current = current->link; 
	}
}

// overloading assignment operator
template <class Type>
  linkedListType<Type>& 
		linkedListType<Type>::operator=(  linkedListType<Type>& otherList)
{
	if (this != & otherList)
	{
		copyList(otherList);
	}
	return *this; 
}

#endif