// *****************************************************************
// Author:			Brandon Olivarez
// Class:			CSCI 3333.02, Spring 2014
// Lab 21:			Graph, breadth-first search 
// Date:			4/30/2014
// Comment:			The code here is meant to be revised.
//
//-----------------------------------------------------------------
//
// Description: This program is to implement a generic graph 
//				depth-first search algorithm
// *****************************************************************
#include <iostream>
#include <fstream>
#include <cassert>
#include <string> 
#include <cstdlib>
#include <ctime>
#include "graphType.h"	

using namespace std; 

int main()
{
	/**********************************************************
	 Part A:	Testing graphType class and depth-first-search
				The graph data file is "graphData.txt".
	 **********************************************************/
	ifstream inFile;
	graphType graph; 
	
	//load graph
	inFile.open("graphData.txt"); 
	graph.loadGraph(inFile); 
	inFile.close(); 
	graph.print(); 
	//do bfs
	cout<<" BFS result starting at node 0 ................" <<endl; 
	graph.bfs(0); 

	/******************************************************************************
	 Part B:	In my design, each node contains an integer label. Extend this 
				to include some general info. Say, besides an integer label, each 
				node can store a city name of string type. When you implement 
				the breadth-first-search, you shall display the node labels along 
				with city names. use the data file graphCity.txt to test your design.
	 ******************************************************************************/
	//Write your code here
	ifstream myFile;
	graphType graph2;

	myFile.open("GraphCity.txt");
	graph2.loadCityGraph(myFile);
	myFile.close();

	//graph2.print();
	cout<<" BFS result starting at node 0 ................" <<endl; 
	graph2.citybfs(0);
	//complete the program
	return 0; 
}