#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
// stores adjacency list items
struct GraphVertix { //this represents a vertix node in the list of adjacencies.
    int val; //the vertix number to whom there is an Edge! for ex u-->val
    int weight; //the weight of the edge from the list representative to this vertex
    GraphVertix* next; //points to the next vertix in the adj list
    GraphVertix* p_to_parallel_edge; //the graphs are Un_directed, implemented in the manner of adj list with parallel edges.
};
// structure to store edges
struct GraphEdge {
    //this struct is used for debugging and easier main checks
    int start_ver, end_ver, weight;
};
class AdjList {
    // insert new nodes into adjacency list from given graph
    GraphVertix* CreateAdjListNode(int value, int weight, GraphVertix* head) {
        GraphVertix* newNode = new GraphVertix;
        newNode->val = value; //the value is the vertix number to which the current list representative points to
        newNode->weight = weight; //the weight of this certain edge
        newNode->next = head; //nodes in the list are inserted by pushing the head
        return newNode;
    }
    int N;  // number of nodes in the graph
public:
    GraphVertix** head;                //adjacency list as array of pointers
    //every vertix in the array is the head to a list of adjacencies from said index
    //the index represents the u and the val represents the v in every u--->v
    // Constructor
  
    AdjList(GraphEdge edges[], int m, int N) { //edges[] is an array of edges to insert into the adjacency list
        // allocate new node
        head = new GraphVertix * [N](); //the head represents an array of graph vertices lists.
        this->N = N;
        // initialize head pointer for all vertices
        for (int i = 0; i < N; ++i) //N number of vertices
            head[i] = nullptr;
        // construct directed graph by adding edges to it
        for (int i = 0; i < m; i++) { //m = number of edges
            int start_ver = edges[i].start_ver;
            int end_ver = edges[i].end_ver;
            int weight = edges[i].weight;
            // insert in the beginning
            GraphVertix* newNode = CreateAdjListNode(end_ver, weight, head[start_ver]);
            //end_ver - to where the edge leads | weight of the edge | head[start_ver] is to access the adj list of a certain vertix.
            // point head pointer to new node
            head[start_ver] = newNode;
        }
    }
    // Destructor
    ~AdjList() {
        for (int i = 0; i < N; i++)
            delete[] head[i];
        delete[] head;
    }

    bool AddEdge(int u, int v, int c); //add edges between u v, if no edge exists there
    bool IsAdjacent(int u, int v); //checks if edge u--->v exists
    bool RemoveEdge(int u, int v); //remove an edge u-->v if it exists
    GraphVertix* GetAdjList(int u)
    { //returns the adjacency list of the vertix u.
        GraphVertix* res =this-> head[u];
        return res;
    }

};

// print all adjacent vertices of given vertex
void display_AdjList(GraphVertix* ptr, int i);
AdjList* MakeEmptyGraph(int n); //n = number of vertices