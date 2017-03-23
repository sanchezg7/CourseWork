/*
 * Name.
 * 
 * Description.
 */

#include <iostream>

#include "Edge.h"

// Create new edge
Edge::Edge(int from, int to, int weight)
{
    this->from = from;
    this->to = to;
    this->weight = weight;
}

// Copy edge
Edge::Edge(const Edge& other)
{
    this->from = other.from;
    this->to = other.to;
    this->weight = other.weight;
}

int
Edge::From()
{
    return this->from;
}

int
Edge::To()
{
    return this->to;
}

int
Edge::Weight()
{
    return this->weight;
}

std::ostream& operator<<(std::ostream &strm, const Edge &e) {
    strm << "Edge(" << e.from << ", " << e.to << ", " << e.weight << ")";
    return strm;
}

//////////////////////////////////////////////////////////////////////
// Comparison operators.
//
// (Sort by weight, then by from, then by to.)
//////////////////////////////////////////////////////////////////////

bool operator== (const Edge& e1, const Edge& e2)
{
    return (e1.from == e2.from) && (e1.to == e2.to) && (e1.weight == e2.weight);
}

bool operator<= (const Edge& e1, const Edge& e2)
{
    if (e1.weight == e2.weight) {
        if (e1.from == e2.from) {
            return e1.to <= e2.to;
        } else {
            return e1.from <= e2.from;
        }
    } else {
        return e1.weight <= e2.weight;
    }
}

bool operator>= (const Edge& e1, const Edge& e2)
{
    if (e1.weight == e2.weight) {
        if (e1.from == e2.from) {
            return e1.to >= e2.to;
        } else {
            return e1.from >= e2.from;
        }
    } else {
        return e1.weight >= e2.weight;
    }
}

bool operator< (const Edge& e1, const Edge& e2)
{
    if (e1.weight == e2.weight) {
        if (e1.from == e2.from) {
            return e1.to < e2.to;
        } else {
            return e1.from < e2.from;
        }
    } else {
        return e1.weight < e2.weight;
    }
}

bool operator> (const Edge& e1, const Edge& e2)
{
    if (e1.weight == e2.weight) {
        if (e1.from == e2.from) {
            return e1.to > e2.to;
        } else {
            return e1.from > e2.from;
        }
    } else {
        return e1.weight > e2.weight;
    }
}

/* vim: set et sw=4 ts=4: */