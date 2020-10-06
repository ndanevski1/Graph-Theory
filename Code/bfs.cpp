#include "graph.h"
#include <iostream>
#include <queue>

using namespace std;

void Graph::BFS(int v) {
	vector<bool> visited(this->V, false);
	queue<int> q;
	q.push(v);
	visited[v] = true;
	while(!q.empty()) {
		int current = q.front();
		q.pop();
		cout << "Visiting " << current << endl;
		for(int u: this->get_neighbors(current)) {
			if(!visited[u]) {
				q.push(u);
				visited[u] = true;
			}
		}
	}
}