#include "graph.h"
#include <iostream>

using namespace std;

void DFS_helper(Graph* g, int v, vector<bool>& visited);
void Graph::DFS(int v) {
	vector<bool> visited(this->V, 0);
	DFS_helper(this, v, visited);
}

void DFS_helper(Graph* g, int v, vector<bool>& visited) {
	visited[v] = true;
	cout << "Visiting " << v << endl;
	for(int u: g->get_neighbors(v))
		if(!visited[u])
			DFS_helper(g, u, visited);
}