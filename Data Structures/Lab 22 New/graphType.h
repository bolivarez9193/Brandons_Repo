/**********************************************************************************************
*  Program Name:		lab3333_22_head.h
*  Author:				Zhixiang Chen
*  Course:				CSCI/CMPE 3333, Fall 2013
*  Lab 22:				Header file for Lab 22
*  Date:				11/07/2013
*  Description:			This header contains a graph, emphasizing on depth-first search
*  Graph representation: Adjacent list is used. And the input graph is weighted. 
*  Input fiel format:	Raw data of a graph is stored in a file. The first row has 
*						the number of nodes. the next row gives the adjacent list of the first 
*						node, the third gives the adjacent list of the second node, and so on.
***********************************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include <string>

#include "arrayBasedListType.h"
#include "linkedListType.h"
#include "stackType.h"
#include "queueType.h"
#include "heapType.h"

using namespace std; 


#ifndef GRAPH
#define GRAPH

enum statusType{VISITED, UNVISITED, ACTIVE}; 


/************************************************************
 binary min-heap node type
*************************************************************/
struct mhNodeType
{
	double distance;		//distance from the source to the current node
	int label;				//lable fo the current node 
	bool operator<(const mhNodeType & rhs);
	bool operator>(const mhNodeType & rhs);
	bool operator>=(const mhNodeType & rhs);
	bool operator==(const mhNodeType & rhs); //{return distance == rhs.distance;}
	bool operator<=(const mhNodeType & rhs); //{return distance <= rhs.distance;}
	mhNodeType();
	mhNodeType(const mhNodeType & rhs);
};

bool mhNodeType::operator<(const mhNodeType & rhs)
{
	return distance < rhs.distance;
}

bool mhNodeType::operator>(const mhNodeType & rhs)
{
	return distance > rhs.distance;
}
bool mhNodeType:: operator>=(const mhNodeType & rhs)
{
	return distance >= rhs.distance;
}
bool mhNodeType:: operator==(const mhNodeType & rhs)
{
	return distance == rhs.distance;
}
bool mhNodeType:: operator<=(const mhNodeType & rhs)
{
	return distance <= rhs.distance;
}
mhNodeType::mhNodeType()
{
	distance = static_cast<double>(LONG_MAX); 
	label = -1;
}
mhNodeType::mhNodeType(const mhNodeType & rhs)
{
	distance = rhs.distance; 
	label = rhs.label;
}
/************************************************************
 graph node type
*************************************************************/

struct vertexType
{
	friend ostream & operator<<(ostream & os, vertexType n); 
	
