
//roei.biton33@gmail.com
//206400426

#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

namespace ariel {

Graph::Graph(): adjacencyMatrix() {}

    void Graph::loadGraph(const std::vector<std::vector<int>>& graph) {
        // Check if the graph is a square matrix
        if (graph.size() != graph[0].size()) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        // Check if diagonal elements are all zero
        for (size_t i = 0; i < graph.size(); ++i) {
            if (graph[i][i] != 0) {
                throw std::invalid_argument("Invalid graph: Diagonal elements must be zero.");
            }
        }

        // Load the graph from the provided matrix representation
        // and store it in the adjacencyMatrix member variable.
        adjacencyMatrix = graph;
    }



void Graph::printGraph() const {
    // Print the graph's adjacency matrix.
    std::cout << "Graph with " << adjacencyMatrix.size() << " vertices and ";
    int edgeCount = 0;
    for (const auto& row : adjacencyMatrix) {
        for (int value : row) {
            if (value != 0) {
                edgeCount++;
            }
        }
    }
    std::cout << edgeCount << " edges." << std::endl;
}

} // namespace ariel
