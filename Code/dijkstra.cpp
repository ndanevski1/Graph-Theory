#include "weightGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

vector<int> WeightedGraph::dijkstra_bad(int s) {
	vector<int> distance(this->V, INT_MAX/3);
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
	vector<int> distance(this->V, INT_MAX/3);
	vector<bool> visited(this->V, false);
	distance[s] = 0;

	// The priority queue will hold a pair (d, v) representing the distance d to the vertex v. 
	// Because d is the first number in the pair, the comparator will work as required.
	priority_queue<iPair,vector<iPair>,greater<iPair>> pq;

	pq.push(make_pair(0, s));
	
	while(!pq.empty()) {
		iPair current = pq.top();
		pq.pop();
		int curr_dist = current.first;
		int curr_vertex = current.second;

		visited[curr_vertex] = true;
		// cout << "Current in queue: " << curr_vertex << ", with distance = " << curr_dist << endl;
 
		for(auto neighbor: this->get_neighbors(curr_vertex)) {
			int v = neighbor.first;
			int w = neighbor.second;
			int new_distance = curr_dist + w;
			if(new_distance < distance[v]) {
				distance[v] = new_distance;
				if(!visited[v])
					pq.push(make_pair(new_distance, v));
			}
		}
	}
	return distance;
}