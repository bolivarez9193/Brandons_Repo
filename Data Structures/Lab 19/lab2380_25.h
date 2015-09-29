/********************************************************************************************
*  Program Name:		lab2380_25_head.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 2380, Spring 2009
*  Lab 25:				Header file for Lab 25
*						- adding two versions (recursive and iterative) of quick sort method
*  Date:				10/20/2008
*
*  Description: This file contains the prototype of the class arrayListType with 
*  two versions of quick-sort algorithm: the recursive media3QuikSort and 
*  the iterative median3QuickSort. 
* 
*  Search methods include linear search, randomized search, and binary search.
*
*  Simple sorting algorithms of insertion sort, selection sort and bubble sort
*  also included. The recursive and iterative merge sort algorithms are also 
*  included.
*********************************************************************************************/

#ifndef H_ArrayListType
#define H_ArrayListType

#include <iostream>
#include <iomanip>
#include <cassert>
using namespace std; 


template <class Type> 
class arrayListType
{
	//overload insertion operator <<
	ostream& operator<<<>(ostream& os, const arrayListType<Type>& x);
public:
	const arrayListType<Type> & operator=	// overloading assignment operator
				(const arrayListType<Type>&); 
	Type & operator[] (int index) const;	// index operator overloading
	void initializeList();					// initialize the list to an empty list
	bool isEmpty();							// chech whether list is empty
	bool isFull();							// chech whether list is full
	int  length() const;					// read the number of nodes in list
	void destroyList();						// to delete all nodes from the list
	Type front();							// return the first element in the list
	Type back();							// return the last element in the list
	bool search(const Type & searchItem);	// to determine the searchItem is in the list
											// return true if yes or no otherwise
	void insertFirst(const Type & newItem);	// insert the newItem to the beginning of the list
	void insertLast(const Type & newItem);	// insert the newItem to the end of the list
	void deleteItem(const Type & deleteItem); // delete the node containing the input item from the list
	void print();							// print the list  
	
	//simple sorting algorithms
	void insertionSort();					// insertion sorting
	void selectionSort();					// selection sorting
	void bubbleSort();						// bubble sorting
	
	//merge sorting algorithms
	void recursiveMergSort();				// recursive merge sorting
	void iterativeMergeSort();				// interative merge sorting

	//median-three quick sort algorithms
	void recursiveMedian3QuickSort();		// recursive median three quick sort
	void iterativeMedian3QuickSort();		// iterative median three quick sort
	
	// merge sorting auxillary functions
	void mergeList(Type *list, Type *tmpList,				// merger the first half and the second half of list
				   int left, int right, int rightEnd);
	void recursiveMergeSort(Type * inList, Type * tmpList,	//recursive merging sort
							int left, int right);	

	// quick sorting auxillary functions
	Type & median3(Type *list, int left, int right);		//find the median 3 element as pivot
	void recursiveMedian3QuickSort(Type *list, int left, int right);
	void iterativeMedian3QuickSort(Type *list, int left, int right); 
	void bubbleSort(Type *list, int left, int right);
	void swap(Type &x, Type &y);	

	//search algorithms		
	bool binSearch(const Type & );			// binary search 
	bool linearSearch(const Type & );		// linear/sequential search
	bool randomSearch( const Type & );		// random search

	//delete an item from a sorted list
	void sortedDelete(const Type &);		// delete an item from a sorted list

	arrayListType();						// default constructor
	arrayListType(int n);					// another constructor
	arrayListType(const arrayListType<Type>&);// copy constructor 
	~arrayListType();						// the destructor

protected: 
	int count;								// store the number of nodes in the list
	int maxSize;							// the max size of the list
	Type *list;								// pointer for dynamic array

private: 
	void copyList(const arrayListType<Type> & otherList); 
											//copy other list to the invoking list
};

//choose median 3 pivot
template<class Type>
Type & arrayListType<Type>::median3(Type *list, int left, int right)	
{
	int middle; 
	
	middle = (left + right)/2; 
	
	//sort list[left], list[middle], list[right]
	if (list[middle] < list[left])
		swap(list[middle], list[left]); 
	if (list[right] < list[left])
		swap(list[right], list[left]);
	if (list[right] < list[middle])
		swap(list[middle], list[right]); 

	//place the pivot at position right - 1
	swap(list[middle], list[right - 1]); 
	
	return list[right - 1]; 
}

