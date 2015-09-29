/****************************************************************************************
*  Program Name:		arrayListType.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 2380, Spring 2009
*  Lab 14:				Header file for Lab 11- defining the array based list
*  Date:				01/15/2009
*  Description: This file contains the prototype of the class arrayListType
*****************************************************************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std; 


#ifndef H_ArrayListType
#define H_ArrayListType

template <class Type> 
class arrayListType
{
public:
	const arrayListType<Type> & operator=	// overloading assignment operator
				(const arrayListType<Type>&); 
	Type & operator[] (int index);			// index operator overloading
	void initializeList();					// initialize the list to an empty list
	bool isEmpty();							// chech whether list is empty
	bool isFull();							// chech whether list is full
	int  length();							// read the number of nodes in list
	void destroyList();						// to delete all nodes from the list
	Type front();							// return the first element in the list
	Type back();							// return the last element in the list
	bool search(const Type & searchItem);	// to determine the searchItem is in the list
											// return true if yes or no otherwise
	void insertFirst(const Type & newItem);	// insert the newItem to the beginning of the list
	void insertLast(const Type & newItem);	// insert the newItem to the end of the list
	bool deleteItem(const Type & deleteItem);	// delete the node containing the input item from the list
	void print();							// print the list  
	arrayListType();						// default constructor
	arrayListType(int n);					// another constructor
	arrayListType(const arrayListType<Type>&);	// copy constructor 
	~arrayListType();						// the destructor

protected: 
	int count;								// store the number of nodes in the list
	int maxSize;							// the max size of the list
	Type *list;								// pointer for dynamic array

private: 
	void copyList(const arrayListType<Type> & otherList); 
											//copy other list to the invoking list
};


// Overload  array index operator []
template <class Type>
Type& arrayListType<Type>::operator[](int index)
{
	assert(0<= index && index < count);		//check the range of the index
	return list[index];
}

// print the list
template <class Type>
void arrayListType<Type>::print( )
{
	for (int i = 0; i < count; i++)
	{
		cout << list[i] <<endl; 
	}
}

// initialize the list to an empty list
template <class Type> 
void arrayListType<Type> :: initializeList()
{
	count = 0; 								//destroy the list to an empty one
	maxSize = 0; 
	list = NULL; 
}

// chech whether list is empty
template <class Type> 
bool arrayListType<Type>::isEmpty()
{
	return count == 0; 
}

// chech whether list is full
template <class Type> 
bool arrayListType<Type>::isFull()
{
	return count == maxSize; 
}

// read the number of nodes in list
template <class Type>
int  arrayListType<Type>::length()
{
	return count; 
}
	
// to delete all nodes from the list
template <class Type>
void arrayListType<Type>::destroyList()
{
	count = 0;
	maxSize = 0; 
	delete[] list; 
	list = NULL; 
}


// return the first element in the list
template <class Type> 
Type arrayListType<Type>::front()
{
	assert(!isEmpty());			//to make sure the list is not empty
	return list[0]; 
}

// return the last element in the list
template <class Type> 
Type arrayListType<Type>::back()
{
	assert(!isEmpty());			//to make sure the list is not empty
	return list[count-1]; 
}

// to determine the searchItem is in the list
// return true if yes or no otherwise
template <class Type> 
bool arrayListType<Type>::search(const Type & searchItem)
{
	assert(!isEmpty());			// make sure the list is not empty
	
	bool found = false;			//flag for founding status
	
	int i = 0;					//point to first
	while (!found && i < count)
	{
		if (list[i] == searchItem)
			found = true;		//find the searchItem
		else					//otherwise move to the next node
			i++; 
	}
	return found; 
}

// insert the newItem to the beginning of the list
template <class Type>
void arrayListType<Type>::insertFirst(const Type & newItem)
{
	assert(!isFull());				//make sure the list is not full
    
	for (int i = count; i>=0; i--)	//shift all elements one position to the end
	{
		list[i+1] = list[i]; 
	}
	list[0] = newItem;				//add the new item into the first 
	count++;						//increase the index
}


// insert the newItem to the end of the list
template <class Type> 
void arrayListType<Type>::insertLast(const Type & newItem)
{
	assert(!isFull());				//make sure the list is not full
		
	list[count] = newItem; 
	count++; 
}



// delete the node containing the input item from the list	
template <class Type>
bool arrayListType<Type>::deleteItem(const Type & deleteItem)
{
	int i; 
	bool found = false; 
	for (i=0; i<count; i++)
	{
		if (list[i] == deleteItem)
		{
			found = true; 
			break; 
		}
	}
	if (!found)						//if not found then stop
		return false; 
	else							//found then delete
	{
		if (i==count)
			count--; 
		else						//shift elements 
		{
			for (int j = i+1; j<count; j++)
				list[j-1]=list[j]; 
			count--; 
		}
		return true; 
	}
}

// default constructor	
template <class Type>
arrayListType<Type>::arrayListType()
{
	count = 0; 
	maxSize = 100;
	list = new Type[100]; 
}

// another constructor	
template <class Type>
arrayListType<Type>::arrayListType(int n)
{
	assert(n>=0);					//make sure n >= 0
	count = 0; 
	maxSize = n;
	list = new Type[n]; 
}

// copy constructor 
template <class Type>
arrayListType<Type>::arrayListType(const arrayListType<Type>& otherList)
{
	copyList(otherList); 
}

//destructor
template <class Type>
arrayListType<Type>::~arrayListType()
{
	destroyList(); 
}

//copy list
template <class Type>
void arrayListType<Type>::copyList(const arrayListType<Type> & otherList)
{
	count = otherList.count; 
	maxSize = otherList.maxSize; 
	delete[] list; 
	if (otherList.isEmpty())
		list = NULL; 
	else
	{
		list = new Type[maxSize]; 
		for (int i = 0; i<count; i++)
			list[i] = otherList[i];
	}
}

// overloading assignment operator
template <class Type>
const arrayListType<Type>& 
		arrayListType<Type>::operator=(const arrayListType<Type>& otherList)
{
	if (this != & otherList)
	{
		copyList(otherList);
	}
	return *this; 
}



#endif