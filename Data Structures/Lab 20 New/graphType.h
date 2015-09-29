/**********************************************************************************************
*  Program Name:		lab3333_20_head.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 20:				Header file for Lab 20
*  Date:				11/04/2013
*  Description:			This header contains a graph, emphasizing on depth-first search
*  Graph representation: Adjacent list is used. And the input graph is weighted. 
*  Input fiel format:	Raw data of a graph is stored in a file. The first raw has 
*						the number of nodes. the next row gives the adjacent list of the first 
*						node, the third gives the adjacent list of the second node, and so on.
***********************************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <string>

#include "arrayBasedListType.h"
#include "linkedListType.h"
#include "stackType.h"

using namespace std; 


#ifndef GRAPH
#define GRAPH

enum statusType{VISITED, UNVISITED, ACTIVE}; 

/************************************************************
 graph node type
*************************************************************/

struct vertexType
{
	friend ostream & operator<<(ostream & os, vertexType n); 
	int label;					//the lable of the node
	string city;
	statusType tag;				//indicate VISITED, ACTIVE, UNVISITED status

	bool operator==(vertexType & rhs){return label == rhs.label;}
	vertexType & operator=(vertexType &);
	vertexType(); 
}; 

ostream & operator<<(ostream & os, vertexType n)
{
	os<<setw(4)<<n.label; 
	return os; 
}

vertexType::vertexType()
{
	label = -1; 
	tag=UNVISITED;
}
vertexType & vertexType::operator=(vertexType & rhs)
{
	if (this != &rhs)
	{
		label = rhs.label; 
		tag = rhs.tag; 
	}
	return *this; 
}

/************************************************************
 adjacent list node type
*************************************************************/
struct adjVertexType
{
	friend ostream & operator<<(ostream & os, adjVertexType n); 
	
	int label;					//the lable of the node
	double weight;				//save the edge weight

	bool operator==(adjVertexType & rhs){return label == rhs.label;}
	adjVertexType & operator=(adjVertexType &);
	adjVertexType(); 
}; 

ostream & operator<<(ostream & os, adjVertexType n)
{
	os<<setw(4)<<n.label <<setw(6)<<setprecision(2)<<fixed<<showpoint<<n.weight;  
	return os; 
}

adjVertexType::adjVertexType()
{
	label = -1; 
	weight=0;
}

adjVertexType & adjVertexType::operator=(adjVertexType & rhs)
{
	if (this != &rhs)
	{
		label = rhs.label; 
		weight = rhs.weight; 
	}
	return *this; 
}

/************************************************************
 graph class, including depth-first-search
*************************************************************/

class graphType
{
public: 
	void loadGraph(ifstream & inFile); 
	void loadCityGraph(ifstream & inFile);	// This is new
	void saveGraph(ofstream & outFile); 
	void print();							//in adj list format
	void dfs(int); 
	void citydfs(int);
	void setSize(int); 
	graphType & operator=(graphType &); 

	graphType(){};
	graphType (graphType &); 
	~graphType(){};  

private: 
	arrayListType<linkedListType<adjVertexType>> adjList; //store the adjacent list
	arrayListType<vertexType> nodes; 
}; 

/*--------------------------------------------------------------------------
 This the depth-first-search function. The inpput parameter indicates the 
 starting node.
--------------------------------------------------------------------------*/
void graphType::dfs(int start)
{
	int i, j;
	bool more= false; 
	arrayStackType<vertexType> stack; 
	vertexType nodeTmp; 
	adjVertexType adjNodeTmp; 

	stack.push(nodes[start]); 
	while(!stack.isEmpty())
	{
		nodeTmp = stack.pop();				//pop the top stack node and visit it 
		cout<<nodeTmp<<endl; 
		i = nodeTmp.label;					//set the current node to be visited
		nodes[i].tag = VISITED;				
		more = adjList[i].getNext(adjNodeTmp); //push all unvisited adjacent nodes of the top stack on the stack 
		while (more)
		{
			j = adjNodeTmp.label; 
			if (nodes[j].tag == UNVISITED)
			{
				nodeTmp.label = j;					
				nodes[j].tag = ACTIVE;		//set the newly selected node to be active
				nodeTmp.tag = ACTIVE;		//this setting is not useful for now
				stack.push(nodeTmp);		//push the newly selected node onto stack
			}
			more = adjList[i].getNext(adjNodeTmp);
		}
	}
}

