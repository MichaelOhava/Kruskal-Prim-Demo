#define _CRT_SECURE_NO_WARNINGS
#ifndef _FILEEX
#define _FILEEX
#include <fstream>
#include <string>
#include "Algorithms.h"
enum Input_inedxes { ARCSTARTVERTEXINDEX, ARCENDVERTEXINDEX, WEIGHTINDEX };

void Check_num_of_VandA(fstream& file_name, int& n, int& m);
bool Is_number(const std::string& s);
bool Insert_to_graph(fstream& file_name, AdjList* G,int& n, int& m, GraphEdge& Sub_arc, GraphEdge* edges);
bool Check_and_insert_edge(char* str, AdjList* G, fstream& file_name, int& n, GraphEdge* edges);
bool Get_edge_to_remove(char* str, GraphEdge& Sub_arc, fstream& file_name, int& n);
bool Vertex_and_weight_valid_check(int index, char* token, int n);
bool Too_many_edge_or_incorrect_data_check(int index, int limit, char* token);
#endif // !_FILEEX
