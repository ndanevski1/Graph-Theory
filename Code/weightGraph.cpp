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
			for(auto neighbor: this->get_neighbors(closest_vertex)) {
				int v = neighbor.first;
				int w = neighbor.second;
				distance[v] = min(distance[v], distance[closest_vertex] + w);
			}
		}
	}
	return distance;
}


vector<int> WeightedGraph::dijkstra_good(int s) {
	vector<int> distance(this->V, INT_MAX);
	distance[s] = 0;

	// The priority queue will hold a pair (d, v) representing the distance d to the vertex v. 
	// Because d is the first number in the pair, it will sort accordingly
	priority_queue<iPair,vector<iPair>,greater<iPair>> pq;

	pq.push(make_pair(0, s));
	
	while(!pq.empty()) {
		iPair current = pq.top();
		pq.pop();
		int curr_dist = current.first;
		int curr_vertex = current.second;

		// cout << "Current in queue: " << curr_vertex << ", with distance = " << curr_dist << endl;
 

		for(auto neighbor: this->get_neighbors(curr_vertex)) {
			int v = neighbor.first;
			int w = neighbor.second;
			int new_distance = curr_dist + w;
			if(new_distance < distance[v]) {
				distance[v] = new_distance;
				pq.push(make_pair(new_distance, v));
			}
		}
	}
	return distance;
}