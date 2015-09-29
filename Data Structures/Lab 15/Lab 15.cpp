// *****************************************************************
// Author:			Brandon
// Class:			CSCI 3333, Spring 2014
// Lab 15:			Hashing, separate chaining 
// Date:			4/22/2014
// Comment:			The code here is meant to be revised.
//
//-----------------------------------------------------------------
//
// Description: This program is to implement a generic hash table with 
//				open addressing techniques to resolve collisions.
// *****************************************************************
#include <iostream>
#include <cassert>
#include <string> 
#include <cstdlib>
#include <ctime>

#include "lab3333_15_head.h"	
#include "personType.h"

using namespace std; 

static const char alpha[] = 
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";

int lenghthOfAlpha = sizeof(alpha) -1;

char randomChar()
{
	return alpha[rand() % lenghthOfAlpha];
}

string returnWord()
{
	string word;
	for (unsigned int i = 0; i < 10; i++)
	{
		word += randomChar();
	}
	return word;
}

personType rerurnPerson()
{
	string word = returnWord();
	personType person(word);
	int num[6];
	double num2[2];
	for (int i = 0; i < 6; i++)
	{
		num[i] = rand() % 9;
	}
	for (int j = 0; j < 2; j++)
	{
		num2[j] = rand() & 2;
	}

	person.setID(num);
	person.setGrade(num2);

	return person;
}

int main()
{
	/**********************************************************
	 Part A: Some practice
	 
	 Note:	Three open addressing types are defined: 
			For linear probing, Tag = LINEAR_PROBING,
			For quadratic, Tag = QUADRATIC_PROBING, 
			For double hashing,  Tag = DOUBLE_HASHING
	 **********************************************************/

	//pratice integer hash table
	int S = 10; 
	hashTableType<int, intHashFunctor, LINEAR_PROBING> ht(S); 
	int num, i, j, N=20; 
	bool tag; 

	//load the table
	srand(time(0)); 
	for (i=0; i<15; i++)
	{
		num = 2 + rand()%100; 
		ht.insert(num); 
	}
	//print hash table
	cout<<" table size = " << ht.getTableSize()<<endl
		<<" table count = " <<ht.getTableCount()<<endl; 
	ht.print(); 
	cout<<endl<<"*************************"<<endl;
	
	
	//search hash table
	for (i=0; i<3; i++)
	{
		tag = false; 
		cout<<" enter a target value for search "; 
		cin>>num; 
		tag = ht.search(num);
		if (tag)
		{
			cout<<" found " <<num <<"............" <<endl; 
			ht.print(); 
			cout<<endl<<"after removal --------------------------------"<<endl; 
			ht.remove(num); 
			ht.print(); 
			cout<<endl<<"--------------------------------"<<endl; 
		}
		else
			cout<< " failed to find " << num  <<endl; 
		system("pause"); 
	}
	

	/**********************************************************************
	 Part B: Redo part A. Here, you shall practice a string type hashTable. 
	 You can use the hash function hashStr to map a string to an int. You 
	 shall also define a function to generate a random string.  
	 **********************************************************************/
	
	//Write your code here
	bool tag2; 
	hashTableType<string,strHashFunctor, LINEAR_PROBING> ht2(S);
	string word, word2;

	for(i = 0; i < 20; i++)
	{
		word = returnWord();
		j = hashStr(word, ht2.getTableSize());
		ht2.insert(word);
	}

	cout<<" table size = " << ht2.getTableSize()<<endl
		<<" table count = " <<ht2.getTableCount()<<endl; 
	
	ht2.print(); 
	cout<<endl<<"*************************"<<endl;
	

	for (i=0; i<3; i++)
	{
		tag2= false; 
		cout<<" enter a target value for search "; 
		cin>>word2; 
		tag2 = ht2.search(word2);
		if (tag2)
		{
			cout<<" found " <<word2<<"............" <<endl; 
			ht2.print(); 
			cout<<endl<<"after removal --------------------------------"<<endl; 
			ht2.remove(word2); 
			ht2.print(); 
			cout<<endl<<"--------------------------------"<<endl; 
		}
		else
			cout<< " failed to find " << word2  <<endl; 
		system("pause"); 
	}

	/**********************************************************************
	 Part C:  Redo part A. Here, you shall practice a personType hashTable. 
	 You use the hash function hashStr to map a person's name to an int. You 
	 shall also define a function to generate a random person.  
	 ***********************************************************************/
	
	//Write your code here
	bool tag3; 
	hashTableType<personType, strHashFunctor, LINEAR_PROBING> ht3(S);
	personType person;
	string word3;

	for(i = 0; i < 20; i++)
	{
		person = rerurnPerson();
		j = hashStr(person.returnName(), ht3.getTableSize());
		ht3.insert(person.returnName());
	}

	cout<<" table size = " << ht3.getTableSize()<<endl
		<<" table count = " <<ht3.getTableCount()<<endl; 
	
	ht3.print(); 
	cout<<endl<<"*************************"<<endl;
	

	for (i=0; i<3; i++)
	{
		tag3= false; 
		cout<<" enter a target value for search "; 
		cin>>word3; 
		tag3 = ht3.search(word3);
		if (tag3)
		{
			cout<<" found " <<word3<<"............" <<endl; 
			ht3.print(); 
			cout<<endl<<"after removal --------------------------------"<<endl; 
			ht3.remove(word3); 
			ht3.print(); 
			cout<<endl<<"--------------------------------"<<endl; 
		}
		else
			cout<< " failed to find " << word3  <<endl; 
		system("pause"); 
	}
	//complete the program
	return 0; 
}