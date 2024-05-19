/*
 * Demo program for Exercise 3.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
using ariel::Algorithms;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

void runDemo()
{
    ariel::Graph g1;
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph, false); // Load the graph to the object.

    cout << g1; // Should print the matrix of the graph: Graph with 3 vertices and 2 edges.The graph is undirected

    // 3x3 matrix that represents a weighted connected graph.
    vector<vector<int>>
        weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    ariel::Graph g2;
    g2.loadGraph(weightedGraph, false); // Load the graph to the object.

    ariel::Graph g3 = g1 + g2; // Add the two graphs together.
    cout << g3;                // Graph with 3 vertices and 3 edges.The graph is undirected.

    g1 *= -2;   // Multiply the graph by -2.
    cout << g1; // Should print the matrix of the graph:Graph with 3 vertices and 2 edges.The graph is undirected.

    ariel::Graph g4 = g1 * g2; // Multiply the two graphs together.
    cout << g4;                // Should print Graph with 3 vertices and 4 edges.The graph is undirected.

    // 5x5 matrix that represents a connected graph.
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    ariel::Graph g5;
    g5.loadGraph(graph2, false); // Load the graph to the object.
    try
    {
        ariel::Graph g6 = g5 * g1; // Multiply the two graphs together.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print "Graphs must be of the same size."
    }

    ariel::Graph g7;
    vector<vector<int>> graph7 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g7.loadGraph(graph7, false);
    cout << --g7 << endl; // Graph with 5 vertices and 0 edges.The graph is undirected.
}