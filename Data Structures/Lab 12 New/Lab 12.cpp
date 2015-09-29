// *****************************************************************
// Author:			Zhixiang Chen
// Class:			CSCI/CMPE 2380, Spring 2009
// Lab Optional 5:	Binary search tree
// Date:			January 17, 2009
// Comment:			The code here is meant to be revised.
//
//-----------------------------------------------------------------
//
// Description: This program is to implement the binary search tree 
// class template
// *****************************************************************
#include <iostream>
#include <cassert>
#include <string> 
#include <cstdlib>
#include <fstream>
#include <iomanip>

#include "lab2380_optional_5_head.h"	//changed by sirisha
#include "personType.h"

using namespace std; 

int main()
{
	/**********************************************************
	 Part A: Some practice
	 **********************************************************/
	//var decarations
	unsigned int seed;					//a random seed
	int num;							//to hold an int value
	binarySearchTree<int> tree;			//create a list of int type
	char tag; 
	
	cout<<"loading the list with random numbers between 0 and 666 ... "<<endl; 

	cout<<"Enter a random seed => ";	//get the random seed
	cin >> seed; 
	srand(seed);						//set the randon seed

	for (int i=0; i <10 ; i++)			//insert 50 random numbers into the list
	{
		num = rand()%31; 
		cout<<num<<"  ";
		tree.insert(num);
	}
	cout<<endl; 

	cout<<"inorder traversal ..... "<<endl; 
	tree.inOrderTraversal(); 
	cout<<"preorder traversal ..... "<<endl; 
	tree.preOrderTraversal(); 
	cout<<"postorder traversal ..... "<<endl; 
	tree.postOrderTraversal(); 
	cout<<"tree height is "<< tree.treeHeight()<<endl; 
	cout<<"tree node count is "<< tree.treeNodeCount()<<endl; 
	cout<<"tree leave count is "<< tree.treeLeaveCount()<<endl; 

	cout<<endl; 
	
	//test delete and search
	while (true)
	{
		cout<<"Want to play with searching or deletion(s/d)? "<<endl; 
		cout<<"Enter q to stop "; 
		cin>>tag; 
		switch (tag)
		{
		case 'd':
		case 'D':
				cout<<"What to be deleted? "; 
				cin>> num; 
				tree.remove(num); 
				tree.inOrderTraversal(); 
				cout<<endl; 
				break; 
		case 's': 
		case 'S':
				cout<<"What to be searched for? "; 
				cin>>num; 
				if(tree.find(num))
					cout<<"found "<< num <<" in the tree "<<endl; 
				else 
					cout<<"failed to find " <<num<<" in the tree "<<endl; 
		default: 
				break;
		}
		if (tag == 'q' || tag == 'Q')
			break; 
	}
	
	/**********************************************************************
	 Part B: Try to create a binary search tree of strings and practice 
	 basic tree operations such as insertion, deletion, search, etc.
	 **********************************************************************/
	
	//Write your code here
	binarySearchTree<string> tree2;
	char tag2;
	string word;
	tree2.insert("hello");
	tree2.insert("goodbye");
	tree2.insert("morning");
	tree2.insert("night");
	
	cout<<endl; 

	cout<<"inorder traversal ..... "<<endl; 
	tree2.inOrderTraversal(); 
	cout<<"preorder traversal ..... "<<endl; 
	tree2.preOrderTraversal(); 
	cout<<"postorder traversal ..... "<<endl; 
	tree2.postOrderTraversal(); 
	cout<<"tree height is "<< tree2.treeHeight()<<endl; 
	cout<<"tree node count is "<< tree2.treeNodeCount()<<endl; 
	cout<<"tree leave count is "<< tree2.treeLeaveCount()<<endl; 

	cout<<endl; 

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
				cin>> word; 
				tree2.remove(word); 
				tree2.inOrderTraversal(); 
				cout<<endl; 
				break; 
		case 's': 
		case 'S':
				cout<<"What to be searched for? "; 
				cin>>word; 
				if(tree2.find(word))
					cout<<"found "<< word <<" in the tree "<<endl; 
				else 
					cout<<"failed to find " <<word<<" in the tree "<<endl; 
		default: 
				break;
		}
		if (tag2 == 'q' || tag2 == 'Q')
			break; 
	}
	/**********************************************************************
	 Part C: First define a personType class with three data members 
	 (string name, int ID, and double grade). Second, create binary search
	 tree of personType. Third, practice basic tree operations such as 
	 insertion, deletion, search, etc.
	 ***********************************************************************/
	
	//Write your code here
	
	personType Max = personType("Max");
	Max.setGrade(71);
	Max.setID(554665);
	personType Rick = personType("Rick");
	Rick.setGrade(95);
	Rick.setID(545887);
	personType Sherry = personType("Sherry");
	Sherry.setGrade(84);
	Sherry.setID(565281);

	binarySearchTree<personType> tree3;
	char tag3;
	string word2;
	tree3.insert(Max);
	tree3.insert(Rick);
	tree3.insert(Sherry);
	
	cout<<endl; 

	cout<<"inorder traversal ..... "<<endl; 
	tree3.inOrderTraversal(); 
	cout<<"preorder traversal ..... "<<endl; 
	tree3.preOrderTraversal(); 
	cout<<"postorder traversal ..... "<<endl; 
	tree3.postOrderTraversal(); 
	cout<<"tree height is "<< tree3.treeHeight()<<endl; 
	cout<<"tree node count is "<< tree3.treeNodeCount()<<endl; 
	cout<<"tree leave count is "<< tree3.treeLeaveCount()<<endl; 

	cout<<endl; 

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
				cin>> word2; 
				tree3.remove(word2); 
				tree3.inOrderTraversal(); 
				cout<<endl; 
				break; 
		case 's': 
		case 'S':
				cout<<"What to be searched for? "; 
				cin>>word2; 
				if(tree3.find(word2))
					cout<<"found "<< word2 <<" in the tree "<<endl; 
				else 
					cout<<"failed to find " <<word2<<" in the tree "<<endl; 
		default: 
				break;
		}
		if (tag2 == 'q' || tag2 == 'Q')
			break; 
	}
	/******************************************************************************************
	 Part D: Use binary search tree to sort a list of 10,000 random integers.
	 (1) Use a random number generator to generate a list of 10,000 random integers 
		 and save them into a file "data.txt"
	 (2) Create a binary search tree of int type 
		 and use this tree to sort those integers in "data.txt". Record the time of the sorting. 
	 (3) Use insertionSort, selectionSort, bubbleSort, megerSort, and quickSort to sort
		 the same list of the integers, and record the times of those sorting algorithms
	 (4) Prepare a table to report the time performance of the sorting algorithms. 
	 *******************************************************************************************/
	//Write your code here
	//srand(time(0));
	//ofstream myFile;
	binarySearchTree<int> tree4;
	// This is the random number generator that inserts into text file.
	/*
	int y;
	
	myFile.open("data.txt");
	for(int i = 0; i < 10000; i++)
	{
		y = rand() % 10000;
		myFile << y;
		myFile << endl;
	}
	myFile.close();
	*/
	
	ifstream myFile("data.txt");;
	int y;
	while (myFile >> y)
	{
		tree4.insert(y);
	}
	//complete the program
	return 0; 
}