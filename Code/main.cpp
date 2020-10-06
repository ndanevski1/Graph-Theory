#include <iostream>
#include <algorithm>
#include "graph.h"

using namespace std;

// tests for undirected graph
Graph* create_undir_graph();
void run_DFS(Graph* g, int v);
void run_BFS(Graph* g, int v);
void print_connected_components(Graph* g);
void acyclic(Graph* g);

// tests for directed graph
Graph* create_dir_graph();
void print_top_sort(Graph* g);
void test_transpose(Graph* g);
void test_scc(Graph* g);
int main() {
	
	// cout << "Testing undirected graph!" << endl;
	// Graph* g_undir = create_undir_graph();
	// run_DFS(g_undir, 2);
	// run_BFS(g_undir, 3);
	// print_connected_components(g_undir);
	// acyclic(g_undir);

	cout << endl << endl << "Testing directed graph!" << endl;
	Graph* g_dir = create_dir_graph();
	acyclic(g_dir);
	print_top_sort(g_dir);
	test_transpose(g_dir);
	test_scc(g_dir);

	return 0;
}

Graph* create_undir_graph() {
	Graph* g = new Graph(8, false);
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
void run_BFS(Graph* g, int v) {
	cout << "Running BFS from " << v << endl;
	g->BFS(v);
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
		if(g->isDirected())
			reverse(cycle.begin(), cycle.end());
		for(int v: cycle)
			cout << v << " ";
	}
	cout << endl;
}

Graph* create_dir_graph() {
	Graph* g = new Graph(6, true);
	g->add_edge(2, 3);
	g->add_edge(1, 2);
	g->add_edge(3, 4);
	g->add_edge(0, 2);
	// the following edge makes the graph directed
	g->add_edge(4, 0);
	g->add_edge(1, 5);
	g->add_edge(0, 1);
	return g;
}

void print_top_sort(Graph* g) {
	vector<int> top_sort = g->topological_sort();
	if(!g->isDirected()) {
		cout << "The graph isn't directed." << endl; 
		return;
	} 
	if (top_sort.size() == 0) {
		cout << "The graph doesn't have a topological sort." << endl; 
		return;
	}
	cout << "Topological sort: ";
	for(int v: top_sort)
			cout << v << " ";
	cout << endl;
}

void test_transpose(Graph* g) {
	cout << "Printing original graph " << endl;
	g->print_graph();
	Graph* g_t = g->getTranspose();
	cout << "Printing transpose graph " << endl;
	g_t->print_graph();
}

void test_scc(Graph* g) {
	vector<int> scc = g->scc();
	for(int i = 0; i < g->getV(); i++)
		cout << i << " is in component " << scc[i] << endl;
}