//swap two elements
template<class Type>
void arrayListType<Type>::swap(Type & x, Type & y)
{
	Type tmp; 
	tmp = x;
	x = y; 
	y = tmp; 
}

template<class Type>
void arrayListType<Type>::recursiveMedian3QuickSort(Type *list, int left, int right)
{
	Type pivot; 
	
	//when then list is long, then use quick sort
	if(left + 10 <= right)
	{
		pivot = median3(list, left, right); 
	
		//quick splitting
		int i = left, j = right - 1; 
		for ( ; ; )
		{
			//move i pointer from left to right until found an item bigger than pivot
			while(i<j && list[++i] <= pivot){}
			//move j pointer from right to right until found an item smaller than pivot
			while (i<j && pivot <= list[--j]){}
			if (i<j)
				swap(list[i], list[j]); 
			else 
				break; 
		}
		//move the pivot to the splitting point
		
		swap(list[i], list[right - 1]); 

		//recusively sort the smaller elements
		recursiveMedian3QuickSort(list, left, i - 1); 

		//recusively sort the bigger elements
		recursiveMedian3QuickSort(list, i+1, right); 
	}
	else //if the list is too short, use bubbleSort
	{
		bubbleSort(list, left, right); 
	}
}

template<class Type>
void arrayListType<Type>::recursiveMedian3QuickSort( )
{
	recursiveMedian3QuickSort(list, 0, count - 1); 
}

template<class Type>
void arrayListType<Type>::iterativeMedian3QuickSort(Type *list, int left, int right)
{
	Type pivot;							//store the pivot
	int leftPos, rightPos;				//left and right end pos for each segment
	int i, j;							//loop control vars
	int top;							//stach top pointer
	
	//use an array to hold break point. consider this array as a stack. 
	//the stack bottom holds right most pos, and the stack top holds the left most pos. 
	int *endPoints;					
	endPoints = new int[right - left + 1];		

	top = 1;							//set top to 1
	endPoints[0] = right;				//push right most pos
	endPoints[1] = left;				//push left most pos
	

	while (top > 0)
	{
		leftPos = endPoints[top--];		//pop the left pos of the current segment
		if (leftPos > left)				//increase leftPos by one if it is not the first segment
			leftPos++; 

		rightPos = endPoints[top--];	//pop the right pos of the current segment
		if (rightPos < right )			//decrease right pos by one if it is not the last segment
			rightPos--; 

		//when then list is long (say more 10 elements), then use quick sort
		if(leftPos < rightPos && leftPos + 10  <= rightPos )
		{
			pivot = median3(list, leftPos, rightPos); 
	
			//quick splitting
			i = leftPos, j = rightPos - 1; 
			for ( ; ; )
			{
				//move i pointer from left to right until found an item bigger than pivot
				while(list[++i] <= pivot){}
				//move j pointer from right to right until found an item smaller than pivot
				while (pivot <= list[--j]){}
				if (i<j)
					swap(list[i], list[j]); 
				else 
					break; 
			}
			
			//move the pivot to the splitting point
			swap(list[i], list[rightPos - 1]); 

			//find the break point and shall push two segments onto stack
			//push the ends of the right segment
			endPoints[++top]= rightPos; 
			endPoints[++top]=i; 
			//push the ends of the left segment
			endPoints[++top]=i; 
			endPoints[++top]=leftPos; 
		}
		else if (leftPos < rightPos) //if the list is too short, use bubbleSort
		{
			bubbleSort(list, leftPos, rightPos); 
		}
	}

	delete[] endPoints; 
}

template<class Type>
void arrayListType<Type>::iterativeMedian3QuickSort( )
{

	iterativeMedian3QuickSort(list, 0, count - 1); 
}

// recursive merge sorting
template<class Type>
void arrayListType<Type>::recursiveMergSort()				
{
	Type *tmpList; 
	tmpList = new Type[count];

	recursiveMergeSort(list, tmpList, 0, count-1); 
	
	delete[] tmpList;
}

