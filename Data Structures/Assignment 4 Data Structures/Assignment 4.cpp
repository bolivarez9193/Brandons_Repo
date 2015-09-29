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
//				to use another list file. This is the main driver file.
//
////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <string>

#include "personHashTable.h"

using namespace std;

int main()
{
	hashTable example;
	string name = "";
	example.addPerson("Chris", 542369, 88);
	example.addPerson("Jill", 713549, 90);
	example.addPerson("Barry", 143925, 74);
	example.addPerson("Joseph", 317564, 77);
	

	example.printTable();
	

	return 0;
}