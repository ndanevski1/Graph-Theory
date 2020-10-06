#include "graph.h"
#include <iostream>

using namespace std;

/*
Defined only for directed graphs.
*/

void connnected_components_helper(Graph* g, int v, int& curr_comp, 
	vector<int>& components, vector<bool>& visited);
vector<int> Graph::find_connected_components() {
	int curr_comp = -1;
	vector<int> components(this->V, -1);
	vector<bool> visited(this->V, 0);

	for(int v = 0; v < V; v++) {
		if(!visited[v]) {
			curr_comp++;
			connnected_components_helper(this, v, curr_comp, components, visited);
		}

	}
	return components;
}

void connnected_components_helper(Graph* g, int v, int& curr_comp, 
	vector<int>& components, vector<bool>& visited) {
	visited[v] = true;
	components[v] = curr_comp;
	for(int u: g->get_neighbors(v))
		if(!visited[u])
			connnected_components_helper(g, u, curr_comp, components, visited);
}

bool Graph::is_connected() {
	int initial_component = 0;
	vector<int> connected_components = this->find_connected_components();
	for(int component: connected_components)
		if(component != initial_component)
			return false;
	return true;
}
