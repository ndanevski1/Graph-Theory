#include "graph.h"
#include <iostream>
#include <stack>

// The following are used for checking if a graph is acyclic (similar to visited).
// Initially every vertex is UNVISITED. 
// The vertices on the call stack are VISITING.
// The vertices we are done with are VISITED
#define UNVISITED 0
#define VISITING 1
#define VISITED 2


using namespace std;


Graph::Graph(int V, bool directed) {
	this->V = V;
	this->directed = directed;
	adj = new vector<int>[V];
}

int Graph::getV() {
	return this->V;
}
bool Graph::isDirected() {
	return this->directed;
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
	
	cout << "CYCLE VERTEX = " << cycle_vertex << endl;

	int w = cycle_vertex;
	cycle.push_back(w);
	while(parent[w] != cycle_vertex) {
		cycle.push_back(parent[w]);
		w = parent[w];
	}
	cycle.push_back(cycle_vertex);

	return cycle;
}

void topological_sort_helper(Graph* g, int v, vector<bool>& visited, stack<int>& s);
vector<int> Graph::topological_sort() {
	vector<int> top_sort;
	// if the graph is not acyclic, return empty vector
	if(this->is_acyclic().size() != 0)
		return top_sort;
	
	vector<bool> visited(this->V, 0);
	stack<int> s;
	for(int v = 0; v < V; v++)
		if(!visited[v])
			topological_sort_helper(this, v, visited, s);
	
	while(!s.empty()) {
		top_sort.push_back(s.top());
		s.pop();
	}
	return top_sort;
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
void topological_sort_helper(Graph* g, int v, vector<bool>& visited, stack<int>& s) {
	visited[v] = true;

	// check all the neighbors of node v and then push it to the stack.
	// this ensures that it comes in the top sort before all of its neighbors
	for(int u: g->get_neighbors(v))
		if(!visited[u])
			topological_sort_helper(g, u, visited, s);

	// in the end push the current node
	s.push(v);
}