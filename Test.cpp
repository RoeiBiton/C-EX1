
//roei.biton33@gmail.com
//206400426

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"


using namespace std;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph4 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No path from start to end vertex.");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph5 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->0");

    vector<vector<int>> graph6 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->0");
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph7 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={2, 0}, B={1}");

    vector<vector<int>> graph8 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph9 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph9);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={4, 2, 0}, B={3, 1}");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph10 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph10));
}



TEST_CASE("Test invalid graph with edge from vertice to itself")
{
    ariel::Graph g;
    vector<vector<int>> graph11 = {
            {0, 1, 2, 0},
            {1, 2, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0}};
    CHECK_THROWS(g.loadGraph(graph11));
}

TEST_CASE("Example of shortest path that going through negative edges")
{
    ariel::Graph g;
    vector<vector<int>> graph12 = {
            {0, 1, 0, 0,  9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4,  0},
            {0, 0, 4, 0,  5},
            {0, 0, 0, 5,  0}};
    g.loadGraph(graph12);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->1->3->4");
}

TEST_CASE("Example of negative cycle")
{
    ariel::Graph g;
    vector<vector<int>> graph13 = {
            {0, 1, 0, 0,  9},
            {0, 0, 0, -2, 0},
            {0, 3, 0, 4,  0},
            {0, 1, 4, 0,  5},
            {0, 0, 0, 5,  0}};
    g.loadGraph(graph13); // Load the graph to the object.
    CHECK(ariel::Algorithms::negativeCycle(g) == true);
}

