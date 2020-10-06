#include "graph.h"
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

Graph* Graph::getTranspose() {
    Graph* transpose = new Graph(this->V, true);
    for(int v = 0; v < V; v++) {
		for(int u: this->adj[v])
            transpose->add_edge(u, v);
    }
    return transpose;
}

void scc_firstDFS(Graph* g, int v, vector<bool>& visited, stack<int>& s);
void scc_secondDFS(Graph* g, int v, vector<bool>& visited, vector<int>& components, int& c);
vector<int> Graph::scc() {
    vector<bool> visited(this->V, false);
    stack<int> s;

    // run dfs on the original graph and save the vertices in a stack according to "finish" time
    for(int v = 0; v < V; v++)
        if(!visited[v])
            scc_firstDFS(this, v, visited, s);

    // create the transpose graph and run DFS on it by taking the vertices in order by finish time,
    // i.e. by popping from the stack 
    Graph* g_t = this->getTranspose();
    fill(visited.begin(), visited.end(), false);

    // the following vector is the returning vector
    vector<int> components(this->V,-1);
    // the following integer is the component, we start from zero and increment when we have a new one
    int c = -1;
    while(!s.empty()) {
        int v = s.top();
        s.pop();

        if(!visited[v]) {
            c++;
            scc_secondDFS(g_t, v, visited, components, c);
        }
    }

    return components;
}

void scc_firstDFS(Graph* g, int v, vector<bool>& visited, stack<int>& s) {
    visited[v] = true;
    for(int u: g->get_neighbors(v))
        if(!visited[u])
            scc_firstDFS(g, u, visited, s);
    s.push(v);
}

void scc_secondDFS(Graph* g, int v, vector<bool>& visited, vector<int>& components, int& c) {
    components[v] = c;
    visited[v] = true;
    for(int u: g->get_neighbors(v))
        if(!visited[u])
            scc_secondDFS(g, u, visited, components, c);
}