void graphType::citydfs(int start)
{
	int i, j;
	bool more= false; 
	arrayStackType<vertexType> stack; 
	vertexType nodeTmp; 
	adjVertexType adjNodeTmp; 

	stack.push(nodes[start]); 
	while(!stack.isEmpty())
	{
		nodeTmp = stack.pop();				//pop the top stack node and visit it 
		cout<<setw(4)<<nodeTmp.label; 
		i = nodeTmp.label;					//set the current node to be visited
		nodes[i].tag = VISITED;		
		more = adjList[i].getNext(adjNodeTmp); //push all unvisited adjacent nodes of the top stack on the stack 
		cout << setw(4) << nodeTmp.city << endl;
		while (more)
		{
			j = adjNodeTmp.label; 
			if (nodes[j].tag == UNVISITED)
			{
				nodeTmp.label = j;					
				nodes[j].tag = ACTIVE;		//set the newly selected node to be active
				nodeTmp.tag = ACTIVE;		//this setting is not useful for now
				stack.push(nodeTmp);		//push the newly selected node onto stack
			}
			more = adjList[i].getNext(adjNodeTmp);
		}
	}
}
/*---------------------------------------------------------------------------------------------------
intput file fortmat example	 
4								(graph has 4 nodes)
0	2	1 3.5  3 4.6			(node 0 has 2 adjacent nodes 1 and 3 with respective weights 3.5 and 4.6)
1	1	0 2.0  					(node 1 has 1 adjacent node 0 with respective weight 2.0)
2   2	0 4.7  1 5.5			(node 2 has 2 adjacent nodes 0 and 1 with respective weights 4.7 and 5.5)
3   2	2 2.8  1 3.4			(node 3 has 2 adjacent nodes 2 and 1 with respective weights 2.8 and 3.4)
-----------------------------------------------------------------------------------------------------*/
void graphType::loadGraph(ifstream & inFile)
{
	int len, i, j, deg, newLabel;
	double newWeight; 
	vertexType v; 
	adjVertexType newNode; 

	inFile >> len; 
	setSize(len); 
	for (i=0; i<len; i++)
	{
		inFile>>v.label; 
		v.tag = UNVISITED;
		nodes.insertLast(v); 
		inFile>>deg;
		for (j=0; j<deg; j++)
		{
			inFile>>newLabel>>newWeight; 
			newNode.label = newLabel; 
			newNode.weight = newWeight; 
			adjList[i].insertLast(newNode);
		}
		adjList.setCount(); 
	}
}

// This is the load graph that features the city string
void graphType::loadCityGraph(ifstream & inFile)
{
	int len, i, j, deg, newLabel;
	double newWeight; 
	vertexType v; 
	adjVertexType newNode; 

	inFile >> len; 
	setSize(len); 
	for (i=0; i<len; i++)
	{
		inFile>>v.label; 
		v.tag = UNVISITED;
		nodes.insertLast(v);
		inFile>>v.city;
		inFile>>deg;
		for (j=0; j<deg; j++)
		{
			inFile>>newLabel>>newWeight; 
			newNode.label = newLabel; 
			newNode.weight = newWeight; 
			adjList[i].insertLast(newNode);
		}
		adjList.setCount(); 
	}
}
/*------------------------------------------------
 The output file format is the same as that of the 
 input file format
--------------------------------------------------*/
void graphType::saveGraph(ofstream & outFile)
{
	int len, i;
	adjVertexType newNode; 

	len = nodes.length(); 

	for (i=0; i<len; i++)
	{
		outFile<<nodes[i]<<adjList[i]<<endl; 
	}
}

void graphType::print()
{
	int len, i; 
	len = nodes.length(); 
	cout<<setw(4)<<len<<endl; 
	for (i=0; i<len; i++)
	{
		cout <<nodes[i] <<setw(4)<<adjList[i].length();  
		adjList[i].print(); 
		cout<<endl; 
	}
}

void graphType::setSize(int N)
{
	adjList.initializeList(N);
	nodes.initializeList(N); 
}

graphType::graphType (graphType & rhs)
{
	int i, len; 
	if (this != & rhs)
	{
		len = adjList.length(); 
		for (i = 0; i< len; i++) 
		{
			adjList[i].destroyList();
		}
		adjList.destroyList(); 
		nodes.destroyList(); 

		len = rhs.adjList.length(); 
		adjList.initializeList(len); 
		for (i=0; i<len; i++)
			adjList[i] = rhs.adjList[i];
		nodes.initializeList(len); 
	}
}

graphType & graphType:: operator=(graphType & rhs)
{
	int i, len; 
	if (this != & rhs)
	{
		len = adjList.length(); 
		for (i = 0; i< len; i++) 
		{
			adjList[i].destroyList();
		}
		adjList.destroyList(); 
		nodes.destroyList(); 

		len = rhs.adjList.length(); 
		adjList.initializeList(len); 
		for (i=0; i<len; i++)
			adjList[i] = rhs.adjList[i];
		nodes.initializeList(len); 
	}
	return *this; 
}

#endif
