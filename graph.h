#ifndef _graph_h
#define _graph_h

#include <vector>

class Graph {
private:
	int V;
	std::vector<int>* adj;
	bool directed;
	
public:
	Graph(int V, bool directed);
	int getV();
	bool isDirected();
	void add_edge(int v, int u);
	void add_undir_edge(int v, int u);
	std::vector<int> get_neighbors(int v);
	// the following functions just print BFS or DFS from the vertex v
	void BFS(int v);
	void DFS(int v);
	// the following function returns a vector containing the component of each 
	// vertex. All the vertices with the same value are in the same component
	// Implemented using DFS
	std::vector<int> find_connected_components();
	// the following function returns whether or not the graph is is connected. 
	// Implemented using DFS
	bool is_connected();
	// the following function returns an empty vector if the graph is acyclic, 
	// and returns one cycle otherwise
	// Implemented using DFS
	// Another implementation to check if the graph is acyclic is to check whether
	// in every connected component, the number of edges is one less than the 
	// number of vertices 
	std::vector<int> is_acyclic();
	// the following function returns a topological sort of a DAG. if the graph is
	// not a DAG, it return an empty vector
	std::vector<int> topological_sort();
};


#endif 