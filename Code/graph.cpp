#include "graph.h"
#include <iostream>

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