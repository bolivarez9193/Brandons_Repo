/****************************************************************************************
*  Program Name:		stackType.h)
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 20:				Header file for Lab 20
*						- deriving the array based stack from the array based list
*  Date:				11/07/2013
*  Description:			This file contains the prototype of the class arrayStackType
*****************************************************************************************/

#ifndef H_ArrayStackType
#define H_ArrayStackType

#include <iostream>
#include <iomanip>
#include <cassert>
#include "arrayBasedListType.h"

using namespace std; 


//derive arrayStackType from arrayListType
template <class Type> 
class arrayStackType: public arrayListType<Type>
{
	//overload insertion operator <<
	friend ostream& operator<<<Type>(ostream& os, const arrayStackType<Type>& x);  
public:
	const arrayStackType<Type> & operator=		// overloading assignment operator
				(const arrayStackType<Type>&); 
	Type & operator[] (int index);				// index operator overloading
	
	//two major stack operation
	Type pop();									//pop the top element
	void push(Type & item);						//push an item upto stack
	Type getTop(){return list[top];}
	arrayStackType():arrayListType<Type>()		// default constructor
	{
		top = -1;
	}
	arrayStackType(int n):arrayListType<Type>(n)	// another constructor
	{
		top = -1; 
	}
	arrayStackType(const arrayStackType<Type>&);	// copy constructor 
	
	~arrayStackType(){};							// the destructor

private: 
	int top; 
	void arrayStackType<Type>::copyStack(const arrayStackType<Type> & rhs); //copy stack method
};

//pop
template<class Type>
Type arrayStackType<Type>::pop()					//pop the top element
{
	assert(!isEmpty());								//make sure the stack is not empty
	
	if (!isEmpty())
	{
		Type tmp = list[top--]; 
		deleteItem(tmp); 
		return tmp; 
	}
	else
	{
		cout<<"No pop, the stack is empty." <<endl; 
	}
}

//push
template<class Type>
void arrayStackType<Type>::	push(Type & item)		//push an item upto stack
{
	assert(!isFull());								//make sure no full
	
	if(!isFull())
	{
		insertLast(item); 
		top++; 
	}
	else 
	{
		cout<<"No push, the stack is full."<<endl; 
	}
}


//overload insertion operator <<
template<class Type>
ostream&  operator<<<>(ostream& os, const arrayStackType<Type>& x)
{
	for (int i = 0; i < x.length(); i++)
	{
		os << x[i] << endl;
	}
	return os; 
}

// index operator overloading
template<class Type>
Type & arrayStackType<Type>::operator[] (int index)
{
	assert(0<= index && index < count);		//check the range of the index
	return list[index]; 
}

// overloading assignment operator
template<class Type>
const arrayStackType<Type> & 
arrayStackType<Type>::operator=	(const arrayStackType<Type>& rhs)
{
	if (this != & rhs)
	{
		copyStack(rhs);
	}
	return *this; 
}

//copy stack
template <class Type>
void arrayStackType<Type>::copyStack(const arrayStackType<Type> & rhs)
{
	count = rhs.count; 
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

//copy constructor
template<class Type>
arrayStackType<Type>::arrayStackType(const arrayStackType<Type>& rhs)	// copy constructor 
{
	top = rhs.top; 
	count = rhs.count; 
	maxSize = rhs.maxSize; 
	delete[] list; 
	if (rhs.isEmpty())
		list = NULL; 
	else
	{
		list = new Type[maxSize]; 
		for (int i = 0; i<count; i++)
			list[i] = otherList[i];
	}
}

#endif