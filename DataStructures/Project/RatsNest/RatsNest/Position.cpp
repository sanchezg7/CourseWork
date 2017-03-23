//-------------Position.cpp---------------//

#include "Position.h"
#include <iostream>
#include <cassert>

using namespace std;

Position Position::Neighbor(const direction &d) const
{
    switch(d) {
        case DOWN:
            return Position(row+1,col);
        case LEFT:
            return Position(row,col-1);
        case UP:
            return Position(row-1,col);
        case RIGHT:
            return Position(row,col+1);
        case NONE:
            assert(0);
    }
}

bool Position::operator==(const Position &other) const
{
    return row == other.row && col == other.col;
}


void Position::display(ostream & out) const
{
    out << '('<< row << ',' << col << ')';
}

void Position::input(istream & in)
{
    cout << "row index: ";
    in >> row;
    cout << "column index: ";
    in >> col;
}

ostream & operator<<(ostream &out, const Position &P)
{
    P.display(out);
    return out;
}

istream & operator>>(istream &in, Position &P)
{
    P.input(in);
    return in;
}

direction operator++(direction & d) // prefix increment (++d)
{
    switch(d) {
        case DOWN: d =  LEFT; break;
        case LEFT: d =  UP; break;
        case UP:   d =  RIGHT; break;
        case RIGHT: d =  NONE; break;
        case NONE: d = NONE;
    }
    return d;
}

direction operator++(direction & d,int) // postfix increment (d++)
{
    direction tmp = d;
    switch(d) {
        case DOWN: d =  LEFT; break;
        case LEFT: d =  UP; break;
        case UP:   d =  RIGHT; break;
        case RIGHT: d =  NONE; break;
        case NONE: d = NONE;

    }
    return tmp;
}
