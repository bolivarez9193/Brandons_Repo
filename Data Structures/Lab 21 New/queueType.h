/**********************************************************************************************
*  Program Name:		queueType.h)
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 13
*  Lab 21:				Header file for Lab 21-derving array-based queue from array-based list
*  Date:				11/07/2013
*  Description: This file contains the prototype of the class arrayQueueType
*  Here, the queue is the FIFO (First In First Out) queue. 
************************************************************************************************/

#ifndef H_ArrayQueueType
#define H_ArrayQueueType

#include <iostream>
#include <iomanip>
#include <cassert>
#include "arrayBasedListType.h"

using namespace std; 


//derive arrayStackType from arrayListType
template <class Type> 
class arrayQueueType: public arrayListType<Type>
{
	//overload insertion operator <<
	friend ostream& operator<<<Type>(ostream& os,   arrayQueueType<Type>& x);  
public:
	  arrayQueueType<Type> & operator=		// overloading assignment operator
				(  arrayQueueType<Type>&); 
	Type & operator[] (int index);				// index operator overloading
	
	//two major stack operation
	Type deQueue();								// enter an element into the queue
	void enQueue(Type & item);					// remove an element from the queue

	arrayQueueType():arrayListType<Type>()		// default  ructor
	{
		front = 0;								// front is always at position 0	 
		rear = -1;								// rear varies from -1 (empty queue) to count - 1
	}
	arrayQueueType(int n):arrayListType<Type>(n)// another  ructor
	{
		front = 0;								// front is always at position 0	 
		rear = -1;								// rear varies from -1 (empty queue) to count - 1
	}
	arrayQueueType(  arrayQueueType<Type>&);// copy  ructor 
	
	~arrayQueueType(){};						// the destructor

private: 
	int front; 
	int rear; 
	void arrayQueueType<Type>::copyQueue(  arrayQueueType<Type> & rhs); //copy stack method
};

//deQueue
template<class Type>
Type arrayQueueType<Type>::deQueue()				//remove the front element
{
	assert(!isEmpty());								//make sure the stack is not empty
	
	if (!isEmpty())
	{
		Type tmp = list[0]; 
		deleteItem(tmp); 
		return tmp; 
	}
	else
	{
		cout<<"No dequeue, the queue is empty." <<endl; 
	}
}

//push
template<class Type>
void arrayQueueType<Type>::	enQueue(Type & item)//push an item upto stack
{
	assert(!isFull());							//make sure no full
	
	if(!isFull())
	{
		insertLast(item);
		rear++; 
	}
	else 
	{
		cout<<"No enQueue, the queue is full."<<endl; 
	}
}


//overload insertion operator <<
template<class Type>
ostream&  operator<<<>(ostream& os,   arrayQueueType<Type>& x)
{
	int flag = 1; 
	for (int i = 0; i < x.length(); i++)
	{
		os << x[i] << "  "; 
		if (flag %5 == 0)
			os << endl;
		flag++; 
	}
	return os; 
}

// index operator overloading
template<class Type>
Type & arrayQueueType<Type>::operator[] (int index)
{
	assert(0<= index && index < count);				//check the range of the index
	return list[index]; 
}

// overloading assignment operator
template<class Type>
  arrayQueueType<Type> & 
arrayQueueType<Type>::operator=	(  arrayQueueType<Type>& rhs)
{
	if (this != & rhs)
	{
		copyQueue(rhs);
	}
	return *this; 
}

//copy stack
template <class Type>
void arrayQueueType<Type>::copyQueue(  arrayQueueType<Type> & rhs)
{
	count = rhs.count; 
	front = rhs.front; 
	rear = rhs.rear; 
	maxSize = rhs.maxSize; 
	delete[] list; 
	if (rhs.isEmpty())
		list = NULL; 
	else
	{
		list = new Type[maxSize]; 
		for (int i = 0; i<count; i++)
			list[i] = rhs.list[i];
	}
}

//copy  ructor
template<class Type>
arrayQueueType<Type>::arrayQueueType(  arrayQueueType<Type>& rhs)	// copy  ructor 
{
	front = rhs.front; 
	rear = rhs.rear; 
	count = rhs.count; 
	maxSize = rhs.maxSize; 
	delete[] list; 
	if (rhs.isEmpty())
		list = NULL; 
	else
	{
		list = new Type[maxSize]; 
		for (int i = 0; i<count; i++)
			list[i] = rhs[i];
	}
}

#endif