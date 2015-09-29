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
//				to use another list file. This is the file that contains
//				the hash table functions.
//
////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <string>

#include "personHashTable.h"

using namespace std;

hashTable::hashTable()
{
	for(int i = 0; i < tableSize; i++)
	{
		table[i] = new personType;
		table[i]->name = "nothing";
		table[i]->grade = 0;
		table[i]->ID = 0;
		table[i]->next = NULL;
	}
}

void hashTable::addPerson(string name, int ID, int grade)
{
	int x = Hash(name);

	if(table[x]->name == "nothing") //Index is empty
	{
		table[x]->name = name;
		table[x]->ID = ID;
		table[x]->grade = grade;
	}
	else							//Index is not empty
	{
		personType * point = table[x];
		personType * other = new personType;
		other->grade = grade;
		other->ID = ID;
		other->name = name;
		other->next = NULL;
		while(point->next != NULL)
		{
			point = point->next;
		}
		point->next = other;
	}
}

int hashTable::numPeople(int x)
{
	int count = 0;
	if(table[x]->name == "nothing")
	{
		return count;
	}
	else
	{
		count++;
		personType * point = table[x];
		while(point->next != NULL)
		{
			count++;
			point = point->next;
		}
	}
	return count;
}

void hashTable::printTable()
{
	personType * point;
	int num;
	for(int i = 0; i < tableSize; i++)
	{
		point = table[i];
		num = numPeople(i);
		cout << "----------------" << endl;
		cout << "At index " << i << endl;
		while(point != NULL)
		{
			cout << point->name << "  " << point->ID << "  " << point->grade << endl;
			point = point->next;
		}
		cout << "Number of Students = " << num << endl;
		cout << "----------------" << endl;
	}
}



void hashTable::removePerson(string y)
{
	int x = Hash(y);

	personType * delPoint;
	personType * point;
	personType * point2;

	//empty list
	if(table[x]->name == "nothing")
	{
		cout << y << " was not found." << endl;
	}
	// one item in list and name mathes
	else if(table[x]->name == y && table[x]->next == NULL)
	{
		table[x]->name = "nothing";
		table[x]->ID = 0;
		table[x]->grade = 0;
		cout << y << " has been deleted." << endl;
	}
	//more than one item in list and name matches first item
	else if(table[x]->name == y)
	{
		delPoint = table[x];
		table[x] = table[x]->next;
		delete delPoint;
	}
	//list has items but match is not first item
	else
	{
		point = table[x]->next;
		point2 = table[x];

		while(point != NULL && point->name != y)
		{
			point2 = point;
			point = point->next;
		}
		//no matches
		if (point == NULL)
		{
			cout << y << " was not found." << endl;
		}
		else
		{
			delPoint = point;
			point = point->next;
			point2->next = point;
			delete delPoint;
			cout << y << " has been deleted." << endl;
		}
	}
}
int hashTable::Hash(string key)
{
	int hash = 0;
	int index;


	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash + (int)key[i]) * 17;
	}
	
	index = hash % tableSize;
	
	return index;
}