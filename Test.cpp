#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
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
TEST_CASE("Graph subtraction")
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

TEST_CASE("Test graph multiplication")
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
TEST_CASE("Graph scalar multiplication assignment operator")
{
    // Setup the initial graph
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 2, 3},
        {4, 0, 6},
        {7, 8, 0}};
    g1.loadGraph(matrix1, true); // Assume this graph is directed

    int scalar = 3;
    g1 *= scalar; // Apply multiplication assignment
    vector<vector<int>> expectedMatrix1 = {
        {0, 6, 9},
        {12, 0, 18},
        {21, 24, 0}};
    CHECK(g1.getAdjacencyMatrix() == expectedMatrix1);

    int scalar1 = 0;
    g1 *= scalar1; // Multiply the matrix by zero
    vector<vector<int>> expectedMatrix2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g1.getAdjacencyMatrix() == expectedMatrix2);

    int scalar2 = -1;
    g1 *= scalar2; // Multiply the matrix by -1
    vector<vector<int>> expectedMatrix3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g1.getAdjacencyMatrix() == expectedMatrix3);
}

TEST_CASE("Invalid operations")
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
    CHECK_THROWS(g2.loadGraph(weightedGraph, false));
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
    g6.loadGraph(graph6, false);
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
    expected.loadGraph({{0, 8, 9, 9},
                        {8, 0, 10, 2},
                        {9, 10, 0, 9},
                        {9, 2, 9, 0}},
                       false);

    ariel::Graph result = ++ ++ ++ ++ ++g1 + g2; // 5 times increment for g1;
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
TEST_CASE("Graph with negative cycle")
{
    ariel::Graph g, g2;
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
    vector<vector<int>> weightedGraph = {
        {0, 2, 0},
        {0, 0, 2},
        {-2, 0, 0}};
    g2.loadGraph(weightedGraph, true);
    g -= g2;
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2}, B={}");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
    CHECK(ariel::Algorithms::isConnected(g) == false);
    g += ++ ++ ++g2;
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycle found.");
    CHECK(ariel::Algorithms::isConnected(g) == false);
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

    CHECK(g1 == g2);      // They are the same
    CHECK(g1 != g3);      // They are different
    CHECK_FALSE(g3 < g1); // g3 has more edges
}

TEST_CASE("10")
{
    ariel::Graph g4;
    g4.loadGraph({{0, 1},
                  {1, 0}},
                 false);
    ariel::Graph g5;

    g5.loadGraph({{0, 1},
                  {1, 0}},
                 false);
    ariel::Graph g6;
    g6.loadGraph({{0, 1, 0},
                  {1, 0, 1},
                  {0, 1, 0}},
                 false);
    CHECK((g4 >= g5) == true);
    CHECK(g5 <= g4);
    CHECK((g4 >= g6) == false);
    CHECK(g6 > g4);
}

TEST_CASE("Clique-k5")
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
TEST_CASE("Clique-k3")
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
    CHECK(g12 <= g11);
}

TEST_CASE("Clique-k6")
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
        {1, 1, 1, 1, 1, 0}};
    g12.loadGraph(graph12, false);
    CHECK(g12 < g11);
}
TEST_CASE("Weighted graph")
{
    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 3, 0, 2, 0, 0, 0, 0, 4},
        {3, 0, 0, 0, 0, 0, 0, 4, 0},
        {0, 0, 0, 6, 0, 1, 0, 2, 0},
        {2, 0, 6, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 8},
        {0, 0, 1, 0, 0, 0, 8, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0, 0},
        {0, 4, 2, 0, 0, 0, 0, 0, 0},
        {4, 0, 0, 0, 8, 0, 0, 0, 0}};
    g11.loadGraph(graph11, false);
    CHECK(ariel::Algorithms::isConnected(g11) == true);
    CHECK(ariel::Algorithms::shortestPath(g11, 3, 4) == "3->4");
    CHECK(ariel::Algorithms::shortestPath(g11, 5, 1) == "5->2->7->1");
    CHECK(ariel::Algorithms::shortestPath(g11, 6, 8) == "6->5->2->3->0->8");
    g11--;
    CHECK(ariel::Algorithms::isConnected(g11) == false);
    CHECK(ariel::Algorithms::shortestPath(g11, 3, 4) == "3->0->8->4");
    CHECK(ariel::Algorithms::shortestPath(g11, 5, 1) == "No path available");
    CHECK(ariel::Algorithms::shortestPath(g11, 6, 8) == "No path available");
}
TEST_CASE("Test graph addition post decrement")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 10, 0},
        {10, 0, 10},
        {0, 10, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g3 = g1-- + g2;

    CHECK(g3.printGraph() == "[0, 11, 1]\n[11, 0, 12]\n[1, 12, 0]");
    CHECK(g1.printGraph() == "[0, 9, 0]\n[9, 0, 9]\n[0, 9, 0]");
}

