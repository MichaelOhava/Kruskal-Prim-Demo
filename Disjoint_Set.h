#pragma once
struct subset {
    int parent; //parent number of this nubmer
    int size;   //size of numbers pointing to this number
};

class DisjointSets {
    subset* vertices;
public:
    // Create an empty union find data structure with N isolated sets.
    DisjointSets(int N) { //this ctor automatically performs MakeSet on every number.
        vertices = new subset[N];
        for (int i = 0; i < N; i++)  MakeSet(i);
    }
    ~DisjointSets() { delete[] vertices; } //clears the struct.

    int Find(int i);
    // Replace sets containing x and y with their union.
    void Union(int x, int y);
    // Are objects x and y in the same set?
    bool connected(int x, int y) { return Find(x) == Find(y); }
    void MakeSet(int i)
    {
        vertices[i].parent = i;
        vertices[i].size = 1;
    }
};