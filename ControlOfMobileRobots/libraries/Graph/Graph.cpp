#include "Graph.h"




//make linked list
//need to make an array of pointers
//[0] --> 
//[1] --> 4 --> 7 --> 10
//[2] --> 6 --> 12
//[3] --> 1

Graph::Graph()
{
	entry = 1;
	exit = 13;
	for(int i = 0; i < 17; i++)
	{
		//color[i] = WHITE;
		color[i] = 0;//white
	}
}

bool Graph::canWallFollow(int cell, int offset)
{
	int adjCell = cell + offset; //this gives the neighbor to check for
	bool flag = true;
	for(int i = 0; i < 3; ++i)
	{
		if(mazeCell[cell].neighbors[i] == adjCell)
		{
			flag = false;
			break;
		}
	}
	
	return flag;
}

void Graph::makeGraph(int maze)
{
	if(maze == 1)
	{
		makeMaze1();
	} else if(maze == 2)
	{
		makeMaze2();
	} else if(maze == 3)
	{
		makeMaze3();
	}
	
}

void Graph::setStartEnd(int start, int end)
{
	entry = start;
	exit = end;
}

void Graph::makeMaze1()
{
	fillInNeighbors(1,2,5,0,0);
	fillInNeighbors(2,1,3,0,0);
	fillInNeighbors(3,2,4,7,0);
	fillInNeighbors(4,3,8,0,0);
	fillInNeighbors(5,1,9,0,0);
	fillInNeighbors(6,7,10,0,0);
	fillInNeighbors(7,3,6,11,0);
	fillInNeighbors(8,4,12,0,0);
	fillInNeighbors(9,5,10,0,0);
	fillInNeighbors(10,6,9,0,0);
	fillInNeighbors(11,7,15,0,0);
	fillInNeighbors(12,8,0,0,0);
	fillInNeighbors(13,14,0,0,0);
	fillInNeighbors(14,13,15,0,0);
	fillInNeighbors(15,11,14,16,0);
	fillInNeighbors(16,15,0,0,0);
	
}

void Graph::fillInNeighbors(int cell, int a, int b, int c, int d)
{
	mazeCell[cell].id = cell;
	mazeCell[cell].neighbors[0] = a;
	mazeCell[cell].neighbors[1] = b;
	mazeCell[cell].neighbors[2] = c;
	mazeCell[cell].neighbors[3] = d;
}

void Graph::makeMaze2()
{
	fillInNeighbors(1,2,0,0,0);
	fillInNeighbors(2,1,3,6,0);
	fillInNeighbors(3,2,4,0,0);
	fillInNeighbors(4,3,8,0,0);
	fillInNeighbors(5,9,0,0,0);
	fillInNeighbors(6,2,7,10,0);
	fillInNeighbors(7,6,11,0,0);
	fillInNeighbors(8,4,12,0,0);
	fillInNeighbors(9,5,13,0,0);
	fillInNeighbors(10,6,0,0,0);
	fillInNeighbors(11,7,15,0,0);
	fillInNeighbors(12,8,16,0,0);
	fillInNeighbors(13,9,14,0,0);
	fillInNeighbors(14,13,15,0,0);
	fillInNeighbors(15,14,16,0,0);
	fillInNeighbors(16,12,15,0,0);
	
}

void Graph::makeMaze3()
{
	fillInNeighbors(1,2,5,0,0);
	fillInNeighbors(2,1,3,0,0);
	fillInNeighbors(3,2,0,0,0);
	fillInNeighbors(4,8,0,0,0);
	fillInNeighbors(5,1,9,0,0);
	fillInNeighbors(6,7,0,0,0);
	fillInNeighbors(7,8,11,0,0);
	fillInNeighbors(8,4,7,12,0);
	fillInNeighbors(9,5,10,13,0);
	fillInNeighbors(10,9,11,0,0);
	fillInNeighbors(11,7,0,0,0);
	fillInNeighbors(12,8,16,0,0);
	fillInNeighbors(13,9,14,0,0);
	fillInNeighbors(14,13,15,0,0);
	fillInNeighbors(15,14,16,0,0);
	fillInNeighbors(16,12,15,0,0);
	
}

void Graph::findPath()
{
	breadthFirstSearch(entry,exit);
}

void Graph::breadthFirstSearch(int u,int exit)
{
	//color[u] = GRAY;
	color[u] = 1;
	q.push(u);
	while(q.empty() != true)
	{
		u = q.front();
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			if(color[mazeCell[u].neighbors[i]] == 0 && mazeCell[u].neighbors[i] != 0) //to handle values that 0 in the array WHITE
			{
				color[mazeCell[u].neighbors[i]] = 1;//GRAY
				parent[mazeCell[u].neighbors[i]] = u;
				if (mazeCell[u].neighbors[i] == exit)
					return;
				else
					q.push(mazeCell[u].neighbors[i]);
			}
		}
		
	}
}

void Graph::setPath()
{
	int temp = exit;//exit
	//populates the stack from the parent array
	while (!(temp == entry))//start
	{
		hold.push(temp);
		temp = parent[temp];
	}
	
}

stack<int> Graph::getPath()
{
	return hold;
}