TEST_CASE("Test graph addition pre decrement")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 10, 0},
        {10, 0, 10},
        {0, 10, 0}};
    g1.loadGraph(graph, false);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph, false);
    ariel::Graph g3 = --g1 + g2;

    CHECK(g3.printGraph() == "[0, 10, 1]\n[10, 0, 11]\n[1, 11, 0]");
}

TEST_CASE("Directed graph")
{
    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 0, 12, 60, 0},
        {10, 0, 0, 0, 0},
        {0, 20, 0, 32, 0},
        {0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0}};
    g11.loadGraph(graph11, true);
    CHECK(ariel::Algorithms::negativeCycle(g11) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g11) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::isContainsCycle(g11) == "The cycle is: 0->2->1->0");
    CHECK(ariel::Algorithms::isConnected(g11) == false);

    ariel::Graph g12;
    g12 = -g11;
    CHECK(ariel::Algorithms::negativeCycle(g12) == "Negative cycle found: 2->1->0->2");
    CHECK(ariel::Algorithms::isBipartite(g12) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::isConnected(g12) == false);
}
TEST_CASE("Directed graph")
{
    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 0, 12, 60, 0},
        {10, 0, 0, 0, 0},
        {0, 20, 0, 32, 0},
        {0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0}};
    g11.loadGraph(graph11, true);
    CHECK(ariel::Algorithms::negativeCycle(g11) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g11) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::isContainsCycle(g11) == "The cycle is: 0->2->1->0");
    CHECK(ariel::Algorithms::isConnected(g11) == false);

    ariel::Graph g12;
    g12 = +g11;
    CHECK(ariel::Algorithms::negativeCycle(g12) == "No negative cycle found");
    CHECK(ariel::Algorithms::isBipartite(g12) == "The graph is not bipartite.");
    CHECK(ariel::Algorithms::isContainsCycle(g11) == "The cycle is: 0->2->1->0");
    CHECK(ariel::Algorithms::isConnected(g12) == false);
}

TEST_CASE("Graph subtraction assignment operator")
{
    // Setting up the initial graphs
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 2, 3},
        {5, 0, 6},
        {7, 0, 0}};
    g1.loadGraph(matrix1, true); // Assuming this is a directed graph

    ariel::Graph g2;
    vector<vector<int>> matrix2 = {
        {0, 2, 1},
        {0, 0, 3},
        {4, 0, 0}};
    g2.loadGraph(matrix2, true); // Same directed status for compatibility

    g1 -= g2; // Apply subtraction assignment
    vector<vector<int>> expectedMatrix = {
        {0, 0, 2},
        {5, 0, 3},
        {3, 0, 0}};
    CHECK(g1.getAdjacencyMatrix() == expectedMatrix);
}
TEST_CASE("Graph addition assignment operator")
{
    // Setting up the initial graphs
    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 5, 7},
        {2, 0, 1},
        {0, 4, 0}};
    g1.loadGraph(matrix1, true);

    ariel::Graph g2;
    vector<vector<int>> matrix2 = {
        {0, 3, 4},
        {1, 0, 0},
        {6, 0, 0}};
    g2.loadGraph(matrix2, true);

    g1 += g2; // Apply addition assignment
    vector<vector<int>> expectedMatrix = {
        {0, 8, 11},
        {3, 0, 1},
        {6, 4, 0}};
    CHECK(g1.getAdjacencyMatrix() == expectedMatrix);
}

