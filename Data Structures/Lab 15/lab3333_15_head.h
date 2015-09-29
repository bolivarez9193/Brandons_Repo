/****************************************************************************************
*  Program Name:		lab3333_15_head.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 15:				Header file for Lab 15
*  Date:				10/08/2013
*  Description: This file contains the prototype of the class template hashTableType
*				Open addressing is used to resolve collisons
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
	int old = p; 
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
 Type: for element type
 Functor: for hash function
 Tag: for linear probing, Tag = LINEAR_PROBING,
	  for quadratic, Tag = QUADRATIC_PROBING, 
	  for double hashing,  Tag = DOUBLE_HASING
 ********************************************************/
enum hashType {LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING};

template<class Type, typename Functor, hashType Tag>
class hashTableType
{
public: 
	explicit hashTableType( int size = 101);		//default constructor
	hashTableType(const hashTableType<Type, Functor, Tag> & rhs);		//copy constructor
	~hashTableType(); 								//destructor

	bool search(const Type &x); 
	void insert(const Type &x); 
	void remove(const Type &x); 
	bool searchLinearProbing(const  Type & x) ;			//find x in the table or not
	void insertLinearProbing(const Type & x);				//insert x into the tree
	void removeLinearProbing(const Type & x);				//remove x from the tree
	bool searchQuadraticProbing(const  Type & x) ;			//find x in the table or not
	void insertQuadraticProbing(const Type & x);				//insert x into the tree
	void removeQuadraticProbing(const Type & x);				//remove x from the tree
	bool searchDoubleHash(const  Type & x) ;			//find x in the table or not
	void insertDoubleHash(const Type & x);				//insert x into the tree
	void removeDoubleHash(const Type & x);				//remove x from the tree
	bool isEmpty();								//check if the table is empty or not
	void destroy();								//delete the table
	int getTableSize(){return tableSize;}		//the table capacity
	int getTableCount(){return count;}			//actual number of elements in the table
	void print(); 
	void makeEmpty(); 
	//overload operator =
	const hashTableType<Type, Functor, Tag> & operator=(const hashTableType<Type, Functor, Tag> & rhs); 
	void reHash();								//double the hashTable size to the next nearest prime and rehash

	enum EntryType{OCCUPIED, EMPTY, DELETED};
private: 
	struct HashEntryType
	{
		Type info; 
		EntryType flag; 
		HashEntryType( Type  e = Type(), EntryType i = EMPTY)
			: info(e), flag(i){}; 
		const HashEntryType & operator=(HashEntryType & rhs)
			{info = rhs.info; flag = rhs.flag; return *this;}
	};
	Functor whichHash; 
	HashEntryType * table; 
	int count; 
	int tableSize; 

	void copyHashTable(const hashTableType<Type, Functor, Tag> & rhs);	//a deep copy method
}; 

template <class Type, typename Functor, hashType Tag>
bool hashTableType<Type, Functor, Tag>::search(const Type &x)
{
	if (Tag == LINEAR_PROBING)
		return searchLinearProbing(x); 
	else if (Tag == QUADRATIC_PROBING)
		return searchQuadraticProbing(x); 
	else
		return searchDoubleHash(x); 
}

template <class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::insert(const Type &x)
{
	if (Tag == LINEAR_PROBING)
		insertLinearProbing(x); 
	else if (Tag == QUADRATIC_PROBING)
		insertQuadraticProbing(x); 
	else
		insertDoubleHash(x); 
}

template <class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::remove(const Type &x)
{
	if (Tag == LINEAR_PROBING)
		removeLinearProbing(x); 
	else if (Tag == QUADRATIC_PROBING)
		removeQuadraticProbing(x); 
	else
		removeDoubleHash(x); 
}

//rehash: double the hash table size to next nearest prime
template <class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::reHash( )
{
	int newSize, i, j, oldSize, oldCnt; 
	HashEntryType *oldTable; 
	Type x;

	oldTable = table; 
	oldSize = tableSize; 
	oldCnt = count; 

	tableSize = nextPrime(2*oldSize); 	
	table = new HashEntryType [tableSize]; 
	
	for (i = 0; i<tableSize; i++)
	{
		table[i].flag == EMPTY; 
	}

	for (i=0; i<oldSize; i++)
	{
		if (oldTable[i].flag == OCCUPIED)
		{
			insert(oldTable[i].info); 
		}
	}
	count = oldCnt;
	delete[] oldTable;  
}

