#include "Adj_list.h"

AdjList* MakeEmptyGraph(int n) //n = number of vertices
{
    AdjList* graph = new AdjList(nullptr, 0, n); //REMEMBER TO FREE THIS POINTER TO AN ADJLIST
    return graph;
}

void display_AdjList(GraphVertix* ptr, int i)
{//debugging func
    cout << i << "'s adjacancies: ";
    while (ptr != nullptr) {
        cout << "(" << i << ", " << ptr->val
            << ") ";
        ptr = ptr->next;
    }
    cout << endl;
}

bool AdjList::AddEdge(int u, int v, int c)
{   // u---->v and the weight is c.
    int start_ver = u;
    int end_ver = v;
    int weight = c;
    // insert in the beginning
    if (IsAdjacent(u, v) == false) { //checks if theres no edge u-->v
        GraphVertix* newNode_u = CreateAdjListNode(end_ver, weight, head[start_ver]); //node representing u-->v SAME WEIGHT
        GraphVertix* newNode_v = CreateAdjListNode(start_ver, weight, head[end_ver]); //node representing v-->u (UNDIRECTED GRAPH)
        newNode_u->p_to_parallel_edge = newNode_v;
        newNode_v->p_to_parallel_edge = newNode_u;
        //end_ver - to where the edge leads | weight of the edge | head[start_ver] is to access the adj list of a certain vertix.
        //point head pointer to new node
        head[start_ver] = newNode_u;
        head[end_ver] = newNode_v;
        return true; //edge was added
    }
    //NOTE : IF THERE IS ALREADY AN EDGE u--->v this func DOESNT ADD ONE
    //question: if an input is received to add another edge to an existing one, exit?
    //answer: if the input is assumed as a simple graph no need to check
    return false; //edge wasnt added

    //NOTE: says so in exercise it can be assumed that the graph is simple!
}



bool AdjList::IsAdjacent(int u, int v) // u--->v
{
    GraphVertix* current = head[u]; //access in the array of lists
    //                              the adj list of vertix u
    while (current != nullptr) {
        if (current->val == v)
            return true; //there is an edge u-->v 
        current = current->next;
    }
    return false; //there is no edge u-->v
}



bool AdjList::RemoveEdge(int u, int v)
{
    bool exists = false;
    GraphVertix* current = head[u]; //access in the array of lists
    //                                 the adj list of vertix u
    if (head[u]->val == v)
    {
        head[u] = head[u]->next;
        exists = true;
        free(current);
    }
    else
        while (current != nullptr) {//THIS LOOP RELEASES ONE OF THE EDGES
            if (current->next != nullptr && current->next->val == v) //stops one before the requested edge
            {
                GraphVertix* temp = current->next;
                current->next = temp->next; //if the val exists, his next is either another edge or nullptr
                free(temp);
                exists = true;
            }
            current = current->next;
        }
    if (exists)
    {
        current = head[v];
        if (head[v]->val == u)
        {
            head[v] = head[v]->next;
            free(current);
            return true;
        }
        else
            while (current != nullptr) {//THIS LOOP RELEASES THE PARALLEL EDGE
                if (current->next != nullptr && current->next->val == u) //stops one before the requested parallel edge
                {
                    GraphVertix* temp = current->next;
                    current->next = temp->next; //if the val exists, his next is either another edge or nullptr
                    free(temp);
                    return true; //edge was removed
                }
                current = current->next;
            }
    }
    return false; //edge doesnt exist therefore wasnt removed.
}