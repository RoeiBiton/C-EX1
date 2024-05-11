
//roei.biton33@gmail.com
//206400426

#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_set>

namespace ariel {

    // Function to check if the graph is connected.
    // We use a breadth-first search (BFS) traversal starting from vertex 0.
    bool Algorithms::isConnected(const Graph& graph) {
        // Initialize a vector to mark visited vertices during BFS traversal
        std::vector<bool> visited(graph.adjacencyMatrix.size(), false);
        // Initialize a queue for BFS traversal
        std::queue<int> q;

        // Start BFS traversal from vertex 0
        q.push(0);
        visited[0] = true;

        // Breadth-First Search to traverse the graph and mark visited vertices
        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();

            // Visit neighbors of the current vertex
            for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
                if (graph.adjacencyMatrix[currentVertex][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }

        // Check if all vertices are visited
        for (bool v : visited) {
            if (!v) {
                return false; // If any vertex is not visited, the graph is not connected
            }
        }

        return true; // If all vertices are visited, the graph is connected
    }

    // Function to find the shortest path between two vertices using the Bellman-Ford algorithm.
    // This algorithm can handle graphs with negative edge weights and detects negative cycles.
    std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
        int numVertices = graph.adjacencyMatrix.size();

        // Initialize distances to all vertices as infinity
        std::vector<int> distance(numVertices, INT_MAX);
        // Initialize parent array to keep track of the shortest path
        std::vector<int> parent(numVertices, -1);

        // Distance to the start vertex is 0
        distance[start] = 0;

        // Bellman-Ford algorithm to find shortest paths
        for (int i = 0; i < numVertices - 1; ++i) {
            for (int u = 0; u < numVertices; ++u) {
                for (int v = 0; v < numVertices; ++v) {
                    if (graph.adjacencyMatrix[u][v] != 0 && distance[u] != INT_MAX && distance[u] + graph.adjacencyMatrix[u][v] < distance[v]) {
                        distance[v] = distance[u] + graph.adjacencyMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative cycles
        if (negativeCycle(graph)) {
            return "Negative cycle detected. Shortest paths not well-defined.";
        }

        // Construct the shortest path string
        if (distance[end] == INT_MAX) {
            return "No path from start to end vertex.";
        }

        std::stringstream ss;
        ss << end;
        for (int v = parent[end]; v != -1; v = parent[v]) {
            ss << ">-" << v;
        }

        std::string shortestPath = ss.str();
        std::reverse(shortestPath.begin(), shortestPath.end()); // Reverse the string
        return shortestPath;
    }

    // Function to check if the graph contains a cycle using depth-first search (DFS).
    // If a back edge is encountered during DFS traversal, a cycle is detected.
    std::string Algorithms::isContainsCycle(const Graph& graph) {
        std::vector<int> color(graph.adjacencyMatrix.size(), 0); // 0 for unvisited, 1 for visiting, 2 for visited
        std::vector<int> parent(graph.adjacencyMatrix.size(), -1); // To store parent of each vertex for cycle detection
        int cycleStart = -1;

        // Depth-First Search (DFS) to detect cycles
        for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
            if (color[i] == 0 && hasCycleDFS(graph, i, color, parent, cycleStart)) {
                // Construct the cycle path
                std::stringstream ss;
                ss << "The cycle is: " << cycleStart;
                for (int v = parent[cycleStart]; v != cycleStart; v = parent[v]) {
                    ss << "->" << v;
                }
                ss << "->" << cycleStart;
                return ss.str();
            }
        }
        return "0"; // No cycle found
    }

    // Depth-First Search (DFS) to detect cycles in the graph
    bool Algorithms::hasCycleDFS(const Graph& graph, int vertex, std::vector<int>& color, std::vector<int>& parent, int& cycleStart) {
        color[vertex] = 1; // Mark as visiting (1 like grey in Algorithm 1 Lectures)
        for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
            if (graph.adjacencyMatrix[vertex][i]) {
                if (color[i] == 1) {
                    cycleStart = i; // Found a back edge, cycle detected
                    parent[cycleStart] = vertex;
                    return true;
                } else if (color[i] == 0) {
                    parent[i] = vertex;
                    if (hasCycleDFS(graph, i, color, parent, cycleStart)) {
                        return true;
                    }
                }
            }
        }
        color[vertex] = 2; // Mark as visited
        return false;
    }

    // Function to check if the graph is bipartite using breadth-first search (BFS).
    // This algorithm partitions the graph into two sets and assigns colors to vertices.
    std::string Algorithms::isBipartite(const Graph& graph) {
        std::vector<int> color(graph.adjacencyMatrix.size(), -1); // -1 for not colored, 0 and 1 for two different colors
        std::queue<int> q;
        std::vector<std::unordered_set<int>> partitions(2); // Two partitions

        q.push(0);
        color[0] = 0;
        partitions[0].insert(0); // Insert the first vertex into the first partition

        // BFS traversal to partition the graph into two sets and assign colors
        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();

            int currentColor = color[currentVertex];
            int nextColor = 1 - currentColor; // Alternate color

            // Visit neighbors of the current vertex
            for (size_t i = 0; i < graph.adjacencyMatrix.size(); ++i) {
                if (graph.adjacencyMatrix[currentVertex][i]) {
                    if (color[i] == -1) {
                        color[i] = nextColor;
                        q.push(i);
                        partitions[nextColor].insert(i); // Insert the vertex into the appropriate partition
                    } else if (color[i] != nextColor) {
                        // If the adjacent vertex has a conflicting color, the graph is not bipartite
                        return "0";
                    }
                }
            }
        }

        // If we reach here, the graph is bipartite
        std::stringstream ss;
        ss << "The graph is bipartite: A={";
        for (int v : partitions[0]) {
            ss << v << ", ";
        }
        ss.seekp(-2, std::ios_base::end); // Remove the trailing ", "
        ss << "}, B={";
        for (int v : partitions[1]) {
            ss << v << ", ";
        }
        ss.seekp(-2, std::ios_base::end); // Remove the trailing ", "
        ss << "}";

        return ss.str();
    }

    // Function to check for negative cycles using the Bellman-Ford algorithm.
    // This algorithm iteratively relaxes all edges to find the shortest paths and detects negative cycles.
    bool Algorithms::negativeCycle(const Graph& graph) {
        std::vector<int> distance(graph.adjacencyMatrix.size(), INT_MAX);
        distance[0] = 0; // Assume the source vertex is 0

        // Relax all edges V-1 times
        for (size_t i = 0; i < graph.adjacencyMatrix.size() - 1; ++i) {
            for (size_t u = 0; u < graph.adjacencyMatrix.size(); ++u) {
                for (size_t v = 0; v < graph.adjacencyMatrix.size(); ++v) {
                    if (graph.adjacencyMatrix[u][v] && distance[u] != INT_MAX && distance[u] + graph.adjacencyMatrix[u][v] < distance[v]) {
                        distance[v] = distance[u] + graph.adjacencyMatrix[u][v];
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < graph.adjacencyMatrix.size(); ++u) {
            for (size_t v = 0; v < graph.adjacencyMatrix.size(); ++v) {
                if (graph.adjacencyMatrix[u][v] && distance[u] != INT_MAX && distance[u] + graph.adjacencyMatrix[u][v] < distance[v]) {
                    return true; // Negative cycle found
                }
            }
        }

        return false; // No negative cycle found
    }

} // namespace ariel
