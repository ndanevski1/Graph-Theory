#include "graph.h"
#include <iostream>

using namespace std;


// The following are used for checking if a graph is acyclic (similar to visited).
// Initially every vertex is UNVISITED. 
// The vertices on the call stack are VISITING.
// The vertices we are done with are VISITED
#define UNVISITED 0
#define VISITING 1
#define VISITED 2

void acyclic_helper(Graph* g, int v, vector<int>& visited, vector<int>& parent, 
	int& cycle_vertex); 
vector<int> Graph::is_acyclic() {
	vector<int> visited(this->V, UNVISITED);
	vector<int> parent(this->V, -1);
	int cycle_vertex = -1;
	for(int v = 0; v < V; v++) {
		if(visited[v] == UNVISITED) {
			acyclic_helper(this, v, visited, parent, cycle_vertex);
		}
	}
	vector<int> cycle;
	if(cycle_vertex == -1)
		return cycle;
	
	// The parent array
	// for(int i = 0; i < this->V; i++)
	// 	cout << "p[" << i << "] = " << parent[i] << endl;
	
	// cout << "CYCLE VERTEX = " << cycle_vertex << endl;

	int w = cycle_vertex;
	cycle.push_back(w);
	while(parent[w] != cycle_vertex) {
		cycle.push_back(parent[w]);
		w = parent[w];
	}
	cycle.push_back(cycle_vertex);

	return cycle;
}


void acyclic_helper(Graph* g, int v, vector<int>& visited, vector<int>& parent, 
	int& cycle_vertex) {
	visited[v] = VISITING;
	for(int u: g->get_neighbors(v)) {
		if(visited[u] == VISITING) {
			if(u != parent[v]) {
				// we found a cycle
				cycle_vertex = u;
				parent[u] = v;
				return;
			}
		}
		else if(visited[u] == UNVISITED) {
			parent[u] = v;
			acyclic_helper(g, u, visited, parent, cycle_vertex);
		}
	}
	visited[v] = VISITED;
}