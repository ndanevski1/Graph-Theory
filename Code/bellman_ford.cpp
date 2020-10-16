#include "weightGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

vector<int> WeightedGraph::bellman_ford(int s) {
	vector<int> distance(this->V, INT_MAX);
	distance[s] = 0;
	// Repeat "relaxing" an edge as long as there is a change. Will happen at most V times.
	bool change = true;
	while(change) {
		change = false;
		for(int u = 0; u < this->V; u++) {
			for(auto neighbor: this->get_neighbors(u)) {
				int v = neighbor.first;
				int w = neighbor.second;
				if(distance[v] > distance[u] + w) {
					distance[v] = distance[u] + w;
					change = true;
				}
			}
		}
	}
	return distance;
}
