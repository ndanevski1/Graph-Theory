#ifndef _graph_h
#define _graph_h

#include <vector>

class Graph {
private:
	int V;
	std::vector<int>* adj;
	bool directed;
	
public:
	/*
		Basic methods for the graph data structure
	*/
	Graph(int V, bool directed);
	int getV();
	bool isDirected();
	void add_edge(int v, int u);
	void add_undir_edge(int v, int u);
	std::vector<int> get_neighbors(int v);

	/*
		The following functions print a BFS/DFS traversal from an input vertex v.
	*/
	void BFS(int v);
	void DFS(int v);

	/*
		The following function is defined for an undirected graph and returns a
		vector containing the component of each vertex. All the vertices with
		the same value are in the same component.
		Implemented using DFS.
	*/
	std::vector<int> find_connected_components();

	/*
		The following function is defined for an undirected graph and returns 
		whether or not the graph is is connected. Implemented using 
		find_connected_components().
	*/
	bool is_connected();

	/*
		The following function returns an empty vector if the graph is acyclic, 
		and returns a cycle otherwise. Implemented using DFS.
		Another possible implementation to check if the graph is acyclic is to check 
		whether in every connected component, the number of edges is one less than
		the number of vertices.
	*/
	std::vector<int> is_acyclic();

	/*
		The following function returns a topological sort of a DAG. If the graph is
		not a DAG, it return an empty vector.
	*/
	std::vector<int> topological_sort();
};


#endif 