#include"Files_Extract.h"

//This function checks if input is legit number!(signed int)
bool Is_number(const std::string & s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return (!std::isdigit(c)&&c!='-'); }) == s.end();
}

//This function checks if number of vertex/arcs is valid
void Check_num_of_VandA(fstream& file_name, int& n, int& m) {
	int file_line_index = 0;
	string input;
	while (file_line_index < 2) {
		getline(file_name, input);
		file_line_index++;
		if (input.length() == 0 || !Is_number(input)||input.c_str()[0]=='-') {
			cout << "Invalid number of vertex/arcs in input!"<<endl<<"Exiting!";
			file_name.close();
			exit(1);
		}
		else if (file_line_index == 1) {//we are now at line 1 of the valid input
			n = atoi(input.c_str());//num of vertex
		}
		else {//we are now at line 2 of the valid input
			m = atoi(input.c_str());//num of arcs
		}

	}
}

//This function creats the graph
bool Insert_to_graph(fstream& file_name, AdjList* G, int& n, int& m, GraphEdge& Sub_arc,GraphEdge* edges) {
	string input,helper;
	bool is_ok = true;
	char* str =nullptr;
	int counter = 0;
	while (getline(file_name, input) && counter < m && is_ok) {//getting the arcs 
		str = const_cast<char*>(input.c_str());
		if(Check_and_insert_edge(str, G,file_name,n, edges)==false)//inserting the values from file
			return false;
		counter++;
	}
	if(input.data()!=nullptr)
	str = const_cast<char*>(input.c_str());//Sub_edge
	getline(file_name, helper);

	if (counter < m || helper.data() == nullptr) {//if there is less than the number of edges written in input
		cout << "You have not entered enough edges" << endl;
		return false;
	}
	if (!Get_edge_to_remove(str, Sub_arc, file_name, n) )
		return false;
	 return true;
}


//This function checks if number of vertex/arcs is valid and afterwards insert the edge to the graph
bool Check_and_insert_edge(char* str, AdjList* G, fstream& file_name,int&n,GraphEdge* edges) {
	static int edges_index = 0;
	char* token;
	string  buffer;
	int i, start_v=0, end_v=0, weight=0;
	token = strtok(str, " ");

	for (i = 0; i < 3 && token != nullptr; i++)//move to function 
	{
		if (Vertex_and_weight_valid_check(i, token, n) == false) return false;
		else {//assignment of the edge values
			if (i == ARCSTARTVERTEXINDEX)
				start_v = atoi(token);
			else if (i == ARCENDVERTEXINDEX)
				end_v = atoi(token);
			else weight = atoi(token);
		}
		token = strtok(NULL, " ");
	}
	if(Too_many_edge_or_incorrect_data_check(i, 3,token)==false)return false;
	edges[edges_index].start_ver = start_v-1;
	edges[edges_index].end_ver = end_v-1;
	edges[edges_index].weight = weight;
	edges_index++;
	G->AddEdge(start_v-1, end_v-1, weight);
	return true;
}

//This function checks if number of vertex/arcs is valid and afterwards gets the edge to remove
bool Get_edge_to_remove(char* str, GraphEdge& Sub_arc, fstream& file_name, int& n) {
	char* token;
	string  buffer;
	int j;
	token = strtok(str, " ");
	for (j = 0; j < 2 && token != nullptr; j++)
	{
		if (Vertex_and_weight_valid_check(j, token, n) == false) return false;
		else {
			if (j == ARCSTARTVERTEXINDEX)
				Sub_arc.start_ver = atoi(token);
			else //if (j == ARCENDVERTEXINDEX)
				Sub_arc.end_ver = atoi(token);
		}
		token = strtok(NULL, " ");
	}

	return Too_many_edge_or_incorrect_data_check(j,2,token);
}


bool Vertex_and_weight_valid_check(int index, char* token,int n) {
	
	string  buffer;
	buffer.assign(token);
	if (!Is_number(buffer)) {//checks if its valid number, if its a char it will return false
		cout << "Invalid number of vertex in input in edge to remove! " << endl << " exiting!";
		return false;
	}
	else if ((index == ARCSTARTVERTEXINDEX || index == ARCENDVERTEXINDEX) && (atoi(token) > n || atoi(token) < 0))
	{//checks if the vertex is grater than num of vertex and if its not negative
		cout << "Invalid number of vertex in input!" << endl << "There is no such vertex, exiting!";
		return false;
	}
	else return true;
}


bool Too_many_edge_or_incorrect_data_check(int index,int limit, char* token) {
	if (token != nullptr || index != limit) {//checks if user entered too many edges , or if user entered not enough/too many values for edge to remove
		cout << "You have entered too many edges / edge to remove values was incorrect!" << endl << "Exiting.";
		return false;
	}
	return true;
}
