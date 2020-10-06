#include "graph.h"
#include <iostream>
#include <stack>

using namespace std;


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