//print
template <class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::print()
{
	for (int i=0; i<tableSize; i++)
	{
		cout<<" i = " << i << "  "; 
		if (table[i].flag == OCCUPIED) 
			cout<<table[i].info<<endl;
		else if (table[i].flag == DELETED) 
			cout<<" Deleted "<<endl;
		else 
			cout<<" Empty " <<endl; 
	}
}


//default constructor
template <class Type, typename Functor, hashType Tag>
hashTableType<Type, Functor, Tag>::hashTableType(int size)
{
	tableSize = size;
	table = new HashEntryType [size];
	count = 0; 
}

//copy constructor
template<class Type, typename Functor, hashType Tag>
hashTableType<Type, Functor, Tag>::hashTableType(const hashTableType<Type, Functor, Tag> & rhs)
{
	if (this != & rhs)
	{
		copyHashTable();
	}
}
	
//destructor
template<class Type, typename Functor, hashType Tag> 
hashTableType<Type, Functor, Tag>::~hashTableType()
{
	destroy(); 
}



template<class Type, typename Functor, hashType Tag>
bool hashTableType<Type, Functor, Tag>::searchLinearProbing(const Type & x) 
{
	int i, j, p, cnt; 
	
	p = genericHash(whichHash, x, tableSize); 
	j = cnt = 0; 
	while (true)
	{
		i = (p+j) % tableSize; 
		if (table[i].flag == OCCUPIED && table[i].info == x)
			return true; 
		else if (table[i].flag == EMPTY || cnt == tableSize)
			return false; 
		else 
		{
			j++; 
			cnt++; 
		}
	}
}

template<class Type, typename Functor, hashType Tag>
bool hashTableType<Type, Functor, Tag>::searchQuadraticProbing(const Type & x) 
{
	int i, j, p, cnt; 
	
	p = genericHash(whichHash, x, tableSize); 
	j = cnt = 0; 
	while (true)
	{
		i = (p+j*j) % tableSize; 
		if (table[i].flag == OCCUPIED && table[i].info == x)
			return true; 
		else if (table[i].flag == EMPTY || cnt == tableSize)
			return false; 
		else 
		{
			j++; 
			cnt++; 
		}
	}
}

template<class Type, typename Functor, hashType Tag>
bool hashTableType<Type, Functor, Tag>::searchDoubleHash(const Type & x) 
{
	int i, j, p, cnt, h2; 
	
	p = genericHash(whichHash, x, tableSize); 
	h2 = 7 - p % 7;								//h2 is the second hash function that can be changed 
	j = cnt = 0; 
	while (true)
	{
		i = (p+j*h2) % tableSize; 
		if (table[i].flag == OCCUPIED && table[i].info == x)
			return true; 
		else if (table[i].flag == EMPTY || cnt == tableSize)
			return false; 
		else 
		{
			j++; 
			cnt++; 
		}
	}
}

//check whether the tree is empty or not
template <class Type, typename Functor, hashType Tag>
bool hashTableType<Type, Functor, Tag>::isEmpty()
{
	return this->count == 0; 
}

//delete the tree
template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::destroy()
{
	
	delete[] table; 
	this->count = 0; 
	tableSize = 0; 
	table = NULL; 
}


//insert x into the tree
template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::insertLinearProbing(const Type & x)
{
	int i, j, p, cnt; 

	p = genericHash(whichHash, x, tableSize); 
	j = cnt = 0; 
	while (true)
	{
		i = (p+j) % tableSize; 
		if (table[i].flag == EMPTY || table[i].flag == DELETED)
		{
			table[i].info = x; 
			table[i].flag = OCCUPIED; 
			count++; 
			break; 
		}
		else if (cnt == tableSize)
		{
			cout<<" failed to insert the new element " << x <<endl; 
			break; 
		}
		else 
		{
			j++; 
			cnt++; 
		}
	}

	//check to see if rehash is needed
	if (count >= tableSize / 2)
	{
		cout<<" now, reshah when the count " << count <<" >=  tableSize " << tableSize <<endl; 
		reHash(); 
	}
}

