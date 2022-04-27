#ifndef _ALGO
#include"Adj_list.h"
#include"Disjoint_Set.h"
#include"Min_Heap.h"
#define NIL -1
#define FIRST_VERTIX 1
#define ALLOCATE 1
#define RELEASE 0

//Both following algorithms return the weight of the result tree.
int PRIM_Algorithm(AdjList* G, int Num_Of_Vertex, int V_To_Start);
int KRUSKAL_Algorithm(AdjList* G, int Num_Of_Vertex, GraphEdge* edges_arr, int num_of_edges);
int compare_weight(const void* a, const void* b);
bool RemoveEdgeFromEArr(GraphEdge* edges, int uToRemove, int vToRemove, int edges_num);
short int Visit(int v, bool* visited, AdjList* G, int& vertices_visited);
bool Is_Graph_Connected(AdjList* G, int n);
#endif // !_ALGO
