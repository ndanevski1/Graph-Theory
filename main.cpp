#include <bits/stdc++.h>
#include "graph.h"

using namespace std;

Graph* create_graph();
void run_DFS(Graph* g, int v);
void print_connected_components(Graph* g);
void acyclic(Graph* g);

int main() {
	
	Graph* g = create_graph();
	run_DFS(g, 2);
	print_connected_components(g);
	acyclic(g);

	return 0;
}


Graph* create_graph() {
	Graph* g = new Graph(8);
	g->add_undir_edge(0,1);
	g->add_undir_edge(0,3);
	g->add_undir_edge(0,5);
	g->add_undir_edge(1,2);
	g->add_undir_edge(3,4);
	g->add_undir_edge(4,5);
	return g;
}

void run_DFS(Graph* g, int v) {
	cout << "Running DFS from " << v << endl;
	g->DFS(v);
	cout << endl;
}

void print_connected_components(Graph* g) {
	vector<int> connected_components = g->find_connected_components();
	for(int i = 0; i < g->getV(); i++)
		cout << "Vertex " << i << " is in component " << connected_components[i] << endl;
	cout << endl;
}

void acyclic(Graph* g) {
	vector<int> cycle = g->is_acyclic();
	if(cycle.size() == 0)
		cout << "The graph is acyclic." << endl;
	else {
		cout << "The graph is cyclic. Here is one cycle: ";
		for(int v: cycle)
			cout << v << " ";
	}
	cout << endl;
}