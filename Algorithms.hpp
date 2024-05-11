#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <vector>


namespace ariel {

class Algorithms {
public:
    static bool isConnected(const Graph& graph);

    static std::string shortestPath(const Graph& graph, int start, int end);

    static std::string isContainsCycle(const Graph& graph);

    static std::string isBipartite(const Graph& graph);

    static bool negativeCycle(const Graph& graph);

private:
    static bool hasCycleDFS(const Graph& graph, int vertex, std::vector<int>& color, std::vector<int>& parent, int& cycleStart);
    };

} // namespace ariel

#endif // ALGORITHMS_HPP
