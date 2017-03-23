#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <stack>
#include <iostream>

using namespace std;

//typedef enum {WHITE, GRAY, BLACK} allcolors;
typedef struct Cell 
{
	int id;
	int neighbors[4];
} Cell;

class Graph
{
	public:
		Graph();
		void makeGraph(int maze);
		void makeMaze1();
		void makeMaze2();
		void makeMaze3();
		void setStartEnd(int start, int end);
		void fillInNeighbors(int cell, int a, int b, int c, int d);
		void findPath();
		stack <int> getPath();
		void breadthFirstSearch(int u,int exit);
		void setPath();
		bool canWallFollow(int cell, int offset);
	private:
		int entry;
		int exit;
		Cell mazeCell[17];
		int parent[17];
		//allcolors color[17];//holds the color for each index to mark off when visited
		int color[17];
		queue<int> q;//queue for breadth first search
		stack<int> hold;
};

#endif
