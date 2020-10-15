#include "weightGraph.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

WeightedGraph::WeightedGraph(int V, bool directed) {
	this->V = V;
	this->directed = directed;
	adj = new vector<vector<int>>[V];
}

int WeightedGraph::getV() {
	return this->V;
}
bool WeightedGraph::isDirected() {
	return this->directed;
}
void WeightedGraph::add_edge(int v, int u, int w) {
    vector<int> new_edge;
    new_edge.push_back(u);
    new_edge.push_back(w);
    this->adj[v].push_back(new_edge);
}
void WeightedGraph::add_undir_edge(int v, int u, int w) {
	this->add_edge(v, u, w);
    this->add_edge(u, v, w);
}

vector<vector<int>> WeightedGraph::get_neighbors(int v) {
	return this->adj[v];
}
void WeightedGraph::print_graph() {
	cout << "Number of vertices = " << this->V << endl;;
	cout << "Directed = " << this->directed << endl;
	cout << "Adjacency list as follows:" << endl;
	for(int v = 0; v < V; v++) { 
		cout << "adj[" << v << "] = {";
		for(vector<int> u_w: this->adj[v])
			cout << "(" << u_w[0] << ", " << u_w[1] << ") ";
		cout << "}" << endl;
	}
}

vector<int> WeightedGraph::dijkstra_bad(int s) {
	vector<int> distance(this->V, 100);
	vector<bool> visited(this->V, false);

	distance[s] = 0;

	for(int i = 0; i < this->getV(); i++) {
		
		// Find the first nonvisited vertex
		int closest_vertex = 0;
		while(visited[closest_vertex])
			closest_vertex++;

		int next_vertex = closest_vertex+1;
		while(next_vertex < this->getV()) {
			if(!visited[next_vertex] && distance[next_vertex] < distance[closest_vertex])
				closest_vertex = next_vertex;
			next_vertex++;
		}

		// cout << closest_vertex << endl;

		if(closest_vertex < this->getV()) {
			visited[closest_vertex] = true;
			for(vector<int> neighbor: this->get_neighbors(closest_vertex)) {
				distance[neighbor[0]] = min(distance[neighbor[0]], distance[closest_vertex] + neighbor[1]);
			}
		}
	}

	return distance;
}