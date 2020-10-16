#ifndef _weightGraph_h
#define _weightGraph_h

#include <vector>
#include <utility>

/*
    A pair of integers, used for neighboring vertex and cost of getting to there.
*/
typedef std::pair<int, int> iPair;

class WeightedGraph {
    private:
        int V;
        std::vector<iPair>* adj;
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
        void set_weight(int v, int u, int w);
        std::vector<iPair> get_neighbors(int v);
        void print_graph();
        /*
            The following two functions are implementations of Dijkstra's algorithm. 
            The first one using array => O(n^2).
            The second one using a priority queue => O((m+n)logn) = O(mlogn)
        */
        std::vector<int> dijkstra_bad(int s);
        std::vector<int> dijkstra_good(int s);
        std::vector<int> bellman_ford(int s);
        std::vector<std::vector<int>> floyd_warshall();
        std::vector<std::vector<int>> johnson();
};


#endif