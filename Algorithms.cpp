#include"Algorithms.h"

//checking prim
void print(Min_Heap& H) {
	for (int i = 0; i < 6; i++)
	{
		cout << "Index in heap:" << H.Get_Heap()[i].Index << " Key: " << H.Get_Heap()[i].key << " Vertex: " << H.Get_Heap()[i].vertex << ","
			<< " Add in Weight: " << H.Get_Heap()[i].Pointer_To_Pos_in_min << "," << " Weight pointer val: " << H.Get_Heap()[i].Pointer_To_Pos_in_min->Pos_In_Heap
			<< "," << " My address: " << &H.Get_Heap()[i] << endl;
	}
	cout << "\n";
}

//Prim algorithm
int PRIM_Algorithm(AdjList* G, int Num_Of_Vertex, int V_To_Start) {
	Min_Heap H;
	int res = 0;
	bool* InT = new bool[Num_Of_Vertex];//Dynamic Allo
	assert(InT);
	for (int i = 0; i < Num_Of_Vertex; i++) //inT initialization
		InT[i] = false;
	int* P = new int[Num_Of_Vertex];//Dynamic Allo
	assert(P);
	Weight* Min = new Weight[Num_Of_Vertex];
	assert(Min);
	H.Creat_arr(Num_Of_Vertex);//Weight Min Arr
	Node Curr_U;
	for (int i = 0; i < Num_Of_Vertex; i++)//move to func
	{
		if (i != V_To_Start) {
			H.Get_Heap()[i].key = Min[i].Weight = numeric_limits<int>::max();
			Min[i].Pos_In_Heap = &H.Get_Heap()[i];
			H.Get_Heap()[i].Pointer_To_Pos_in_min = &Min[i];
			P[i] = NIL;
		}
		else {
			H.Get_Heap()[V_To_Start].key = Min[V_To_Start].Weight = 0;
			Min[V_To_Start].Pos_In_Heap = &H.Get_Heap()[V_To_Start];
			H.Get_Heap()[V_To_Start].Pointer_To_Pos_in_min = &Min[V_To_Start];
			P[i] = V_To_Start;
		}
	}
	H.Floyd_build_heap();
	while (!H.IsEmpty())
	{
		Curr_U = H.DeleteMin();
		InT[Curr_U.vertex] = true;
		GraphVertix* U = G->GetAdjList(Curr_U.vertex);
		while (U != nullptr)
		{
			if ((!InT[U->val]) && U->weight < Min[U->val].Weight)
			{
				Min[U->val].Weight = U->weight;
				P[U->val] = Curr_U.vertex;
				H.decreaseKey(Min[U->val].Pos_In_Heap->Index, U->weight);
				
			}
			U = U->next;

		}
	}
	for (int i = 0; i < Num_Of_Vertex; i++)
		res += Min[i].Weight;
	delete[] P;
	delete[]Min;
	delete[]InT;
	return res;
}


//Kruskal algorithm
int KRUSKAL_Algorithm(AdjList* G, int Num_Of_Vertex, GraphEdge* edges_arr, int num_of_edges)
{
	int res_index = 0, res = 0;
	//NOTE: edges_arr is an array containing all of the graph's edges.
	GraphEdge* res_arr = new GraphEdge[Num_Of_Vertex - 1]; //trees contain a number of n - 1 edges
	assert(res_arr);
	DisjointSets UF(Num_Of_Vertex); //creates the DisjointedSet ADT, implemented using an array, dynamically allocated, dtor automatically frees
	//this ctor also preforms MakeSet on each index by number of vertices.
	qsort(edges_arr, num_of_edges, sizeof(GraphEdge), compare_weight);
	//rearrange the edges by weight small to big.

	for (int i = 0; i < num_of_edges; i++)
	{
		int u = UF.Find(edges_arr[i].start_ver);
		int v = UF.Find(edges_arr[i].end_ver);
		if (u != v)
		{
			res_arr[res_index].start_ver = u;
			res_arr[res_index].end_ver = v;
			res_arr[res_index].weight = edges_arr[i].weight;
			res_index++;
			res += edges_arr[i].weight;
			UF.Union(u, v);
		}
	}

	delete[] res_arr;
	return res;
}

//This function is comperator for qsort
int compare_weight(const void* a, const void* b)
{
	GraphEdge* x = (GraphEdge*)a;
	GraphEdge* y = (GraphEdge*)b;
	return (x->weight - y->weight);
}

//This function removes Edge from the graph(if edge dont exist it will return false)
bool RemoveEdgeFromEArr(GraphEdge* edges, int uToRemove, int vToRemove, int edges_num)
{
	for (int i = 0;i < edges_num; i++)
	{
		if ((edges[i].start_ver == uToRemove && edges[i].end_ver == vToRemove) ||
			(edges[i].start_ver == vToRemove && edges[i].end_ver == uToRemove))
		{//Union Find will not address vertices with the same source
			edges[i].end_ver = 0;
			edges[i].start_ver = 0;
			edges[i].weight = 0;
			return true;
		}
	}
	return false;
}

//This function checks recursivly if an vertex has already visited
short int Visit(int v, bool* visited, AdjList* G,short int&vertices_visited)
{
	//static short int vertices_visited = 0;
	GraphVertix* current = G->GetAdjList(v);

	while (current != nullptr)
	{
		if (visited[current->val] == false)
		{
			visited[current->val] = true;
			Visit(current->val, visited, G,vertices_visited);
		}
		current = current->next;
	}
	visited[v] = true; //turns black
	vertices_visited++; //increase vertices visited when done with all of adjacent neighbors of a vertix, like in VISIT of DFS algo.
	return vertices_visited;
}

//This function checks if input graph is connected
bool Is_Graph_Connected(AdjList* G, int n)
{
	short int vertices_visited = 0, vertices_counter=0;
	bool* visited = new bool[n];
	assert(visited);
	for (int i = 0; i < n; i++)
		visited[i] = false;
	vertices_counter = Visit(0, visited, G, vertices_visited) - FIRST_VERTIX; //doesnt matter where you search from if graph is connected
	if (vertices_counter != n)
		return false;
	return true;
}

