SRCS = graph.cpp bfs.cpp dfs.cpp connected_components_undir.cpp acyclic.cpp top_sort.cpp strongly_connected_components.cpp main.cpp
HDRS = graph.h 
OBJS = $(SRCS:.c=.o)
EXE = graph

CXX = g++
CXXFLAGS = -Wall $(CXX) =std=c++11

$(EXE): $(OBJS)
	$(CXX) -o $@ $(OBJS)