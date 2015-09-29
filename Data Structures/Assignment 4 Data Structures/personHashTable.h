///////////////////////////////////////////////////////////////////////
// Name: Brandon Olivarez
//
// ID#: 20028785
//
// Class: CSCI 3333.02
//
// Professor: Zhixiang Chen
//
// Date: 4/22/2014
//
// Description: For this assignment, we will derive a hash table
//				of a personType class. I decided not to use a prexisting
//				list, and use a modified personType class that also
//				acts as a linklist. Sorry, I couldn't figure out how
//				to use another list file. This is the prototype hash
//				table file.
//
////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <string>


using namespace std;

#ifndef HASH_H
#define HASH_H

class hashTable{
private:
	static const int tableSize = 4;

	struct personType{
		string name;
		int ID;
		int grade;
		personType * next;
	};

	personType * table[tableSize];

public:
	hashTable();
	int Hash(string key);
	void addPerson(string name, int ID, int grade);
	int numPeople(int x);
	void printTable();
	void removePerson(string y);

};

#endif