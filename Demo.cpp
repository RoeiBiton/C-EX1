
//roei.biton33@gmail.com
//206400426

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using ariel::Algorithms;
using namespace std;

int main()
{
    ariel::Graph g;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->1->2.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={2, 0}, B={1}."
    cout << endl;

    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};

    g.loadGraph(graph2); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 8 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "No path from start to end vertex.".
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" (false).
    cout << endl;

    // 5x5 matrix that reprsents a connected weighted graph.
    vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 0},
            {1, 0, 3, 0, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph3); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 10 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "0->1->2->3->4".
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={4, 2, 0}, B={3, 1}"
    cout << endl;

    // 5x4 matrix that reprsents invalid graph.
    vector<vector<int>> graph4 = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
    try
    {
        g.loadGraph(graph4); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
        cout << endl;
    }

    // 4x4 matrix that reprsents invalid graph (Example of edge from vertice to itself, the diagonal line is not 0).
    cout << "Example of edge from vertice to itself, the diagonal line is not 0" <<endl;
    vector<vector<int>> graph5 = {
            {0, 1, 2, 0},
            {1, 2, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0}};
    try
    {
        g.loadGraph(graph5); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: Diagonal elements must be zero."
        cout << endl;
    }

    // 5x5 matrix that reprsents a connected weighted graph.
    cout << "Example of shortest path that going through negative edges" <<endl;

    vector<vector<int>> graph6 = {
            {0, 1, 0, 0, 9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph6); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 8 edges."
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "0->1->3->4".
    cout << endl;

    // 5x5 matrix that reprsents a connected weighted graph.
    cout << "Example of negative cycle check and shortest path fail because of negative cycle" <<endl;

    vector<vector<int>> graph7 = {
            {0, 1, 0, 0, 9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4, 0},
            {0, 1, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph7); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 9 edges."
    cout << Algorithms::negativeCycle(g) << endl;      // Should print: "1"
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "Negative cycle detected. Shortest paths not well-defined.".
    cout << endl;

    // 5x5 matrix that reprsents a connected weighted graph.
    cout << "Example of negative cycle check and printing the cycle" <<endl;

    vector<vector<int>> graph8 = {
            {0, 1, 0, 0, 9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4, 0},
            {0, 1, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph8); // Load the graph to the object.

    g.printGraph();                                     // Should print: "Graph with 5 vertices and 9 edges."
    cout << Algorithms::negativeCycle(g) << endl;       // Should print: "1"
    cout << Algorithms::isContainsCycle(g) << endl;     // Should print: "The cycle is: 1->3->1".
    cout << endl;


    // 4x4 matrix that reprsents a connected weighted graph.
    cout << "Example of graph that is non connected" <<endl;

    vector<vector<int>> graph9 = {
            {0, 1, 0, 0},
            {1, 0, 2, 0},
            {0, 3, 0, 0},
            {0, 0, 0, 0}};
    g.loadGraph(graph9); // Load the graph to the object.

    g.printGraph();                                     // Should print: "Graph with 4 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;       // Should print: "0"
    cout << endl;



}