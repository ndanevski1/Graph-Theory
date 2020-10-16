#include "weightGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

vector<vector<int>> WeightedGraph::floyd_warshall() {
	vector<vector<int>> distance;
	// Setting up the base case
	for(int i = 0; i < this->V; i++) {
		// initially set to inf/3 because of overflow
		vector<int> d(this->V, INT_MAX/3);
		distance.push_back(d);
		distance[i][i] = 0;
	}
	// The first edges
	for(int u = 0; u < this->V; u++) {
		for(auto neighbor: this->get_neighbors(u)) {
			int v = neighbor.first;
			int w = neighbor.second;
			distance[u][v] = w;
		}
	}
	// Dynamic programming step
	for(int k = 0; k < this->V; k++) {
		for(int u = 0; u < this->V; u++) {
			for(int v = 0; v < this->V; v++) {
				distance[u][v] = min(distance[u][v], distance[u][k] + distance[k][v]);
			}
		}
	}
	return distance;
}