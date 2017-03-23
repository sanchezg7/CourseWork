#include "Maze.h"
#include "Position.h"
#include <queue>
#include <iostream>
#include <cassert>
#include <iomanip>
#include <cstdlib>

using namespace std;

Maze::Maze(Position s, Position e, int n)
{
	size = n;
	start = s;
	exitpos = e;
	try {
		M = new State *[size];
	}
	catch (bad_alloc) {
		cerr << "Unable to allocate array of state pointers";
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		try {
			M[i] = new State[size];
		}
		catch (bad_alloc) {
			cerr << "Unable to allocate row of state values";
			exit(1);
		}
		for (int j = 0; j < size; j++)
			M[i][j] = WALL;
	}
	try {
		Pred = new Position *[size];
	}
	catch (bad_alloc) {
		cerr << "Unable to allocate array of predecessor positions";
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		try {
			Pred[i] = new Position[size];
		}
		catch (bad_alloc) {
			cerr << "Unable to allocate row of predecessor positions";
			exit(1);
		}
		for (int j = 0; j < size; j++)
			Pred[i][j] = Position(i, j);
	}
}

Maze::~Maze()
{
	for (int i = 0; i < size; ++i) {
		delete[] M[i];
		delete[] Pred[i];
	}
	delete[] M;
	delete[] Pred;
}

State
Maze::getState(const Position &P) const
{
	return M[P.getRow()][P.getCol()];
}

void Maze::display(ostream &out) const
{
	out << '\n';
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++)
		if (Position(i, j) == start)
			cout << 's';
		else if (Position(i, j) == exitpos)
			cout << 'e';
		else if (M[i][j] == WALL)
			out << '*';
		else
			out << ' ';
		out << '\n';
	}
	out << '\n';
}

void Maze::setState(const Position &P, State s)
{
	int i = P.getRow();
	int j = P.getCol();
	assert(1 <= i && i <= size && 1 <= j && j <= size);
	M[i][j] = s;
}

bool Maze::findExitPath() //depth-first search
{
	Position current(start.getRow(), start.getCol()); //set current to starting point

INITIAL:
	//goDown while there is no wall or visited
	if (getState(current.Neighbor(DOWN)) == OPEN)
	{
		//do operation for down
		//mark the current square visited
		setState(current, VISITED);
		
		//add it to the stack
		path.push(current);
		//make neighbor the new current state
		current = current.Neighbor(DOWN);
		if (current == exitpos)
		{
			path.push(current);
			return true; //exit position has been found
		}
		goto INITIAL; //go to next point after next point was assigned
	}
	else {
		//check left operation
		if ((getState(current.Neighbor(LEFT)) == OPEN ))
		{
			
			//similar to options on left
			setState(current, VISITED);
			
			path.push(current); //add to the stack
			//then go to DOWN to re-evaluate for the new spot
			current = current.Neighbor(LEFT);
			if (current == exitpos)
			{
				path.push(current);
				return true; //exit position has been found
			}
			goto INITIAL;
		}
		else {
				//check up direction operation
			if (getState(current.Neighbor(UP)) == OPEN)
			{
				//set the new current state
				setState(current, VISITED);
				//add to the stack 
				path.push(current);
				current = current.Neighbor(UP);
				if (current == exitpos)
				{
					path.push(current);
					return true; //exit position has been found
				}
				//go to DOWN to re-evaluate the new spot
				goto INITIAL;
			}
			else {
					//checking the right direction
					if (getState(current.Neighbor(RIGHT)) == OPEN)
					{
						setState(current, VISITED);
						path.push(current);
						current = current.Neighbor(RIGHT);
						if (current == exitpos)
						{
							path.push(current);
							return true; //exit position has been found
						}
						goto INITIAL;
					}
					else {
						setState(current, VISITED);
						current = path.top();
						path.pop();	
						goto INITIAL;
					}
				}
			}
		}
	//No other direction is available 
	//check if current point is equal to ending position
	if (current == exitpos)
	{
		path.push(current);
		return true; //exit position has been found
	}
	else {
		return false;
	}


	// Fill in the missing code
	// Returns true if a start-to-exit path has been found
	// and the contents of the path stack from to bottom 
	// to top will be the exit path

}


bool Maze::findShortestPath() //breadth-first search
{

// Fill in the missing code
// Returns true if a start-to-exit path has been found
// and this path will be a shortest possible escape path
// The function will fill in the values of the Pred array,
// which is used to find the shortest path

	queue<Position> q;
	Position current(start.getRow(), start.getCol());

BEGIN:
		for (direction d = DOWN; d != NONE; d++)
		{
			if (getState(current.Neighbor(d)) == OPEN) //if neighbor is open for respective direction
			{
				setState(current.Neighbor(d), VISITED); //change state of the neighbor
				Pred[current.Neighbor(d).getRow()][current.Neighbor(d).getCol()] = current; //make the predecessor of the neighbor be the current position
			
				if(current.Neighbor(d) == exitpos) //if 
				{
					return true; //we assume that we will always have an exit position and it will return true
				}
				else //visited position is not equal to exit, place in queue
				{
					q.push(current.Neighbor(d)); //if open, add to the queue for later
				}
			}
		}
		
		current = q.front();
		q.pop();
	goto BEGIN;
}

void Maze::printExitPath()
{
	if (path.empty())
	{
		return;
	}
	Position hold = path.top();
	path.pop();
	printExitPath();
	cout << hold << endl;
}

void Maze::printShortestPath()
{
	Position P = exitpos;
	while (!(P == start)) {
		path.push(P);
		P = Pred[P.getRow()][P.getCol()];
	}
	path.push(start);

	while (!path.empty()) {
		cout << path.top() << endl;
		path.pop();
	}
}

