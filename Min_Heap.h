#ifndef _MIN_HEAP
#include <iostream>
#include <assert.h>
using namespace std;
struct Node;

 struct Weight
{
	int Weight;
	Node* Pos_In_Heap;

};

struct Node
{
	int key;//the priority of said node in heap
	int vertex; //satellite info
	int Index;//index in heap
	Weight* Pointer_To_Pos_in_min;// place in min_arr
};

class Min_Heap
{//this will be used to create the ADT , this class will be used once for the bigs and once for the smalls
 // SELF NOTE: on every insert you need to insert the same thing to both and delete the same thing for  both
 //since this adt is used to organize the SAME NODES
 //basically this class is made of two arrays of the SAME nodes with different functionality
private:
	int logic_size;    //the amount of cells being used
	int physical_size; //the size of the entire dynamic allocation
	//this is accessed only through this class:
	int p(int i) { return (i-1) / 2; };     //the parent priority of a certain node
	int l(int i) { return i * 2; };     //the left child of a certain node
	int r(int i) { return i * 2 + 1; }; //the right child of a certai node
	Node* Heap;
public:
	bool IsEmpty() const { return logic_size == 0; }; //if heaps are empty
	Min_Heap(int size);
	Min_Heap();
	Node* Get_Heap() { return Heap; };
	Node Min() const { return Heap[0]; };
	void Insert(int key, int& value); //calls to insert to min heap
	void HeapifyUpMinHeap(int i);
	void HeapifyDownMinHeap(int i);
	Node DeleteMin();
	void setLogicSize(int size) { this->logic_size = size; };
	//------------------------------
	void swap(Node& n1, Node& n2);
	 void decreaseKey(int i, int new_val);
	 Node CreateNewNodeMinHeap(int priority, int& vertex_num);
	 void Floyd_build_heap();
	 void Creat_arr(int Vertex_num);
	 void Free_Heap();
};
#endif // !_MIN_HEAP



