#pragma once
#include "Files_Extract.h"

// To use, enter in properties-> Command Line Arguments: "input_file.txt" "output_file.txt"
// input_file.txt needs to be in folder, or program will exit using assert. output_file.txt will be created from program.
// results will be printed into file only, not on-screen.

int main(int argc,char* argv[]){
	AdjList* G=nullptr;
	GraphEdge* edges = nullptr;
	GraphEdge Sub_arc;
	string input;
	int n, m, file_line_index = 0, kruskal_output,prim_output;//n represent the amount of vertex and m represents the num of ark
	fstream newfile;
	ofstream outputfile;
	newfile.open(argv[1], ios::in); //open a file to perform read operation using file object
	assert(newfile);  //checking whether the file is open
	outputfile.open(argv[2],ios::out); //open a file to perform write operation using file object
	assert(outputfile);  //checking whether the file is open
	Check_num_of_VandA(newfile, n, m);
	G = MakeEmptyGraph(n);
	edges = new GraphEdge[m];
	assert(edges);
	if (Insert_to_graph(newfile, G, n, m, Sub_arc,edges) == false)
	{
		free(G);
		delete[]edges;
		newfile.close();
		exit(1);
	}
	else {
		if(Is_Graph_Connected(G, n)==false )
			outputfile << "The graph is not connected !! " << endl<<"Exiting";
		
		else {
			kruskal_output = KRUSKAL_Algorithm(G, n, edges, m);
			prim_output = PRIM_Algorithm(G, n, 0);
			if (G->RemoveEdge(Sub_arc.start_ver - 1, Sub_arc.end_ver - 1) == true) {
				outputfile << "Kruskal " << kruskal_output << endl;
				outputfile << "Prim " << prim_output << endl;
				RemoveEdgeFromEArr(edges, Sub_arc.start_ver - 1, Sub_arc.end_ver - 1, m);
				if (Is_Graph_Connected(G, n) == false)
					outputfile << "The graph is not connected! " << endl << "You have remove edge that functions as a bridge ,Exiting"<<endl;
				else	outputfile << "Kruskal2 " << KRUSKAL_Algorithm(G, n, edges, m) << endl;
			}
			else outputfile << "Edge to remove isn't exist!!" << endl << "Exiting";
		}
		delete[]edges;
		free(G);
		newfile.close(); //close the file object.
		outputfile.close(); //close the output file object.

	}
	
	
}

