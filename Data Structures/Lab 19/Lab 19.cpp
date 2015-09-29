// ********************************************************************************
// Author:		Brandon Olivarez
// Class:		CSCI 3333, Spring 2014
// Lab 19:		Quick Sort
// Date:		April 21, 2014
// Comment:		The code here is meant to be revised.
//
//----------------------------------------------------------------------------------
//
// Description: This file contains the prototype of the class arrayListType with 
// two versions of quick-sort algorithm: the recursive one and the iterative one. 
// Simple sorting algorithms of insertion sort, selection sort and bubble sort
// are included. Two versions (recursive and iterative) merge sort algorithms are 
// also included. 
//
// Since we have implemented the array based list, we can choose to add a new set of 
// searching and sorting methods into it:
//	
// Search methods include linear search, randomized search, and binary search.
//
// sorting methods include bubble sort, selection sort, insertion sort, 
// two versions of merge sort (the recrusive one and the iterative one), 
// and two versions of quick sort (the recrusive one and the iterative one).
// 
// Compile and run your program. When everything is fine,
// print your .h and .cpp files and turn them to me or the TA.
// ***********************************************************************************
#include <iostream>
#include <cassert>
#include <string> 
#include <cstdlib>

#include "lab2380_25.h"
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
	arrayListType<int> list(1000);		//create a list of int type
	char tag; 
	
	cout<<"loading the list with random numbers between 0 and 666 ... "<<endl; 

	cout<<"Enter a random seed => ";	//get the random seed
	cin >> seed; 
	srand(seed);						//set the randon seed

	for (int i=0; i <500 ; i++)			//insert 50 random numbers into the list
	{
		num = rand()%501; 
		list.insertLast(num);
	}
	list.print(); 
	cout<<endl; 
	
	//list.insertionSort(); 
	//list.bubbleSort(); 
	//list.selectionSort(); 
	

	cout<<"Want to use recursive quick Sort (r) or iterative quick sort (i) => "; 
	cin>>tag; 
	switch(tag)
	{
	case 'r':
	case 'R':	cout<<"calling recursive quick sort .... "<<endl; 
				list.recursiveMedian3QuickSort();
				break; 
	case 'i':
	case 'I':
				cout<<"calling iterative quick sort ....."<<endl; 
				list.iterativeMedian3QuickSort(); 
				break; 
	default: 
				cout<<"entered a wrong choice"<<endl;
	}

	cout<<"after sorting, the list is ....."<<endl; 
	cout<<list<<endl; 


	/***************************************************************
	 Part B: Try to create a list of strings and practice 
	 both recursive quick sort and the iterative quick sort.
	 ***************************************************************/
	
	//Write your code here
	arrayListType<string> list2(10);
	char tag2;
	list2.insertFirst("hello");
	list2.insertLast("goodbye");
	list2.insertFirst("morning");
	list2.insertLast("night");
	list2.print();
	cout << endl;
	cout<<"Want to use recursive merge Sort (r) or iterative merge sort (i) => "; 
	cin>>tag2; 
	switch(tag2)
	{
	case 'r':
	case 'R':	cout<<"calling recusing merge sort .... "<<endl; 
				list2.recursiveMergSort();
				break; 
	case 'i':
	case 'I':
				cout<<"calling iterative merge sort ....."<<endl; 
				list2.iterativeMergeSort(); 
	default: 
				cout<<"entered a wrong choice"<<endl;
	}

	cout<<"after sorting, the list is ....."<<endl; 
	cout<<list2<<endl; 
	/*****************************************************************************
	 Part C: First define a personType class with three data members 
	 (string name, int ID, and double grade). Second, create a list
	 of personType. Third, both recursive quick sort and the iterative quick sort.
	 *****************************************************************************/
	
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

	arrayListType<personType> list3(5);
	char tag3;
	list3.insertFirst(Max);
	list3.insertLast(Rick);
	list3.insertFirst(Sherry);
	list3.print();

	cout<<"Want to use recursive merge Sort (r) or iterative merge sort (i) => "; 
	cin>>tag3; 
	switch(tag3)
	{
	case 'r':
	case 'R':	cout<<"calling recusing merge sort .... "<<endl; 
				list3.recursiveMergSort();
				break; 
	case 'i':
	case 'I':
				cout<<"calling iterative merge sort ....."<<endl; 
				list3.iterativeMergeSort(); 
	default: 
				cout<<"entered a wrong choice"<<endl;
	}

	cout<<"after sorting, the list is ....."<<endl; 
	cout<<list3<<endl; 

	//complete the program
	return 0; 
}