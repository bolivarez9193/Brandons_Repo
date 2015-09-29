/****************************************************************************************
*  Program Name:		lab3333_14_head.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 14:				Header file for Lab 14
*  Date:				08/29/2013
*  Description: This file contains the prototype of the class template hashTableType
*				Separate chaining technique is used to resolve collisions.
*****************************************************************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "arrayBasedList_head.h"
using namespace std; 


#ifndef H_BST
#define H_BST

/**************************************
 hash functions
 **************************************/


//the simplest one
int hashInt(int key, int size)
{
	return key % size; 
}

//convert a string into an int, using a polynomial of a prime value 
//for the variable and them mod the int
int hashStr(string key,  int size, int p=37)
{
	int N = 0; 
	int i, len;
	len = key.length();

	for (i=0; i< len; i++)
	{
		N = N * p + static_cast<int>(key.at(i));
		N = N % size; 
	}
	return N; 
}

//this function finds the least prime that is bigger than the given p > 0.
//In fact, when repeatedly called, this fucntion can find a list of primes 
//that are bigger than the given p. 
int nextPrime(int p)
{
	assert(p>=2); 
	static int old = p; 
	int n, i, upper; 

	for (n=old + 1; ; n++)
	{
		if (n %2 ==0)
			continue; 
		upper = static_cast<int>(sqrt(double(n))) + 1; 
		for (i=2; i<=upper; i++)
		{
			if (n % i == 0)
				break; 
		}
		if (i> upper) 
		{
			old = n; 
			return n; 
		}
	} 
}


/********************************************************
experiment generic hash functions
*********************************************************/

struct intHashFunctor
{
    int operator()(int key, int size, int p) { return hashInt(key, size); }
};

struct strHashFunctor
{
	int operator()(string key, int size, int p) { return hashStr(key,size,p);}
};

template<class Type, typename Functor>
int genericHash(Functor whichHash, Type & x, int size, int p =37)
{
	return whichHash(x, size, p); 
}

/********************************************************
 This part gives the hash table design and implementation
 ********************************************************/
template<class Type, typename Functor>
class hashTableType
{
public: 
	explicit hashTableType( int size = 101);		//default constructor
	hashTableType(const hashTableType<Type, Functor> & rhs);		//copy constructor
	~hashTableType(); 								//destructor

	//bool search (const int i, const Type & x) const;			//find x in the table or not
	bool search(const  Type & x) ;			//find x in the table or not
	void insert(const Type & x);				//insert x into the tree
	void remove(const Type & x);				//remove x from the tree
	bool isEmpty();								//check if the table is empty or not
	void destroy();								//delete the table
	int getTableSize(){return tableSize;}		//the table capacity
	int getTableCount(){return count;}			//actual number of elements in the table
	void print(const int i); 
	//overload operator =
	const hashTableType<Type, Functor> & operator=(const hashTableType<Type, Functor> & rhs); 
	void reHash();								//double the hashTable size to the next nearest prime and rehash

private: 
	Functor whichHash; 
	arrayListType<Type> * table; 
	int count; 
	int tableSize; 

	void copyHashTable(const hashTableType<Type, Functor> & rhs);							//a deep copy method
}; 


//rehash: double the hash table size to next nearest prime
template <class Type, typename Functor>
void hashTableType<Type, Functor>::reHash( )
{
	int newSize, i, j, k, cnt; 
	arrayListType<Type> * newTable;
	Type x;

	cnt=0; 
	newSize = nextPrime(2*tableSize); 	
	newTable = new arrayListType<Type> [newSize]; 
	
	for (i = 0; i<tableSize; i++)
	{
		for (j=0; j<table[i].length(); i++)
		{
			x = table[i][j];
			k = genericHash(whichHash, x, newSize);
			newTable[k].insertLast(x); 
			cnt++; 
		}
		if (cnt>=count)
				break;
	}

	for (i=0; i<tableSize; i++)
		table[i].destroyList(); 
	delete[] table; 

	table = newTable; 
	tableSize = newSize; 
}

//print
template <class Type, typename Functor>
void hashTableType<Type, Functor>::print(const int i)
{
	table[i].print(); 
}


//default constructor
template <class Type, typename Functor>
hashTableType<Type, Functor>::hashTableType(int size)
{
	tableSize = size;
	table = new arrayListType<Type> [size];
	count = 0; 
}

//copy constructor
template<class Type, typename Functor>
hashTableType<Type, Functor>::hashTableType(const hashTableType<Type, Functor> & rhs)
{
	if (this != & rhs)
	{
		copyHashTable();
	}
}
	
//destructor
template<class Type, typename Functor> 
hashTableType<Type, Functor>::~hashTableType()
{
	destroy(); 
}



template<class Type, typename Functor>
bool hashTableType<Type, Functor>::search(const Type & x) 
{
	int i; 
	i = genericHash(whichHash, x, tableSize); 
	
	if (table[i].isEmpty())
		return false; 

	if (i >=0 && i < tableSize)
		return table[i].search(x);
	else
		return false; 
}


//check whether the tree is empty or not
template <class Type, typename Functor>
bool hashTableType<Type, Functor>::isEmpty()
{
	return this->count == 0; 
}

//delete the tree
template<class Type, typename Functor>
void hashTableType<Type, Functor>::destroy()
{
	for (int i=0; i<tableSize; i++)
		table[i].destroyList(); 
	delete[] table; 
	this->count = 0; 
	tableSize = 0; 
}


//insert x into the tree
template<class Type, typename Functor>
void hashTableType<Type, Functor>::insert(const Type & x)
{
	int i; 
	i = genericHash(whichHash, x, tableSize); 

	if (i >=0 && i < tableSize)
	{
		count++; 
		cout<<" now inserting " <<x << " into the hash table at positon " << i <<endl; 
		table[i].insertLast(x);
	}
	else
	{
		cout<<" cannot insert " << x <<" because the hashed value " 
			<< i  << " is out of scope. " <<endl; 
	}
}

//remove x from the tree
template<class Type, typename Functor>
void hashTableType<Type, Functor>::remove(const Type & x)	
{
	int i; 
	i = genericHash(whichHash, x, tableSize); 
	
	if (i >=0 && i < tableSize)
	{
		cout<<" now remove " <<x << " from the hash table at positon " << i<<endl; 
		if (table[i].deleteItem(x))
			count--; 
	}
	else
	{
		cout<<" cannot remove " << x <<" because the hashed value " 
			<< i  << " is out of scope. " <<endl; 
	}
}

//overload operator =
template<class Type, typename Functor>
const hashTableType<Type, Functor> & hashTableType<Type, Functor>::operator=(const hashTableType<Type, Functor> & rhs)
{
	if (this != &rhs)
		copyHashTable(rhs); 

	return this; 
}


/*****************************************************************
 auxillary functions
 *****************************************************************/

template<class Type, typename Functor>
void hashTableType<Type, Functor> :: copyHashTable(const hashTableType<Type, Functor> & rhs)
{
	if (this == &rhs)
		return; 
	destroy(); 
	count = rhs.count; 
	tableSize = rhs.tableSize; 
	table = new arrayListType<Type, Functor> [tableSize]; 
	for (int i =0; i < count ; i++)
		table[i] = rhs.table[i];
}


#endif

