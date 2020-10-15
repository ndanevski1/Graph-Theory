#ifndef _weightGraph_h
#define _weightGraph_h

#include <vector>

class WeightedGraph {
    private:
        int V;
        std::vector<std::vector<int>>* adj;
        bool directed;
    public:
        WeightedGraph(int V, bool directed);
        int getV();
        bool isDirected();
        /*
            A directed edge from v to u with weight w.
        */
        void add_edge(int v, int u, int w);
        void add_undir_edge(int v, int u, int w);
        std::vector<std::vector<int>> get_neighbors(int v);
        void print_graph();
        /*
            The following two functions are implementations of Dijkstra's algorithm. 
            The first one using array => O(n^2).
            The second one using a priority queue => O((m+n)logn) = O(mlogn)
        */
        std::vector<int> dijkstra_bad(int s);
        std::vector<int> dijkstra_good(int s);
};


#endif