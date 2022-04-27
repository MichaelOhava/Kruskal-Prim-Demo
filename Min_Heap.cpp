#include "Min_Heap.h"

//constructor
Min_Heap::Min_Heap(int size){ 
	logic_size = 0;
	physical_size = size;
	Heap = new Node[size];
	assert(Heap);

}

// Empty constructor
Min_Heap::Min_Heap() {
	
	Heap = new Node[1];
	assert(Heap);
	logic_size=0;
}

//This function creats new node for the min heap 
Node Min_Heap::CreateNewNodeMinHeap(int priority, int& vertex_num)
{
	Node NewNode;
	NewNode.vertex= vertex_num;
	NewNode.key = priority;
	return NewNode;
}

//This function is a general swap function to be used between nodes
void Min_Heap::swap(Node& n1, Node& n2)
{//this function is a general swap function to be used between nodes
	std::swap(n1.key, n2.key);//int key
	std::swap(n1.vertex, n2.vertex);//Index in Heap 
	std::swap(n1.Pointer_To_Pos_in_min, n2.Pointer_To_Pos_in_min);//pointers switch Values
	//switch the values of the pointers in weight arr
	n1.Pointer_To_Pos_in_min->Pos_In_Heap = &n1;
	n2.Pointer_To_Pos_in_min->Pos_In_Heap = &n2;
	
}

void Min_Heap::Insert(int key, int& vertex_num)
{//SELF NOTE: if the entire line received from cmd was : f 3 hi
 //to here you only need to send the string "hi" , and the priority 3
 //in this case the letter 'f' stand for inserts no need to send it to this func

	if (logic_size + 1 > physical_size) 
	{
		Heap = new Node[physical_size * 2];
		physical_size = physical_size * 2;
	}
	//if logic_size - 1 is the last cell , we put in the one to the right the new one
	Heap[logic_size] = CreateNewNodeMinHeap(key, vertex_num);
	logic_size++;
	HeapifyUpMinHeap(logic_size - 1); // note: if one of them doesnt need to be moved it wont be
}


void Min_Heap::HeapifyUpMinHeap(int i)
{//checks if certain index needs to go up in heap , in this case if its priority is smaller than its parent
	if (i >= logic_size) //no such item exists in this index , 0 .... size - 1
		return;
	if (i == 0) //root has been reached and it is the max
		return;
	if (Heap[i].key < Heap[p(i)].key)
		swap(Heap[i],Heap[p(i)]);
	HeapifyUpMinHeap(p(i));
}
void Min_Heap::HeapifyDownMinHeap(int i)
{//same as heapifying up , if childern priority is smaller than curr swap
	if (i >= logic_size) //no such item exists in this index , 0 .... size - 1
		return;
	int swapThis = i;
	if (l(i) < logic_size && (Heap[i].key > Heap[l(i)].key)) //if left child exists and and curr smaller than child
		swapThis = l(i);
	if (r(i) < logic_size && (Heap[swapThis].key > Heap[r(i)].key))
		swapThis = r(i);
	if (swapThis != i)
	{
		swap(Heap[i], Heap[swapThis]);
		HeapifyDownMinHeap(swapThis);
	}
}

// This function deletes the minimum node in the heap 
Node  Min_Heap::DeleteMin()
{
	Node min = Heap[0];
	swap(Heap[0], Heap[logic_size - 1]);//SWITCHING M IN WITH THE RIGHT LEAF
	logic_size--;
	HeapifyDownMinHeap(0); //FIXING MIN HEAP FROM ROOT
	HeapifyUpMinHeap(0); //FIXING MIN HEAP FROM ROOT
	return min;
}


//This function decreases key value and fix the min heap 
void Min_Heap::decreaseKey(int index, int new_val) {

	Heap[index].key = new_val;
	HeapifyUpMinHeap(index);
}

//floyd heapo build
void Min_Heap::Floyd_build_heap() {

	for (int i = (logic_size / 2) - 1; i >= 0; i--) {
		HeapifyUpMinHeap(i);
	}
}

//creating Arr for floyd heap built
void Min_Heap::Creat_arr(int Vertex_num) {
	logic_size = Vertex_num;
	physical_size = Vertex_num;
	this->Heap = new Node[Vertex_num];
	assert(this->Heap);
	for (int i = 0; i < Vertex_num; i++)
	{
		this->Heap[i].key = 0;
		this->Heap[i].vertex = i;
		this->Heap[i].Index = i;
		
	}

}

//frees the heap 
void Min_Heap::Free_Heap() {
	delete(Heap);
}