	int label;					//the lable of the node
	statusType tag;				//indicate VISITED, ACTIVE, UNVISITED status
	double distance;			//distance from the source to the current node
	int parent;					//the lable of the parent of the current node
	string city;

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
	parent = -1; 
	distance = static_cast<double>(LONG_MAX); 
}
vertexType & vertexType::operator=(vertexType & rhs)
{
	if (this != &rhs)
	{
		label = rhs.label; 
		tag = rhs.tag; 
		distance = rhs.distance; 
		parent = rhs.parent; 
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

/********************************************************************
 graph class, including 
	- depth-first-search
	- breadth-first-search
	- Dijkstra shortest path algorithm: for this algortihm, a binary 
		min-heap is used to increase its performance  
	- Basically, a graph is represented by three data structures: 
		1) a node list of vertexType
		2) a adjacent list of linkedListType<adjVertexType>
		3) a binary min-heap of mhNodeType
*********************************************************************/

class graphType
{
public: 
	void loadGraph(ifstream & inFile); 
	void loadCityGraph(ifstream & inFile);
	void saveGraph(ofstream & outFile); 
	void print();							//in adj list format
	void dfs(int);				//depth-first-search
	void bfs(int);				//breadth-first-search
	void citybfs(int);
	void dShortestPath(int start);	//Dijkstra shortest path algorithm from start
	void printShortestPath(int end); //print the shortest path ending at end
	void printShortestPath(int start, int end); //print shortest path from start to end
	void setHeapSize(int);		//set minHeap size
	void setSize(int);			//set node list and adjacent list sizes
	graphType & operator=(graphType &); 
	int getSize(){return nodes.length();}
	graphType(){};
	graphType (graphType &); 
	~graphType(){};  

private: 
	arrayListType<linkedListType<adjVertexType>> adjList; //store the adjacent list
	arrayListType<vertexType> nodes; 
	binaryHeapType<mhNodeType> heap; 
}; 

/*--------------------------------------------------------------------------
	Dijkstra shortest path algorithm from start to all nodes
--------------------------------------------------------------------------*/
void graphType:: dShortestPath(int start)
{
	int len = nodes.length();			//get the graph size
	setHeapSize(len);					//prepare the heap to len + 1
	int i, j; // deg;
	mhNodeType m, nm; 
	adjVertexType adjNode; 
	bool more; 
	double cost, oldCost, newCost; 

	//process the starting node
	i=start;				
	nodes[i].tag=VISITED; 
	nodes[i].distance = 0; 
	
	//insert nodes adjacent to the starting node into heap
	more = adjList[i].getNext(adjNode); 
	while (more)
	{
		j = adjNode.label;
		cost = adjNode.weight; 
		
		nodes[j].distance = cost; 
		nodes[j].parent = i; 
		nodes[j].tag = ACTIVE; 

		nm.distance = cost; 
		nm.label = j; 
		heap.insert(nm); 
		
		more = adjList[i].getNext(adjNode); 
	}
	
	//Here, an active node may be inserted into heap multi times due to new, shorter distance changes
	while (!heap.isEmpty())
	{
		//remove the min node from the heap and process it
		heap.deleteMin(m); 
		i = m.label; 
		if (nodes[i].tag==VISITED)
			continue;					//skip the rest loop and start next iteration
		
		//here we found next min-node that has not been visited
		nodes[i].tag = VISITED; 
	
		//process all the nodes adjacent to m
		cost = nodes[i].distance; 
		more = adjList[i].getNext(adjNode); 
		while (more)
		{
			j = adjNode.label;
			if (nodes[j].tag != VISITED)
			{
				oldCost = nodes[j].distance; 
				newCost = cost + adjNode.weight; 
				if (newCost < oldCost)
				{
					nodes[j].distance = newCost; 
					nodes[j].parent = i; 
			
					if (nodes[j].tag == UNVISITED)
					{
						nodes[j].tag = ACTIVE; 
					}
					nm.distance = newCost; 
					nm.label = j; 
					heap.insert(nm); 
				}
			}
			more = adjList[i].getNext(adjNode); 
		}
	}
}

/*--------------------------------------------------------------------------
 Print the shortest path ending at end
--------------------------------------------------------------------------*/
void graphType:: printShortestPath(int end)
{
	int i;
	double cost; 
	arrayStackType<int> path;
	//find cost and path
	cost = nodes[end].distance;
	i = end; 
	while (true)
	{
		path.push(i); 
		i = nodes[i].parent; 
		if (i == -1)
			break; 
	}
	cout<<endl<<" the shortest path from " << setw(4) << path.getTop() << " to " << end <<" has distance " 
		<< setw(10)<<setprecision(2)<<fixed<<showpoint<< cost <<" and is ........ " <<endl; 
	while (!path.isEmpty())
	{
		cout<<setw(4)<<path.pop()<< " -----> "<<endl; 
	}
}

/*--------------------------------------------------------------------------
 print shortest path from start to end
--------------------------------------------------------------------------*/
void graphType:: printShortestPath(int start, int end)
{
	int i;  
	double cost; 
	arrayStackType<int> path;
	//find cost and path
	cost = nodes[end].distance;
	i = end; 
	while (true)
	{
		path.push(i); 
		i = nodes[i].parent; 
		if (i == -1)
			break; 
	}
	cout<<endl<<" the shortest path from " << setw(4) << start << " to " << end <<" has distance " 
		<< setw(10)<<setprecision(2)<<fixed<<showpoint<< cost <<" and is ........ " <<endl; 
	while (!path.isEmpty())
	{
		cout<<setw(4)<<path.pop()<< " -----> "<<endl; 
	}
}

/*--------------------------------------------------------------------------
 Set node list and adjacent list sizes
--------------------------------------------------------------------------*/	
void graphType::setSize(int N)
{
	adjList.initializeList(N);
	nodes.initializeList(N); 
}

/*--------------------------------------------------------------------------
 Set the binary min-heap size
--------------------------------------------------------------------------*/	
void graphType:: setHeapSize(int N)
{
	heap.setSize(N+1);			// need +1 for leaving the first list element blank
}

/*--------------------------------------------------------------------------
 This the depth-first-search function. The inpput parameter indicates the 
 starting node.
--------------------------------------------------------------------------*/
void graphType::bfs(int start)
{
	int i, j;
	bool more= false; 
	arrayQueueType<vertexType> queue; 
	vertexType nodeTmp; 
	adjVertexType adjNodeTmp; 

	queue.enQueue(nodes[start]); 
	while(!queue.isEmpty())
	{
		nodeTmp = queue.deQueue();				//pop the top stack node and visit it 
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
				queue.enQueue(nodeTmp);		//push the newly selected node onto stack
			}
			more = adjList[i].getNext(adjNodeTmp);
		}
	}
}

void graphType::citybfs(int start)
{
	int i, j;
	bool more= false; 
	arrayQueueType<vertexType> queue; 
	vertexType nodeTmp; 
	adjVertexType adjNodeTmp; 

	queue.enQueue(nodes[start]); 
	while(!queue.isEmpty())
	{
		nodeTmp = queue.deQueue();				//pop the top stack node and visit it 
		cout<<setw(4)<<nodeTmp.label << setw(4) << nodeTmp.city <<  endl; 
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
				queue.enQueue(nodeTmp);		//push the newly selected node onto stack
			}
			more = adjList[i].getNext(adjNodeTmp);
		}
	}
}
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
		inFile>>v.city;
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
