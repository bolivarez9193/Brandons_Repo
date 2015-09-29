/****************************************************************************************
*  Program Name:		arrayListType.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 20:				Header file for Lab 20- defining the array based list
*  Date:				11/7/2013
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
	  arrayListType<Type> & operator=	// overloading assignment operator
				(  arrayListType<Type>&); 
	Type & operator[] (int index);			// index operator overloading
	void initializeList(int);				// initialize the list to an empty list
	bool isEmpty();							// chech whether list is empty
	bool isFull();							// chech whether list is full
	int  length();							// read the number of nodes in list
	int  getMaxSize(){return maxSize;}
	void destroyList();						// to delete all nodes from the list
	Type front();							// return the first element in the list
	Type back();							// return the last element in the list
	void setCount(){count++;}
	bool search(  Type & searchItem);	// to determine the searchItem is in the list
											// return true if yes or no otherwise
	void insertFirst(  Type & newItem);	// insert the newItem to the beginning of the list
	void insertLast(  Type & newItem);	// insert the newItem to the end of the list
	void insert(int i, const Type & newItem); 
	bool deleteItem(  Type & deleteItem);	// delete the node containing the input item from the list
	void print();							// print the list  
	arrayListType();						// default  ructor
	arrayListType(int n);					// another  ructor
	arrayListType(  arrayListType<Type>&);	// copy  ructor 
	~arrayListType();						// the destructor

protected: 
	int count;								// store the number of nodes in the list
	int maxSize;							// the max size of the list
	Type *list;								// pointer for dynamic array

private: 
	void copyList(  arrayListType<Type> & otherList); 
											//copy other list to the invoking list
};


// Overload  array index operator []
template <class Type>
Type& arrayListType<Type>::operator[](int index)
{
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
void arrayListType<Type> :: initializeList(int s)
{
	count = 0; 								//destroy the list to an empty one
	maxSize = s; 
	if (list != NULL)
	{
		delete[] list;
	}
	list = new Type[s]; 
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
bool arrayListType<Type>::search(  Type & searchItem)
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


//insert a new element at position i
template <class Type>
void arrayListType<Type>::insert(int i, const  Type &x)
{
	if (0 <= i && i < maxSize) 
	{
		list[i] = x;
		count++; 
	}
}

// insert the newItem to the beginning of the list
template <class Type>
void arrayListType<Type>::insertFirst(  Type & newItem)
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
void arrayListType<Type>::insertLast(  Type & newItem)
{
	assert(!isFull());				//make sure the list is not full
		
	list[count] = newItem; 
	count++; 
}



// delete the node containing the input item from the list	
template <class Type>
bool arrayListType<Type>::deleteItem(  Type & deleteItem)
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

// default  ructor	
template <class Type>
arrayListType<Type>::arrayListType()
{
	count = 0; 
	maxSize = 100;
	list = new Type[100]; 
}

// another  ructor	
template <class Type>
arrayListType<Type>::arrayListType(int n)
{
	assert(n>=0);					//make sure n >= 0
	count = 0; 
	maxSize = n;
	list = new Type[n]; 
}

// copy  ructor 
template <class Type>
arrayListType<Type>::arrayListType(  arrayListType<Type>& otherList)
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
void arrayListType<Type>::copyList(  arrayListType<Type> & otherList)
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
  arrayListType<Type>& 
		arrayListType<Type>::operator=(  arrayListType<Type>& otherList)
{
	if (this != & otherList)
	{
		copyList(otherList);
	}
	return *this; 
}



#endif