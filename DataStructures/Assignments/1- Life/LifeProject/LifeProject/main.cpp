
/*
 * Name.
 * 
 * Description.
 */

#include <iostream>

#include "Life.h"
#include "utilities.h"


void
print_instructions()
{
    cout << "Welcome to Conway's game of Life." << endl;
    cout << "The model is a rectangular grid in which each cell is either \"alive\" or \"dead\"\n";
    cout << "Each configuration evolves into a new configuration depending rules based on\n";
    cout << "the number of live neighbors\n\n";
    cout << "You will be prompted for the number of rows and columns in your grid\n";
    cout << "and then for the rules for the transformation of one configuration to the next\n\n";
    cout << "After that you will see a visual representation of the initial configuration\n" << endl;
    cout << "and repeatedly asked if you want to see the next generation (enter y for yes, n for no)\n\n";
}


int
main(int argc, char **argv)
{
    int nrows, ncols;

    print_instructions();

    cout << "Enter the number of rows in your grid: ";
    cin >> nrows;
    cout << "Enter the number of columns in your grid: ";
    cin >> ncols;
    cout << endl;

    Life game(nrows,ncols);

    game.initialize(); // Inputs the rules and the list of live cells
    cout << endl;
    game.print();

    while (continue_prompt())
    {
        cout << endl;
        game.update();
        game.print();
    }
    cout << endl;

    return 0;
}

/* vim: set et sw=4 ts=4: */
