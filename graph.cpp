#include "graph.h"
#include <iostream>

// The following are used for checking if a graph is acyclic (similar to visited).
// Initially every vertex is BLANK. 
// The vertices on the call stack are RED.
// The vertices we are done with are BLUE
#define BLANK 0
#define RED 1
#define BLUE 2


using namespace std;


Graph::Graph(int V) {
	this->V = V;
	adj = new vector<int>[V];
}

int Graph::getV() {
	return this->V;
}
void Graph::add_edge(int v, int u) {
	this->adj[v].push_back(u);
}
void Graph::add_undir_edge(int v, int u) {
	this->adj[v].push_back(u);
	this->adj[u].push_back(v);
}

vector<int> Graph::get_neighbors(int v) {
	return this->adj[v];
}

void DFS_helper(Graph* g, int v, vector<bool>& visited);
void Graph::DFS(int v) {
	vector<bool> visited(this->V, 0);
	DFS_helper(this, v, visited);
}
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

bool Graph::is_connected() {
	int initial_component = 0;
	vector<int> connected_components = this->find_connected_components();
	for(int component: connected_components)
		if(component != initial_component)
			return false;
	return true;
}

void acyclic_helper(Graph* g, int v, vector<int>& visited, vector<int>& parent, 
	int& cycle_vertex); 
vector<int> Graph::is_acyclic() {
	vector<int> visited(this->V, BLANK);
	vector<int> parent(this->V, -1);
	int cycle_vertex = -1;
	for(int v = 0; v < V; v++) {
		if(visited[v] == BLANK) {
			acyclic_helper(this, v, visited, parent, cycle_vertex);
		}
	}
	vector<int> cycle;
	if(cycle_vertex == -1)
		return cycle;
	
	// The parent array
	// for(int i = 0; i < this->V; i++)
	// 	cout << "p[" << i << "] = " << parent[i] << endl;

	int w = cycle_vertex;
	cycle.push_back(w);
	while(parent[w] != -1) {
		cycle.push_back(parent[w]);
		w = parent[w];
	}
	cycle.push_back(cycle_vertex);

	return cycle;
}


void DFS_helper(Graph* g, int v, vector<bool>& visited) {
	visited[v] = true;
	cout << "Visiting " << v << endl;
	for(int u: g->get_neighbors(v))
		if(!visited[u])
			DFS_helper(g, u, visited);
}
void connnected_components_helper(Graph* g, int v, int& curr_comp, 
	vector<int>& components, vector<bool>& visited) {
	visited[v] = true;
	components[v] = curr_comp;
	for(int u: g->get_neighbors(v))
		if(!visited[u])
			connnected_components_helper(g, u, curr_comp, components, visited);
}
void acyclic_helper(Graph* g, int v, vector<int>& visited, vector<int>& parent, 
	int& cycle_vertex) {
	visited[v] = RED;
	for(int u: g->get_neighbors(v)) {
		if(visited[u] == RED) {
			if(u != parent[v]) {
				// we found a cycle
				cycle_vertex = u;
				return;
			}
		}
		else if(visited[u] == BLANK) {
			parent[u] = v;
			acyclic_helper(g, u, visited, parent, cycle_vertex);
		}
	}
	visited[v] = BLUE;
}