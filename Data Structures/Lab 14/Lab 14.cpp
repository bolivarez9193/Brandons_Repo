// *****************************************************************
// Author:			Brandon Olivarez
// Class:			CSCI3333, Spring 2014
// Lab 14:			Hashing, separate chaining 
// Date:			4/22/2014
// Comment:			The code here is meant to be revised.
//
//-----------------------------------------------------------------
//
// Description: This program is to implement a generic hash table using 
//				separate chaining to resolve collisions.
// *****************************************************************
#include <iostream>
#include <cassert>
#include <string> 
#include <cstdlib>
#include <ctime>

#include "lab3333_14_head.h"	
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
	 **********************************************************/
	
	//pratice integer hash table
	int S = 10; 
	hashTableType<int, intHashFunctor> ht(S); 
	int num, i, j, N=20; 
	bool tag; 

	//load the table
	srand(time(0)); 
	for (i=0; i<40; i++)
	{
		num = rand()%100; 
		j = hashInt(num, ht.getTableSize());
		ht.insert(num); 
	}
	//print hash table
	cout<<" table size = " << ht.getTableSize()<<endl
		<<" table count = " <<ht.getTableCount()<<endl; 
	for (i=0; i<S; i++)
	{
		cout<<" i = " << i <<endl; 
		ht.print(i); 
		cout<<endl<<"*************************"<<endl;
	}
	
	/*
	cout<<" testing rehash " <<endl; 
	ht.reHash(); 
	//print new hash table
	cout<<" new size = " << ht.getTableSize()<<endl
		<<" new count = " <<ht.getTableCount()<<endl; 
	for (i=0; i<ht.getTableSize(); i++)
	{
		cout<<" i = " << i <<endl; 
		ht.print(i); 
		cout<<endl<<"*************************"<<endl;
	}
	*/
	//search hash table
	for (i=0; i<S; i++)
	{
		tag = false; 
		num = rand()%100;
		j = hashInt(num, ht.getTableSize());
		tag = ht.search(num);
		if (tag)
		{
			cout<<" found " <<num << " at j = " << j <<"............" <<endl; 
			ht.print(j); 
			cout<<endl<<"after removal --------------------------------"<<endl; 
			ht.remove(num); 
			ht.print(j); 
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
	char tag2; 
	hashTableType<string, strHashFunctor> ht2(S);
	string word, word2;

	for(i = 0; i < 20; i++)
	{
		word = returnWord();
		j = hashStr(word, ht2.getTableSize());
		ht2.insert(word);
	}

	cout<<" table size = " << ht2.getTableSize()<<endl
		<<" table count = " <<ht2.getTableCount()<<endl; 
	for (i=0; i<S; i++)
	{
		cout<<" i = " << i <<endl; 
		ht2.print(i); 
		cout<<endl<<"*************************"<<endl;
	}
	// I decided to have the user search for the string
	while (true)
	{
		cout<<"Want to play with searching or deletion(s/d)? "<<endl; 
		cout<<"Enter q to stop "; 
		cin>>tag2; 
		switch (tag2)
		{
		case 'd':
		case 'D':
				cout<<"What to be deleted? "; 
				cin>> word2; 
				ht2.remove(word2); 
				cout<<endl; 
				break; 
		case 's': 
		case 'S':
				cout<<"What to be searched for? "; 
				cin>>word2; 
				if(ht2.search(word2))
					cout<<"found "<< word2 <<" in the tree "<<endl; 
				else 
					cout<<"failed to find " <<word2<<" in the tree "<<endl; 
		default: 
				break;
		}
		if (tag2 == 'q' || tag2 == 'Q')
			break; 
	}
	
	/**********************************************************************
	 Part C:  Redo part A. Here, you shall practice a personType hashTable. 
	 You use the hash function hashStr to map a person's name to an int. You 
	 shall also define a function to generate a random person.  
	 ***********************************************************************/
	
	//Write your code here
	char tag3; 
	hashTableType<personType, strHashFunctor> ht3(S);
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
	for (i=0; i<S; i++)
	{
		cout<<" i = " << i <<endl; 
		ht3.print(i); 
		cout<<endl<<"*************************"<<endl;
	}
	// I decided to have the user search for the string
	while (true)
	{
		cout<<"Want to play with searching or deletion(s/d)? "<<endl; 
		cout<<"Enter q to stop "; 
		cin>>tag3; 
		switch (tag3)
		{
		case 'd':
		case 'D':
				cout<<"What to be deleted? "; 
				cin>> word3; 
				ht3.remove(word3); 
				cout<<endl; 
				break; 
		case 's': 
		case 'S':
				cout<<"What to be searched for? "; 
				cin>>word3; 
				if(ht3.search(word3))
					cout<<"found "<< word3 <<" in the tree "<<endl; 
				else 
					cout<<"failed to find " <<word3<<" in the tree "<<endl; 
		default: 
				break;
		}
		if (tag3 == 'q' || tag3 == 'Q')
			break; 
	}

	//complete the program
	return 0; 
}