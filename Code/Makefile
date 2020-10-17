SRCS = graph.cpp bfs.cpp dfs.cpp connected_components_undir.cpp acyclic.cpp bipartite.cpp top_sort.cpp strongly_connected_components.cpp weightGraph.cpp main.cpp dijkstra.cpp bellman_ford.cpp floyd_warshall.cpp johnson.cpp
HDRS = graph.h weightGraph.h
OBJS = $(SRCS:.c=.o)
EXE = graph

CXX = g++
CXXFLAGS = -Wall $(CXX) =std=c++11

$(EXE): $(OBJS)
	$(CXX) -o $@ $(OBJS)