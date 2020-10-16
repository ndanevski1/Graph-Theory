#include "weightGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

WeightedGraph::WeightedGraph(int V, bool directed) {
	this->V = V;
	this->directed = directed;
	adj = new vector<iPair>[V];
}

int WeightedGraph::getV() {
	return this->V;
}
bool WeightedGraph::isDirected() {
	return this->directed;
}
void WeightedGraph::add_edge(int v, int u, int w) {
    this->adj[v].push_back(make_pair(u, w));
}
void WeightedGraph::add_undir_edge(int v, int u, int w) {
	this->add_edge(v, u, w);
    this->add_edge(u, v, w);
}
void WeightedGraph::set_weight(int v, int u, int w) {
	for(int i = 0; i < this->adj[v].size(); i++)
		if(this->adj[v][i].first == u)
			this->adj[v][i].second = w;	
}

vector<iPair> WeightedGraph::get_neighbors(int v) {
	return this->adj[v];
}
void WeightedGraph::print_graph() {
	cout << "Number of vertices = " << this->V << endl;;
	cout << "Directed = " << this->directed << endl;
	cout << "Adjacency list as follows:" << endl;
	for(int v = 0; v < V; v++) { 
		cout << "adj[" << v << "] = {";
		for(auto neighbor: this->adj[v])
			cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
		cout << "}" << endl;
	}
}
