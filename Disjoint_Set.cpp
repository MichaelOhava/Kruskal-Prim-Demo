#include"Disjoint_Set.h"

int DisjointSets::Find(int i)
{
    // find root and make root as parent of i (path
    // compression)
    if (vertices[i].parent != i)
        vertices[i].parent
        = Find(vertices[i].parent);

    return vertices[i].parent;
}

void DisjointSets::Union(int x, int y) {
    int i = Find(x); int j = Find(y); if (i == j) return;
    // Union by size:
    if (vertices[i].size < vertices[j].size) { vertices[i].parent = j, vertices[j].size += vertices[i].size; }
    else { vertices[j].parent = i, vertices[i].size += vertices[j].size; }
}