TEST_CASE("Graph comparison operators")
{

    ariel::Graph g1;
    vector<vector<int>> matrix1 = {
        {0, 4, 3, 0, 0, 0},
        {0, 0, 5, 2, 0, 0},
        {0, 0, 0, 7, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {4, 4, 0, 0, 0, 6},
        {0, 0, 0, 0, 0, 0},
    };
    g1.loadGraph(matrix1, true); // Directed graph

    ariel::Graph g2;
    vector<vector<int>> matrix2 = {
        {0, 4, 3, 0, 0, 0},
        {0, 0, 5, 2, 0, 0},
        {0, 0, 0, 7, 0, 0},
        {0, 0, 0, 0, 2, 0},
        {4, 4, 0, 0, 0, 6},
        {0, 0, 0, 0, 0, 0},
    };
    g2.loadGraph(matrix2, true); // Identical to g1

    ariel::Graph g3;
    vector<vector<int>> matrix3 = {
        {0, 5, 2, 0},
        {0, 0, 7, 0},
        {0, 0, 0, 2},
        {0, 4, 0, 0},
    };
    g3.loadGraph(matrix3, true); // Different from g1 and g2

    CHECK(g1 == g2);
    CHECK_FALSE(g1 == g3);
    CHECK(g1 != g3);
    CHECK_FALSE(g1 != g2);

    CHECK(g1 >= g2);
    CHECK(g1 <= g2);
    CHECK(g1 > g3);
    CHECK_FALSE(g3 > g1);
    CHECK_FALSE(g3 > g1);
    CHECK_FALSE(g1 < g2);
}
TEST_CASE("Complex operation - Adding, subtracting, and scalar multiplication")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 2},
                  {2, 0}},
                 false);

    ariel::Graph g3;
    g3.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph result = ((g1 + g2) *= 2) - g3;

    ariel::Graph expected;
    expected.loadGraph({{0, 5},
                        {5, 0}},
                       false);

    CHECK(result == expected);
}

TEST_CASE("Complex operation - Increment and addition with scalar multiplication")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 2},
                  {2, 0}},
                 false);

    ariel::Graph result = ++g1 + (g2 *= 3);

    ariel::Graph expected;
    expected.loadGraph({{0, 8},
                        {8, 0}},
                       false);

    CHECK(result == expected);
}

TEST_CASE("Complex operation - Decrement and subtraction with unary minus")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 2},
                  {2, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph result = --g1 - (-g2);

    ariel::Graph expected;
    expected.loadGraph({{0, 2},
                        {2, 0}},
                       false);

    CHECK(result == expected);
}

TEST_CASE("Complex operation - In-place addition and subtraction with increment and decrement")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 2},
                  {2, 0}},
                 false);

    g1 += ++g2; // g1=4 g2=3
    g1 -= --g2; //

    ariel::Graph expected;
    expected.loadGraph({{0, 2},
                        {2, 0}},
                       false);

    CHECK(g1 == expected);
}

TEST_CASE("Edge case - empty graphs")
{
    ariel::Graph g1;
    ariel::Graph g2;
    ariel::Graph expected;

    CHECK_THROWS(g1 + g2);
    CHECK_THROWS(g1 - g2);
    CHECK_THROWS(g1 -= g2);
    CHECK_THROWS(g1 += g2);
    CHECK_THROWS(g1 * g2);
    CHECK_THROWS(+g2);
    CHECK_THROWS(-g2);
    CHECK_THROWS(--g2);
    CHECK_THROWS(g2--);
}

TEST_CASE("Edge case - Adding graphs with different directedness")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 1},
                  {1, 0}},
                 true);

    CHECK_THROWS(g1 + g2);
    CHECK_THROWS(g1 * g2);
    CHECK_THROWS(g1 += g2);
    CHECK_THROWS(g1 -= g2);
}
TEST_CASE("Edge case - Scalar multiplication with an empty graph")
{
    ariel::Graph g;
    CHECK_THROWS(g *= 5);
}

TEST_CASE("Edge case - self loops")
{
    ariel::Graph g;
    CHECK_THROWS(g.loadGraph({{1, 2},
                              {2, 1}},
                             false));

    CHECK_THROWS(g *= -2);
}

TEST_CASE("Edge case - Equality of graphs with different sizes")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 1, 0},
                  {1, 0, 1},
                  {0, 1, 0}},
                 false);

    CHECK(g1 != g2);
}

TEST_CASE("Edge case - Equality of graphs with different directedness")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 1},
                  {1, 0}},
                 true);

    CHECK(g1 != g2);
}

TEST_CASE("Edge case - Equality of graphs with different edges")
{
    ariel::Graph g1;
    g1.loadGraph({{0, 1},
                  {1, 0}},
                 false);

    ariel::Graph g2;
    g2.loadGraph({{0, 2},
                  {2, 0}},
                 false);

    CHECK(g1 != g2);
}