//insert x into the tree
template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::insertQuadraticProbing(const Type & x)
{
	int i, j, p, cnt; 

	p = genericHash(whichHash, x, tableSize); 
	j = cnt = 0; 
	while (true)
	{
		i = (p+j*j) % tableSize; 
		if (table[i].flag == EMPTY || table[i].flag == DELETED)
		{
			table[i].info = x; 
			table[i].flag = OCCUPIED; 
			count++; 
			break; 
		}
		else if (cnt == tableSize)
		{
			cout<<" failed to insert the new element " << x <<endl; 
			break; 
		}
		else 
		{
			j++; 
			cnt++; 
		}
	}

	//check to see if rehash is needed
	if (count >= tableSize / 2)
	{
		cout<<" now, reshah when the count " << count <<" >=  tableSize " << tableSize <<endl; 
		reHash(); 
	}
}

//insert x into the tree
template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::insertDoubleHash(const Type & x)
{
	int i, j, p, cnt, h2; 

	p = genericHash(whichHash, x, tableSize); 
	h2 = 7 - p % 7;				//the second hashing fucntion
	j = cnt = 0; 
	while (true)
	{
		i = (p + j * h2) % tableSize; 
		if (table[i].flag == EMPTY || table[i].flag == DELETED)
		{
			table[i].info = x; 
			table[i].flag = OCCUPIED; 
			count++; 
			break; 
		}
		else if (cnt == tableSize)
		{
			cout<<" failed to insert the new element " << x <<endl; 
			break; 
		}
		else 
		{
			j++; 
			cnt++; 
		}
	}

	//check to see if rehash is needed
	if (count >= tableSize / 2)
	{
		cout<<" now, reshah when the count " << count <<" >=  tableSize " << tableSize <<endl; 
		reHash(); 
	}
}


//remove x from the tree
template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::removeLinearProbing(const Type & x)	
{
	int i, j, p, cnt; 
	
	p = genericHash(whichHash, x, tableSize); 
	j = cnt = 0; 
	while (true)
	{
		i = (p+j) % tableSize; 
		if (table[i].flag == OCCUPIED && table[i].info == x)
		{
			cout<<" now remove " <<x << " from the hash table " <<endl;
			table[i].flag = DELETED; 
			return; 
		}
		else if (table[i].flag == EMPTY || cnt == tableSize)
		{
			cout<<" the element " << x <<" is not in the hash table " <<endl; 
			return; 
		}
		else 
		{
			j++; 
			cnt++; 
		}
	}
}

//remove x from the tree
template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::removeQuadraticProbing(const Type & x)	
{
	int i, j, p, cnt; 
	
	p = genericHash(whichHash, x, tableSize); 
	j = cnt = 0; 
	while (true)
	{
		i = (p+j*j) % tableSize; 
		if (table[i].flag == OCCUPIED && table[i].info == x)
		{
			cout<<" now remove " <<x << " from the hash table " <<endl;
			table[i].flag = DELETED; 
			return; 
		}
		else if (table[i].flag == EMPTY || cnt == tableSize)
		{
			cout<<" the element " << x <<" is not in the hash table " <<endl; 
			return; 
		}
		else 
		{
			j++; 
			cnt++; 
		}
	}
}

//remove x from the tree
template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag>::removeDoubleHash(const Type & x)	
{
	int i, j, p, cnt, h2; 
	
	p = genericHash(whichHash, x, tableSize); 
	
	h2 = 7 - p % 7;				//the second hash function
	j = cnt = 0; 
	while (true)
	{
		i = (p+j*h2) % tableSize; 
		if (table[i].flag == OCCUPIED && table[i].info == x)
		{
			cout<<" now remove " <<x << " from the hash table " <<endl;
			table[i].flag = DELETED; 
			return; 
		}
		else if (table[i].flag == EMPTY || cnt == tableSize)
		{
			cout<<" the element " << x <<" is not in the hash table " <<endl; 
			return; 
		}
		else 
		{
			j++; 
			cnt++; 
		}
	}
}

//overload operator =
template<class Type, typename Functor, hashType Tag>
const hashTableType<Type, Functor, Tag> & hashTableType<Type, Functor, Tag>::operator=(const hashTableType<Type, Functor, Tag> & rhs)
{
	if (this != &rhs)
		copyHashTable(rhs); 

	return this; 
}


/*****************************************************************
 auxillary functions
 *****************************************************************/

template<class Type, typename Functor, hashType Tag>
void hashTableType<Type, Functor, Tag> :: copyHashTable(const hashTableType<Type, Functor, Tag> & rhs)
{
	if (this == &rhs)
		return; 
	destroy(); 
	count = rhs.count; 
	tableSize = rhs.tableSize; 
	table = new HashEntryType [tableSize]; 
	for (int i =0; i < count ; i++)
		table[i] = rhs.table[i];
}


#endif

