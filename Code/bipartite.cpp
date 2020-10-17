#include "graph.h"
#include <iostream>
#include <vector>

using namespace std;

#define BLUE -1
#define BLANK 0
#define RED 1

bool isBipartite_helper(Graph* g, vector<bool>& visited, vector<int>& color, int u);

bool Graph::isBipartite(vector<int>& blue, vector<int>& red) {
    vector<bool> visited(this->V, false);
    vector<int> color(this->V, BLANK);

    for(int u = 0; u < this->V; u++) {
        if(color[u] == BLANK) {
            color[u] = BLUE;
            if(!isBipartite_helper(this, visited, color, u))
                return false;
        }
    }

    for(int u = 0; u < this->V; u++) {
        if(color[u] == BLUE)
            blue.push_back(u);
        else if(color[u] == RED)
            red.push_back(u);
    }
    return true;
}

bool isBipartite_helper(Graph* g, vector<bool>& visited, vector<int>& color, int u) {
    visited[u] = true;
    for(int v: g->get_neighbors(u)) {
        if(!visited[v]) {
            color[v] = -color[u];
            if(!isBipartite_helper(g, visited, color, v))
                return false;
        }
        else if (color[v] == color[u])
            return false;
    }
    return true;
}