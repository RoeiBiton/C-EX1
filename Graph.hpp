#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {

class Graph {

public:
    Graph();

    void loadGraph(const std::vector<std::vector<int>>& graph);

    void printGraph() const;

    std::vector<std::vector<int>> adjacencyMatrix;
};

} // namespace ariel

#endif // GRAPH_HPP