// merge two sorted lists 
template<class Type>
void arrayListType<Type>:: mergeList(Type *list, Type *tmpList, 
									 int left, int right, int rightEnd)
{
	int leftEnd = right - 1; 
	int i = left;
	int tmpLeft = left; 
	int tmpRight = rightEnd; 
	int number = rightEnd - left + 1; 

	//main loop to merge to tmpList
	while(left <= leftEnd && right <= rightEnd)
	{
		if (list[left]<=list[right])
			tmpList[i++]=list[left++]; 
		else
			tmpList[i++]=list[right++];
	}

	//copy the rest of the left half if any
	while(left <= leftEnd)
		tmpList[i++]=list[left++]; 
	
	//copy the rest if the right half if any
	while(right <= rightEnd)
		tmpList[i++]=list[right++]; 
	
	//copy tmpList to list
	for(i=tmpLeft; i<=tmpRight; i++)
		list[i]=tmpList[i];

}

//RecursiveMergeSortHelper
template<class Type>
void arrayListType<Type>::recursiveMergeSort(Type * list, Type *tmpList,
													 int left, int right)
{
	int middle; 

	if (left < right)
	{
		middle = (left + right)/2; 
		recursiveMergeSort(list, tmpList, left, middle); 
		recursiveMergeSort(list, tmpList, middle + 1, right); 
		mergeList(list, tmpList, left, middle + 1, right); 
	}
}

template<class Type>
void arrayListType<Type>::iterativeMergeSort()
{
	Type *tmpList = new Type[count];		//temp list 
	int dist;								//size of a segment of list for merging
	int i;									//for starting  segement of the list for merging
	int lastEnd = count - 1; 
	
	for (dist = 1; dist < count; dist = 2* dist)
	{
		//merging two segments of dist length for each iteration
		for (i = 0; i<count; i = i + 2*dist)
		{
			//when there is one segment with length dist or shorter left, no merge and break
			if (count - i <= dist) 
				break; 

			//when there are segments of size dist, then emerge them		
			if (i + 2*dist -1 < count)
				mergeList(list, tmpList, i, i + dist, i + 2*dist-1); 
			else //also merge one segment with the rest of the list
				mergeList(list, tmpList, i, i+dist, lastEnd);
		}
	}


	delete[] tmpList; 
}

//overload insertion operator <<
template<class Type>
ostream& operator<<<>(ostream& os, const arrayListType<Type>& x)
{
	int flag = 1; 
	for (int i = 0; i < x.length(); i++)
	{
		os << setw(6)<< x[i] << "  "; 
		if (flag %5 == 0)
			os << endl;
		flag++; 
	}
	return os; 
}

// insertionSort 
template <class Type>
void arrayListType<Type>::insertionSort( )
{
	int i, k; 
	Type tmp;  
	bool tag; 

	//case 1: list is empty or has one element
	if (count == 0 || count == 1)					
	{ 
		return;							//do nothing, list is sorted	
	}
	//case 2: list has at least two elements
	for (k=1; k < count; k++)			//k control insertion of the k-th element
	{
		tmp = list[k]; 
		//tag = false; 
		for (i = k-1; i>=0; i--)	
		{
			if (list[i] <= tmp)			//find the right location for list[k]
			{
				list[i+1] = tmp;		//insert the newItem
				//tag = true; 
				break; 
			}
			else							
			{
				list[i+1] = list[i];	//shift list[i] to right
			}
		}
		if ( i == -1)					//list[k] is the samllest
			list[0] = tmp;				//add list[k] at the first position 
	}
}

//selection sort
template<class Type>
void arrayListType<Type>::selectionSort()
{
	int i, j, minIndex; 
	Type tmp; 

	for (i = 0; i< count - 1; i++)			
	{
		minIndex = i; 
		for (j = i; j< count; j++)		//find the i-th smallest element
		{
			if (list[j] < list[minIndex])
				minIndex = j; 
		}
		
		//swap list[i] and list[minIndex]
		if (i != minIndex)
		{
			tmp = list[i]; 
			list[i] = list[minIndex]; 
			list[minIndex] = tmp; 
		}
	}
}

//Bubble sort
template<class Type>
void arrayListType<Type>::bubbleSort()
{
	int i, j; 
	Type tmp; 
	bool flag; 

	for (i = 0; i< count; i++)			
	{
		flag = false; 	
		for (j = 0; j< count - i - 1; j++)		//bubble the i-th largest element to the right position
		{
			//swap list[j] and list[j+1] if they are out of order
			if (list[j] > list[j+1])
			{
				tmp = list[j]; 
				list[j] = list[j+1]; 
				list[j+1] = tmp;
				flag = true;
			}
		}
		if (!flag)								//if swapping, then the list is sorted
			break; 
	}
}

