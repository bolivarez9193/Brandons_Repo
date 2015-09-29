///////////////////////////////////////////////////////////////////////
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
//				a lab.
//
////////////////////////////////////////////////////////////////////////
#ifndef H_QuickSort
#define H_QuickSort

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std; 


template <class Type> 
class quickSortList
{
private:
	int count;
	int size;
	Type * list;
	
public:
	void insert(const Type & item);
	void print();
	quickSortList(int n);
	~quickSortList();
	void swap(Type& x, Type& y);
	void quickSortP1();
	void quickSortP1(Type * list, int l, int r);
	void quickSortP2();
	void quickSortP2(Type * list, int l, int r);
	void quickSortP3();
	void quickSortP3(Type * list, int l, int r);
};

template<class Type>
void quickSortList<Type>::swap(Type & x, Type & y)
{
	Type z;
	z = x;
	x = y;
	y = z;
}

// Pivot is middle
template<class Type>
void quickSortList<Type>::quickSortP1(Type * list, int l, int r)
{
	
	Type pivot;
	int mid = (l + r) / 2;
	if(l + 10 <= r)
	{
		pivot = list[mid];
		int i = l;
		int j = r - 1; 
		while(i < j)
		{
			while(list[i] <= pivot)
			{
				i++;
			}

			while(list[j] >= pivot)
			{
				j--;
			}

			swap(list[i], list[j]); 
		}
		
		swap(list[i], list[r - 1]); 
		quickSortP1(list, l, i - 1); 
		quickSortP1(list, i+1, r); 
	}
	
}

template<class Type>
void quickSortList<Type>::quickSortP1()
{
	quickSortP1(list, 0, count - 1);
}

// Pivot is between beginning and middle
template<class Type>
void quickSortList<Type>::quickSortP2(Type * list, int l, int r)
{
	Type pivot;
	int mid = (l + r) / 2;
	mid = (mid + l) / 2;
	if(l + 10 <= r)
	{
		pivot = list[mid];
		int i = l;
		int j = r - 1; 
			while(i < j)
			{
				while(list[i] <= pivot)
				{
					i++;
				}

				while(list[j] >= pivot)
				{
					j--;
				}

				swap(list[i], list[j]); 
			}
		
		swap(list[i], list[r - 1]); 
		quickSortP2(list, l, i - 1); 
		quickSortP2(list, i+1, r); 
	}
}

template<class Type>
void quickSortList<Type>::quickSortP2()
{
	quickSortP2(list, 0, count - 1);
}

// Pivot is between middle and end
template<class Type>
void quickSortList<Type>::quickSortP3(Type * list, int l, int r)
{
	Type pivot;
	int mid = (l + r) / 2;
	mid = (mid + r) / 2;
	if(l + 10 <= r)
	{
		pivot = list[mid];
		int i = l;
		int j = r - 1; 
		while(i < j)
		{
			while(list[i] <= pivot)
			{
				i++;
			}

			while(list[j] >= pivot)
			{
				j--;
			}
			
			swap(list[i], list[j]); 
		}
		
		swap(list[i], list[r - 1]); 
		quickSortP3(list, l, i - 1); 
		quickSortP3(list, i+1, r); 
	}
}

template<class Type>
void quickSortList<Type>::quickSortP3()
{
	quickSortP3(list, 0, count - 1);
}

template <class Type>
void quickSortList<Type>::print()
{
	for (int i = 0; i < count; i++)
	{
		cout << list[i] << endl;
	}
}

template <class Type> 
void quickSortList<Type>::insert(const Type & item)
{
	if( count != size)
	{	
		list[count] = item; 
		count++; 
	}
}

template <class Type>
quickSortList<Type>::quickSortList(int n)
{
	if(n >= 0)
	{
		count = 0; 
		size = n;
		list = new Type[n];
	}

}

template <class Type>
quickSortList<Type>::~quickSortList()
{
	count = 0;
	size = 0; 
	delete[] list; 
	list = NULL; 
}

#endif