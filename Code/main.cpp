#include <iostream>
#include <algorithm>
#include "graph.h"
#include "weightGraph.h"


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
Graph* create_messy_graph();

WeightedGraph* create_wg_graph();
void test_dijkstra_bad(WeightedGraph* wg, int s);
void test_dijkstra_good(WeightedGraph* wg, int s);

int main() {
	
	// cout << "Testing undirected graph!" << endl;
	// Graph* g_undir = create_undir_graph();
	// run_DFS(g_undir, 2);
	// run_BFS(g_undir, 3);
	// print_connected_components(g_undir);
	// acyclic(g_undir);

	// cout << endl << endl << "Testing directed graph!" << endl;
	// Graph* g_dir = create_dir_graph();
	// acyclic(g_dir);
	// print_top_sort(g_dir);
	// test_transpose(g_dir);
	// test_scc(g_dir);

	// Graph* g_messy = create_messy_graph();
	// test_scc(g_messy);
	// Graph* dag_of_scc = g_messy->DAG_of_scc();
	// cout << "Printing the DAG of strongly connected components:" << endl;
	// dag_of_scc->print_graph();
	// acyclic(g_messy);

	WeightedGraph* wg = create_wg_graph();
	// wg->print_graph();
	test_dijkstra_bad(wg, 0);
	test_dijkstra_good(wg, 0);


	return 0;
}

WeightedGraph* create_wg_graph() {
	WeightedGraph* wg = new WeightedGraph(9, false);
	wg->add_undir_edge(0,1,4);
	wg->add_undir_edge(0,7,8);
	wg->add_undir_edge(1,2,8);
	wg->add_undir_edge(1,7,11);
	wg->add_undir_edge(2,3,7);
	wg->add_undir_edge(2,5,4);
	wg->add_undir_edge(3,4,9);
	wg->add_undir_edge(3,5,14);
	wg->add_undir_edge(4,5,10);
	wg->add_undir_edge(5,6,2);
	wg->add_undir_edge(6,7,1);
	wg->add_undir_edge(6,8,6);
	wg->add_undir_edge(7,8,7);
	return wg;
}

void test_dijkstra_bad(WeightedGraph* wg, int s) {
	cout << "Testing slower Dijkstra:" << endl;
	vector<int> distance = wg->dijkstra_bad(s);
	for(int i = 0; i < wg->getV(); i++)
		cout << "Distance from " << s << " to " << i << " is " << distance[i] << endl;
	cout << endl;
}
void test_dijkstra_good(WeightedGraph* wg, int s) {
	cout << "Testing faster Dijkstra:" << endl;
	vector<int> distance = wg->dijkstra_good(s);
	for(int i = 0; i < wg->getV(); i++)
		cout << "Distance from " << s << " to " << i << " is " << distance[i] << endl;
	cout << endl;
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
	cout << "Strongly connected components of the following graph:" << endl;
	g->print_graph();
	cout << endl;
	vector<int> scc = g->scc();
	for(int i = 0; i < g->getV(); i++)
		cout << "Vertex " << i << " is in strongly connected component #" << scc[i] << endl;
	cout << endl;
}

Graph* create_messy_graph() {
	Graph* g = new Graph(10, true);
	// we will have three cycles of 3 vertices, one separate vertex and links between each of these scc
	// this is an example graph shown in class
	// 1st cycle
	g->add_edge(7, 8);
	g->add_edge(8, 9);
	g->add_edge(9, 7);
	// 2nd cycle
	g->add_edge(6, 4);
	g->add_edge(4, 5);
	g->add_edge(5, 6);
	// 3rd cycle
	g->add_edge(3, 1);
	g->add_edge(1, 2);
	g->add_edge(2, 3);
	// the links between them
	g->add_edge(0, 2);
	g->add_edge(2, 8);
	g->add_edge(3, 7);
	g->add_edge(2, 4);
	g->add_edge(8, 6);
	return g;
}