//Bubble sort
template<class Type>
void arrayListType<Type>::bubbleSort(Type *list, int left, int right)
{
	int i, j, k; 
	Type tmp; 
	bool flag; 
	
	//k=0; 
	for (i = left; i<= right; i++)			
	{
		flag = false; 	
		for (j = right; j > i; j--)				//bubble the i-th largest element to the right position
		{
			//swap list[j] and list[j+1] if they are out of order
			if (list[j] < list[j-1])
			{
				swap(list[j],list[j-1]); 
				flag = true;
			}
		}
		if (!flag)								//if swapping, then the list is sorted
			break; 

		//k++; 
	}
}


// to determine the searchItem is in the list
// return true if yes or no otherwise. Since the list is order, need to 
// do binary search
template <class Type> 
bool arrayListType<Type>::binSearch(const Type & searchItem)
{
	assert(!isEmpty());							// make sure the list is not empty
		
	int cnt = 0;								//count the number of comparisons
	bool found = false;							//flag for founding status
	int beg, end, middle;						//three vars for binary search
	beg = 0; 
	end = count - 1; 
	
	while (!found && beg <= end)
	{
		cnt++; 

		middle = (beg + end)/2; 
		
		if (list[middle] == searchItem)			//case 1: found at middle
		{
			found = true; 
			break; 
		}
		else if (list[middle] > searchItem)		//case 2: search in the left half
		{
			end = middle - 1; 
		}
		else									//case 3; search in the right half
		{
			beg = middle + 1; 
		}
	}

	if (found) 
		cout<<"Wow, found "<< searchItem <<" with " << cnt <<" many comparisons."<<endl; 
	else
		cout<<"Wow, failed to "<< searchItem <<" with " << cnt <<" many comparisons."<<endl; 
	
	return found; 
}

// random search to determine the searchItem is in the list
// return true if yes or no otherwise
template <class Type> 
bool arrayListType<Type>::randomSearch(const Type & searchItem)
{
	assert(!isEmpty());			// make sure the list is not empty
	
	int cnt=0;					//to record the number of comparisons
	bool found = false;			//flag for founding status
	unsigned int seed; 

	//get a random seed and set the seed
	cout<<"Enter a random seed => "; 
	cin>>seed; 
	srand(seed);				

	int i = rand()%(count+1);   //get the first random position
	
	while (!found)
	{ 
		cnt++; 
		if (list[i] == searchItem)
			found = true;		//find the searchItem
		else					//otherwise move to the next node
			i = rand()%(count+1); 
	}
	
	if (found) 
		cout<<"Wow, found "<< searchItem <<" with " << cnt <<" many comparisons."<<endl; 
	else
		cout<<"Wow, failed to "<< searchItem <<" with " << cnt <<" many comparisons."<<endl; 
	
	return found; 
}

// random search to determine the searchItem is in the list
// return true if yes or no otherwise
template <class Type> 
bool arrayListType<Type>::linearSearch(const Type & searchItem)
{
	assert(!isEmpty());			// make sure the list is not empty
	
	int cnt=0;					//to record the number of comparisons
	bool found = false;			//flag for founding status
	
	int i = 0;					//point to first
	while (!found && i < count)
	{
		cnt++; 
		if (list[i] == searchItem)
			found = true;		//find the searchItem
		else					//otherwise move to the next node
			i++; 
	}
	
	if (found) 
		cout<<"Wow, found "<< searchItem <<" with " << cnt <<" many comparisons."<<endl; 
	else
		cout<<"Wow, failed to "<< searchItem <<" with " << cnt <<" many comparisons."<<endl; 
	
	return found; 
}

// delete the node containing the input item from the list	
template <class Type>
void arrayListType<Type>::sortedDelete(const Type & deleteItem)
{
	//first use binary search to find the node
	bool found = false;			//flag for founding status
	int beg, end, middle;		//three vars for binary search
	beg = 0; 
	end = count - 1; 
	
	while (!found && beg <= end)
	{
		middle = (beg + end)/2; 
		
		if (list[middle] == deleteItem)		//case 1: found at middle
		{
			found = true; 
			break; 
		}
		else if (list[middle] > deleteItem)	//case 2: search in the left half
		{
			end = middle - 1; 
		}
		else								//case 3; search in the right half
		{
			beg = middle + 1; 
		}
	}
}

// Overload  array index operator []
template <class Type>
Type& arrayListType<Type>::operator[](int index)const
{
	assert(0<= index && index < count);		//check the range of the index
	return list[index];
}

