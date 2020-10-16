#include "weightGraph.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility>

using namespace std;

vector<vector<int>> WeightedGraph::johnson() {
    // The first step of the algorithm is to create a copy of the graph with an 
    // additional vertex that is connected to every existing vertex with weight 0.
    // The additional vertex is with index V (i.e. the (V+1)'st vertex)
    WeightedGraph* new_wg = new WeightedGraph(this->getV() + 1, false);
    for(int u = 0; u < this->getV(); u++) {
        for(auto neighbor: this->get_neighbors(u)) {
            int v = neighbor.first;
            int w = neighbor.second;
            new_wg->add_edge(u,v,w);
        }
    }
    int new_vertex = this->getV();
    for(int v = 0; v < this->getV(); v++)
        new_wg->add_edge(new_vertex, v, 0);
    
    // The next step is to negate the distance from the additional vertex 
    // after running bellman ford
    vector<int> phi = new_wg->bellman_ford(new_vertex);

    // We pop because phi bellman ford will calculate the distance from new_vertex
    // to itself which we don't need
    phi.pop_back();
    cout << endl;
    for(int i = 0; i < phi.size(); i++)
        phi[i] = -phi[i];

    for(int u = 0; u < this->getV(); u++) {
        for(auto neighbor: this->get_neighbors(u)) {
            int v = neighbor.first;
            int w = neighbor.second;
            new_wg->set_weight(u, v, w + phi[v] - phi[u]);
        }
    }

    vector<vector<int>> distances;
    for(int u = 0; u < this->getV(); u++) {
        distances.push_back(new_wg->dijkstra_good(u));
    }
    for(int u = 0; u < this->getV(); u++)
        for(int v = 0; v < this->getV(); v++)
            distances[u][v] -= phi[v] - phi[u];

    return distances;
}