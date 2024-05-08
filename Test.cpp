#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("1-Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("2-Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
}

TEST_CASE("3-Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    // g2.loadGraph(weightedGraph, false);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2, false);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph6 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    // g6.loadGraph(graph3, false);
    CHECK_THROWS(g1 + g6);
}
TEST_CASE("Graph addition with larger matrices")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 2, 3, 4},
                  {2, 0, 5, 0},
                  {3, 5, 0, 1},
                  {4, 0, 1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 1, 1, 0},
                  {1, 0, 0, 2},
                  {1, 0, 0, 3},
                  {0, 2, 3, 0}},
                 false);

    ariel::Graph expected;
    expected.loadGraph({{0, 3, 4, 4},
                        {3, 0, 5, 2},
                        {4, 5, 0, 4},
                        {4, 2, 4, 0}},
                       false);

    ariel::Graph result = g1 + g2;
    CHECK(result == expected);
}
TEST_CASE("Graph subtraction with larger matrices")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 4, 6, 4},
                  {4, 0, 10, 2},
                  {6, 10, 0, 4},
                  {4, 2, 4, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 2, 3, 2},
                  {2, 0, 5, 1},
                  {3, 5, 0, 2},
                  {2, 1, 2, 0}},
                 false);

    ariel::Graph expected;
    expected.loadGraph({{0, 2, 3, 2},
                        {2, 0, 5, 1},
                        {3, 5, 0, 2},
                        {2, 1, 2, 0}},
                       false);

    ariel::Graph result = g1 - g2;
    CHECK(result == expected);
}
TEST_CASE("Graph subtraction with larger matrices")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 4, 6, 4},
                  {4, 0, 10, 2},
                  {6, 10, 0, 4},
                  {4, 2, 4, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 2, 3, 2},
                  {2, 0, 5, 1},
                  {3, 5, 0, 2},
                  {2, 1, 2, 0}},
                 false);

    ariel::Graph expected;
    expected.loadGraph({{0, 2, 3, 2},
                        {2, 0, 5, 1},
                        {3, 5, 0, 2},
                        {2, 1, 2, 0}},
                       false);

    ariel::Graph result = g1 - g2;
    CHECK(result == expected);
}
TEST_CASE("Graph comparison operators")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 3, 4},
                  {3, 0, 0},
                  {4, 0, 0}},
                 false);
    g1++;
    ariel::Graph g2;
    g2.loadGraph({{0, 4, 5},
                  {4, 0, 0},
                  {5, 0, 0}},
                 false);

    CHECK(g1 == g2); // They are the same
}
TEST_CASE("5-Graph with negative cycle")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {-3, 0, 0}};
    g.loadGraph(graph, true);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Negative cycle found: 1->2->0->1");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
    CHECK(ariel::Algorithms::isConnected(g) == true);
    g++;
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("Graph comparison operators")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 3, 4},
                  {3, 0, 0},
                  {4, 0, 0}},
                 false);
    g1--;
    ariel::Graph g2;
    g2.loadGraph({{0, 2, 3},
                  {2, 0, 0},
                  {3, 0, 0}},
                 false);

    CHECK(g1 == g2); // They are the same
}

TEST_CASE("Graph comparison operators")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 3, 4},
                  {3, 0, 0},
                  {4, 0, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 3, 4},
                  {3, 0, 0},
                  {4, 0, 0}},
                 false);

    ariel::Graph g3;
    g3.loadGraph({{0, 1, 1},
                  {1, 0, 2},
                  {1, 2, 0}},
                 false);

    CHECK(g1 == g2); // They are the same
    CHECK(g1 != g3); // They are different
    CHECK(g3 > g1);  // g3 has more edges
}

TEST_CASE("4")
{
    ariel::Graph g4;
    g4.loadGraph({
        {0, 1},
        {1, 0}}, false);
    ariel::Graph g5;
  
    g5.loadGraph( {
        {0, 1},
        {1, 0}}, false);
    ariel::Graph g6;
    g6.loadGraph({
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}}, false);
    CHECK(g4 >= g5);       // Should be true, as g1 and g2 are equal
    CHECK(g5 <= g4);       // Should be true, as g2 and g1 are equal
    CHECK_FALSE(g4 >= g6); // Should be false, as g3 is not equal or smaller in any sense compared to g1
    CHECK(g6 > g4);        // Should be true if we consider g3 to have more nodes/edges
}

TEST_CASE("5")
{
    ariel::Graph g7;
    vector<vector<int>> graph7 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g7.loadGraph(graph7, false);

    ariel::Graph g8;
    vector<vector<int>> graph8 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g8.loadGraph(graph8, false);
    CHECK(g7 == g8);
}
TEST_CASE("6-Clique-k5")
{
    ariel::Graph g9;
    vector<vector<int>> graph9 = {
        {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}};
    g9.loadGraph(graph9, false);

    ariel::Graph g10;
    vector<vector<int>> graph10 = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}};
    g10.loadGraph(graph10, false);
    CHECK(g10 < g9);
}
TEST_CASE("7-Clique-k3")
{
    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}};
    g11.loadGraph(graph11, false);

    ariel::Graph g12;
    vector<vector<int>> graph12 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g12.loadGraph(graph12, false);
    CHECK(g12 < g11);
}
TEST_CASE("8-Clique-k3")
{
    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}};
    g11.loadGraph(graph11, false);

    ariel::Graph g12;
    vector<vector<int>> graph12 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g12.loadGraph(graph12, false);
    CHECK(g12 < g11);
}
TEST_CASE("9-Clique-k6")
{
    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0}};
    g11.loadGraph(graph11, false);

    ariel::Graph g12;
    vector<vector<int>> graph12 = {
        {0, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1}};
    g12.loadGraph(graph12, false);
    CHECK(g12 < g11);
}