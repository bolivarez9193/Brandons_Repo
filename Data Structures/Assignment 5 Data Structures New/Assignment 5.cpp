///////////////////////////////////////////////////////////////////////////
// Name: Brandon Olivarez
//
// ID#: 20028785
//
// Class: CSCI 3333.02
//
// Professor: Zhixiang Chen
//
// Date: 4/24/2014
//
// Description: For this assignment, we will write a bunch of words
//				to a file and sort them using quicksort. 
//				I have used a random string generator that I coded for 
//				a lab. There was a problem trying to implement time.h
//				so I went ahead and just used a stop watch to record time.
//				The insertion of each element is also taken into 
//				consideration when measuring time.
//
////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "QuickSort.h"
using namespace std; 

static const char alpha[] = 
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";

int lenghthOfAlpha = sizeof(alpha) - 1;

char randomChar()
{
	return alpha[rand() % lenghthOfAlpha];
}

string returnWord()
{
	string word;
	for (unsigned int i = 0; i < 5; i++)
	{
		word += randomChar();
	}
	return word;
}

int main()
{
	/*
	srand(time(0));
	string temp;
	ofstream inFile;
	inFile.open("text1.txt");
	for(int j = 0; j < 10000; j++)
	{
		temp = returnWord();
		inFile << temp << endl;
	}
	inFile.close();
	*/
	string word;
	ifstream myFile;
	quickSortList<string> x(10000);
	myFile.open("text1.txt");
	for(int i = 0; i < 10000; i++)
	{
		getline(myFile, word);
		x.insert(word);
	}
	x.quickSortP1();
	x.print();
	myFile.close();
	return 0;
}