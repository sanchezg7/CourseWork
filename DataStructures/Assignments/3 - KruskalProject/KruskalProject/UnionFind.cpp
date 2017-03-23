
/*
 * Name.
 * 
 * Description.
 *
 * $Id: skel.cpp,v 1.4 2004/09/03 04:44:35 bgeiger Exp $
 * Copyright (c) 2004 Benjamin Geiger <copyright@bgeiger.net>
 */

#include <iostream>

#include "UnionFind.h"

using namespace std;

UnionFind::UnionFind(int n)
{
    this->n = n;
    this->parent = new int[this->n];
    this->rank = new int[this->n];

    for (int i = 0; i < this->n; i++) {
        this->parent[i] = i;
        this->rank[i] = 0;
    }
}

UnionFind::UnionFind(const UnionFind &other)
{
    this->n = other.n;
    this->parent = new int[this->n];
    this->rank = new int[this->n];

    for (int i = 0; i < this->n; i++) {
        this->parent[i] = other.parent[i];
        this->rank[i] = other.rank[i];
    }
}

UnionFind::~UnionFind()
{
    delete[] this->parent;
    delete[] this->rank;
}

UnionFind&
UnionFind::operator= (const UnionFind& other)
{
    if (this == &other) {
        return *this;
    }

    if (this->n != other.n) {
        this->n = other.n;

        delete[] this->parent;
        this->parent = new int[this->n];
        delete[] this->rank;
        this->rank = new int[this->n];
    }

    for (int i = 0; i < this->n; i++) {
        this->parent[i] = other.parent[i];
        this->rank[i] = other.rank[i];
    }

    return *this;
}

int
UnionFind::FindSet(int i)
{
    int root = i;
    while (root != this->parent[root]) {
        root = this->parent[root];
    }
    int j = parent[i];
    while (j != root) {
        parent[i] = root;
        i = j;
        j = parent[i];
    }

    return root;
}

void
UnionFind::Union(int i, int j)
{
    int a = this->FindSet(i);
    int b = this->FindSet(j);

    if (this->rank[a] < this->rank[b]) {
        this->parent[a] = b;
    } else if (this->rank[b] < this->rank[a]) {
        this->parent[b] = a;
    } else {
        this->parent[b] = a;
        this->rank[a]++;
    }
}

/* vim: set et sw=4 ts=4: */
