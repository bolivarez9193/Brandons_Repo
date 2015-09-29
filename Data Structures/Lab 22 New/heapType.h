/****************************************************************************************
*  Program Name:		heapType.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 22:				Header file for Lab 22
*  Date:				11/07/2013
*  Description: This file contains the prototype of the class template binary heap.
*****************************************************************************************/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "arrayBasedListType.h"
using namespace std; 


#ifndef BH
#define BH

template <class Type>
class binaryHeapType
{
public:
    bool isEmpty ( )  ;
    bool isFull ( );
	int getSize() {return size;}
      Type & findMin ( )  ;
	  binaryHeapType<Type> & operator=(binaryHeapType<Type> &);
    void add(int, Type &);
	void insert (const  Type & x);
    void deleteMin ( );                     // removes the minimum.
    void deleteMin (Type & minItem);		// removes the minimum and stores the removed value 
											// in an object passed by reference. 
    void makeEmpty ( );
	void buildHeap ( );
    void percolateDown ( int pos);			// Internal method to percolate down in the heap.
	void percolateUp( int pos);				// pos is the index of the percolating up process
	void print(); 
	void setSize(int); 

	binaryHeapType(int cap = 100);
	binaryHeapType (binaryHeapType<Type> & rhs); 

private:
    int size;								// Number of elements in heap
    arrayListType<Type> heapList;				// The heap array

};

template <class Type>
void binaryHeapType<Type>::setSize(int N)
{
	size = 0; 
	heapList.initializeList(N); 
}


template <class Type>
void binaryHeapType<Type>::print()
{
	for (int i=1; i<=size; i++)
		cout<<"heapList["<<i<<"] = " <<heapList[i]<<endl; 
}

template <class Type>
void binaryHeapType<Type>::add(int i, Type & x)
{
	size++; 
	heapList.insert(i,x); 
}


template <class Type>
bool binaryHeapType<Type>::isEmpty ( )  
{
	return size == 0; 
}

template <class Type>
bool binaryHeapType<Type>::isFull ( ) 
{
	return size == heapList.getMaxSize(); 
}

//pre-condition is that the heap is not empty
template <class Type>   
  Type & binaryHeapType<Type>::findMin ( )  
{
	return heapList[1]; 
}

template <class Type>
  binaryHeapType<Type> & binaryHeapType<Type>::operator=(	binaryHeapType<Type> & rhs)
{
	if (this != & rhs)
	{
		size = rhs.size; 
		heapList = rhs.heapList; 
	}
	return *this; 
}


template <class Type>     
void binaryHeapType<Type>::insert (  const Type & x)
{
	if (!isFull())
	{	
		size++; 
		heapList.insert(size, x); 
		percolateUp(size); 
	}
}

template <class Type>     
void binaryHeapType<Type>::deleteMin ( )                     
{
	percolateDown(1); 
}

// removes the minimum and stores the removed value 
// in an object passed by reference. 
template <class Type>     
void binaryHeapType<Type>:: deleteMin ( Type & minItem) 
{														
	minItem = heapList[1]; 
	heapList[1] = heapList[size]; 
	size--; 
	percolateDown(1); 
}

template <class Type>     
void binaryHeapType<Type>::  makeEmpty ( )
{
	size = 0; 
	heapList.destroyheapList(); 
}

template <class Type>
binaryHeapType<Type>:: binaryHeapType(int cap)
{
	size = 0; 
	heapList.initializeList(cap); 
}
template <class Type>     
binaryHeapType<Type>:: binaryHeapType(binaryHeapType<Type> & rhs)
{
	if (this != & rhs)
	{
		size = rhs.size; 
		heapList = rhs.heapList; 
	}
}

// Establish a heap from an arbitrary arrangement of items.
template <class Type>     
void binaryHeapType<Type>::buildHeap ( )	
{
	int i = size / 2; 

	for (; i >= 1; i--)
		percolateDown(i); 
}
    
// Internal method to percolate down in the heap. The starting position is i.
template <class Type>     
void binaryHeapType<Type>::percolateDown ( int i)
{
	Type tmp;  
	int p, left, right;

	if (i >= size)
		return; 

	p = i; 
	while (true)
	{
		left = 2 * p;
		right = left + 1; 
		
		if (left > size)
			return; 

		if (left == size)
		{
			if (heapList[left]<heapList[p])
			{
				tmp = heapList[p]; 
				heapList[p] = heapList[left]; 
				heapList[left] = tmp; 
			}
			return; 
		}
		else
		{
			if (heapList[left]<=heapList[right])
			{
				if (heapList[left]<heapList[p])
				{
					tmp = heapList[p]; 
					heapList[p] = heapList[left]; 
					heapList[left] = tmp; 
					p = left; 
				}
				else
					return; 
			}
			else 
			{
				if (heapList[right]<heapList[p])
				{
					tmp = heapList[p]; 
					heapList[p] = heapList[right]; 
					heapList[right] = tmp;
					p = right; 
				}
				else
					return; 
			}
		}
	}
}

// Internal method to percolate up in the heap. The starting position is i.
template <class Type>     
void binaryHeapType<Type>::percolateUp ( int i)
{
	Type tmp;  
	int left, right, p, old;

	p = i; 
	while (p > 1)
	{
		old = p; 
		p = p/2; 
		
		//old is the left child index
		if (old % 2 == 0)
		{
			if (heapList[p] > heapList[old]) 
			{
				tmp = heapList[p]; 
				heapList[p] = heapList[old]; 
				heapList[old] = tmp; 
			}
		}
		else //old is the right child index, i.e., old is odd.
		{
			if (heapList[p] > heapList[old])
			{
				if (heapList[old] <= heapList[old - 1]) 
				{
					tmp = heapList[p]; 
					heapList[p] = heapList[old]; 
					heapList[old] = tmp; 
				}
				else
				{
					tmp = heapList[p]; 
					heapList[p] = heapList[old - 1]; 
					heapList[old - 1] = tmp; 
				}
			}
		}
	}
}
#endif
