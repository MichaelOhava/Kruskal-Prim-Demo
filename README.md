# Kruskal-Prim-Demo

# Introduction:

  This code is a demonstration of the Kruskal and Prim algorithms to find minimum spanning forests from an un-directed edge-weighted graph.
  The program builds the graph using an input file, then it uses Kruskal to calculate the weight of the graph into an output file.
  Then it uses Prim to calculate the weight of the graph into the same output file (should be the same as the result of Kruskal's algorithm).
  Then the program will remove the edge between the two vertices in the last row of the input file, and will calculate once again the weight
  of the minimum spanning tree of the new graph after an edge has been removed, also using Kruskal.
  
# Few things to note:

  - The program will crash using assert() if no input file exists.
  - The program will stop working if the graph created from the input file is not connected (this program checks connectivity of the graph,
    if the graph is not connected, no minimum spanning tree can be calculated).
  - The program will not work if there's a negative weighted cycle in the graph
  - The program also checks for correct input by the user.
  - The program comes pre-packed with the example input file listed below
  - IMPORTANT: this contains only the .cpp and .h files, meaning to run this program command line arguments are needed!
    In Visual studio: enter in Properties-> command line agruments -> "input_file_name_here" "output_file_name_here"
    OR create an executable , and create a shared library from the .cpp and .h neede in working dir, and run adding arguments.
  
  Basically, follow the ruleset to use the program.
  Also this is not a visual program to help understand to use of kruskal and prim's algorithm, this program is an implementation the algorithms!
  To understand Kruskal and Prim's algorithm read the code fully.

# This program receives a text file as an input, like the following:

6       // number of vertices   <br />
10      // number of edges      <br />
1 2 4   // edge from 1 to 2 weighted 4  <br />
1 3 3   // edge from 1 to 3 weighted 3  <br />
1 4 5   // .... <br />
2 3 5   <br />
2 5 9   <br />
3 4 5    <br />
3 5 6    <br />
3 6 4   <br />
4 6 2   <br />
5 6 6   <br />
1 3     // this last edge is the edge that is removed before calculating kruskal again! read the introduction above to understand more.
