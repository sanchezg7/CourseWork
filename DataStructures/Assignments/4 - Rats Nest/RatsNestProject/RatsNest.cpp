#include <iostream>
#include "Position.h"
#include "Maze.h"

Maze *
initialize_maze()
{
    Position startpos, exitpos;
    int i, j;

    int maze_size;
    cout << "Input the size of the maze (not including the hedge): ";
    cin >> maze_size;

    cout << "All position indices k must satisfy 1 <= k < = " << (maze_size) << endl << endl;
    cout << "Enter the start position:\n";
    cin >> startpos;

    cout << "Enter the exit position:\n";
    cin >> exitpos;

    Maze *maze = new Maze(startpos, exitpos, maze_size + 2);

    cout << "Please enter column indices for each row\n";

    for (i = 1; i < maze_size + 1; i++) {
        cout << "row " << i << ": ";
        cin >> j;
        while (j > 0){
            maze->setState(Position(i, j), OPEN);
            cin >> j;
        };
    }
    cout << endl;

    if (maze->getState(startpos) != OPEN) {
        cout << "Start position must be open. Opening.";
        maze->setState(startpos, OPEN);
    }
    if (maze->getState(exitpos) != OPEN) {
        cout << "Exit position must be open. Opening.";
        maze->setState(exitpos, OPEN);
    }
    cout << "\nMaze entry complete" << endl;

    return maze;
}


int main()
{

    cout << "RAT IN MAZE" << endl;
    cout << endl;
    cout << "Specify the size of the maze, the open rooms, and" << endl;
    cout << "the starting and exit locations, and this program" << endl;
    cout << "will give paths from the start to the exit." << endl;
    cout << endl;

    Maze *RatHaus = initialize_maze();

    cout << "Your maze:\n";
    RatHaus->display(cout);

    int choice;
    cout << "Enter 1 to use DFS." << endl;
    cout << "Enter 2 to use BFS." << endl;
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
        if (!RatHaus->findExitPath())
            cout << "No path found. Check your maze." << endl;
        else {
            cout << "Path found:" << endl;
            RatHaus->printExitPath();
            cout << "\n\n";
        }
    } else {
        if (!RatHaus->findShortestPath())
            cout << "No path found. Check your maze." << endl;
        else {
            cout << "Path found:" << endl;
            RatHaus->printShortestPath();
        }
    }
    return 0;
}