// print the list
template <class Type>
void arrayListType<Type>::print( )
{
	int flag = 1; 
	for (int i = 0; i < count; i++)
	{
		cout << list[i] << "  "; 
		if (flag %5 == 0)
			cout << endl;
		flag++; 
	}
}

// initialize the list to an empty list
template <class Type> 
void arrayListType<Type> :: initializeList()
{
	count = 0; 								//destroy the list to an empty one
	maxSize = 0; 
	list = NULL; 
}

// chech whether list is empty
template <class Type> 
bool arrayListType<Type>::isEmpty()
{
	return count == 0; 
}

// chech whether list is full
template <class Type> 
bool arrayListType<Type>::isFull()
{
	return count == maxSize; 
}

// read the number of nodes in list
template <class Type>
int  arrayListType<Type>::length()const
{
	return count; 
}
	
// to delete all nodes from the list
template <class Type>
void arrayListType<Type>::destroyList()
{
	count = 0;
	maxSize = 0; 
	delete[] list; 
	list = NULL; 
}


// return the first element in the list
template <class Type> 
Type arrayListType<Type>::front()
{
	assert(!isEmpty());			//to make sure the list is not empty
	return list[0]; 
}

// return the last element in the list
template <class Type> 
Type arrayListType<Type>::back()
{
	assert(!isEmpty());			//to make sure the list is not empty
	return list[count-1]; 
}

// to determine the searchItem is in the list
// return true if yes or no otherwise
template <class Type> 
bool arrayListType<Type>::search(const Type & searchItem)
{
	assert(!isEmpty());			// make sure the list is not empty
	
	bool found = false;			//flag for founding status
	
	int i = 0;					//point to first
	while (!found && i < count)
	{
		if (list[i] == searchItem)
			found = true;		//find the searchItem
		else					//otherwise move to the next node
			i++; 
	}
	return found; 
}

// insert the newItem to the beginning of the list
template <class Type>
void arrayListType<Type>::insertFirst(const Type & newItem)
{
	assert(!isFull());				//make sure the list is not full
    
	for (int i = count; i>=0; i--)	//shift all elements one position to the end
	{
		list[i+1] = list[i]; 
	}
	list[0] = newItem;				//add the new item into the first 
	count++;						//increase the index
}


// insert the newItem to the end of the list
template <class Type> 
void arrayListType<Type>::insertLast(const Type & newItem)
{
	assert(!isFull());				//make sure the list is not full
		
	list[count] = newItem; 
	count++; 
}



// delete the node containing the input item from the list	
template <class Type>
void arrayListType<Type>::deleteItem(const Type & deleteItem)
{
	int i; 
	bool found = false; 
	for (i=0; i<count; i++)
	{
		if (list[i] == deleteItem)
		{
			found = true; 
			break; 
		}
	}
	if (!found)						//if not found then stop
		return; 
	else							//found then delete
	{
		if (i==count)
			count--; 
		else						//shift elements 
		{
			for (int j = i+1; j<count; j++)
				list[j-1]=list[j]; 
			count--; 
		}
	}
}

// default constructor	
template <class Type>
arrayListType<Type>::arrayListType()
{
	count = 0; 
	maxSize = 0;
	list = NULL;
}

// another constructor	
template <class Type>
arrayListType<Type>::arrayListType(int n)
{
	assert(n>=0);				//make sure n >= 0
	count = 0; 
	maxSize = n;
	list = new Type[n]; 
}

// copy constructor 
template <class Type>
arrayListType<Type>::arrayListType(const arrayListType<Type>& otherList)
{
	copyList(otherList); 
}

//destructor
template <class Type>
arrayListType<Type>::~arrayListType()
{
	destroyList(); 
}

//copy list
template <class Type>
void arrayListType<Type>::copyList(const arrayListType<Type> & otherList)
{
	count = otherList.count; 
	maxSize = otherList.maxSize; 
	delete[] list; 
	if (otherList.isEmpty())
		list = NULL; 
	else
	{
		list = new Type[maxSize]; 
		for (int i = 0; i<count; i++)
			list[i] = otherList[i];
	}
}

// overloading assignment operator
template <class Type>
const arrayListType<Type>& 
		arrayListType<Type>::operator=(const arrayListType<Type>& otherList)
{
	if (this != & otherList)
	{
		copyList(otherList);
	}
	return *this; 
}



#endif