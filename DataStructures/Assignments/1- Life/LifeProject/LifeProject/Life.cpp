/*
 * Name. Gerardo Sanchez
 *
 * Description. Simulates the game of Life by conway. Assignment 1 Data Structures 
 */

#include <iostream>

#include "Life.h"

using namespace std;

// Constructor
Life::Life(int nrows, int ncols) :
    max_row(nrows), max_col(ncols)
{
    this->grid = this->build_grid();
}

// Destructor
Life::~Life()
{
    this->destroy_grid(this->grid);
}

// Initialize the game (reading from the user)
void
Life::initialize()
{
    int row, col;
    int tmp = 0;

    // TODO: Initialize next_state to all 0 values (all cells die by default).
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			next_state[i][j] = 0; //setting all cells to dead
		}
	}

    cout << "Enter the live neighbor counts (between 0 and 8) ";
    cout << "that will cause a dead cell " << endl;
    cout << "to become alive in the next generation, ";
    cout << "terminating input with -1" << endl << endl;

    // TODO: Read counts from the user and update next_state.
	cin >> tmp;
	while (tmp != -1)
	{
		while (tmp < -1)
		{
			cout << "Enter positive input for number of neighbors";
			cin >> tmp;
		}
		if (tmp != -1)
		{
			for (int j = 0; j <  9; ++j)
			{
				if (tmp == j)
				{
					{
						//cout << "I'm here by next_state dead cells." << endl;
						next_state[0][j] = 1;
					}
				}
			}
		}
		cin >> tmp; //ask for input again 
	}

    cout << "Enter the live neighbor counts (between 0 and 8) ";
    cout << "that will cause a live cell " << endl;
    cout << "to continue living in the next generation, ";
    cout << "terminating input with -1" << endl;
	cin >> tmp;

    // TODO: Read counts from the user and update next_state. For live cells
	while( tmp != -1)
	{

		while (tmp < -1)
		{
			cout << "Enter postive input for number of neighbors";
			cin >> tmp;
		}
		if (tmp != -1)
		{
			for (int j = 0; j < 9; ++j)
			{
				if (tmp == j)
				{
					{
						next_state[1][j] = 1; //set cell to live based on input
					}
				}
			}
		}
		cin >> tmp;
	}
	


    cout << "List the coordinates for living cells." << endl;
    cout << "Terminate the list with the special pair -1 -1" << endl;

    // TODO: Read coordinates from the user, verify their validity,
    // and update the grid.
	cin >> row >> col;
	while(row != -1 || col != -1) {
		if(row >= 1 && row <= max_row)
		{
			if(col >=1 && col <= max_col)
			{
				//cout << "Setting " << row << ", " << col << " to 1";
				grid [row][col] = 1; //set specific coordinates to alive based on coordinate input
			}
			else {
				cout << "Column " << col << "is out of range." << endl;
			 }
		}
		else {
			cout << "Row " << row << " is out of range." << endl;	
		}
	cin >> row >> col;
	}

}

// Print the grid to cout.
void
Life::print()
{
    cout << "\nCurrent Life configuration:\n\n";
    for (int row = 1; row < max_row + 1; ++row)
    {
        for (int col = 1; col < max_col + 1; ++col)
        {
            cout << (grid[row][col] ? '*' : ' ');
        }
        cout << endl;
    }
    cout << endl;
}

// Update the contents of the grid to the next generation.
void
Life::update()
{
    // TODO: Create a new grid.
	int **temp_grid;
	temp_grid = build_grid();

    // TODO: Populate the new grid according to the rules.
	for(int i = 1; i <= max_row; ++i)
	{
		for (int j = 1; j <= max_col; ++j)
		{
			for (int r = 0; r < 9; ++r) //total of 8 rows
			{
				if (grid[i][j] == 0 && neighborCount(i,j) == r) //for dead cells 
				{
					temp_grid [i][j] = next_state[0][r];
				}
				else if (grid [i][j] == 1 && neighborCount(i, j) == r) //for live cells
				{
					temp_grid [i][j] = next_state[1][r];
				}
			}
		}
	}

    // TODO: Update the game with the new configuration.
    // (You can either copy the data back or replace the original grid,
    // but be sure to destroy the grid you no longer need.)
	for(int i = 0; i < max_row + 2; ++i)
	{
		for (int j =0; j < max_col + 2; ++j)
		{
			grid[i][j] = temp_grid[i][j];
		}
	}
	destroy_grid(temp_grid); //reclaim memory from temp grid
}

// Build a new empty grid.
int **Life::build_grid()
{
    int **new_grid;

    // TODO: Create and initialize the new grid.
	new_grid = new int*[max_row + 2];
	for( int i = 0; i < max_row + 2; ++i)
	{
		new_grid[i] = new int[max_col +2];
	}
	
	//initialize each cell to be dead with 0
	for (int i = 0; i < max_row +2; ++i)
	{
		for (int j =0; j < max_col +2; ++j)
		{
			new_grid[i][j] = 0;
		}
	}

	return new_grid;
}

// Destroy the specified grid.
void
Life::destroy_grid(int ** grid)
{
    // TODO: Implement the method.
	for (int i = 0; i < max_row +2; ++i)
	{
		delete [] grid [i];
	}
	delete [] grid;
}

// Count the neighbors of the specified cell.
int
Life::neighborCount(int row, int col)
{
    int count = 0;

    for (int i = row - 1; i <= row+1; ++i)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            count += grid[i][j];
        }
    }

    count -= grid[row][col];
    return count;
}

/* vim: set et sw=4 ts=4: */
