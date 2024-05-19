
#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <string>
#include <iostream>

namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        bool isDirected;
        bool NegativeEdges;
        int edgeCount;
        bool isContained(const Graph &other) const;
        bool isContaining(const Graph &other) const;
        int countEdges();
        void checkCompatibility(const Graph &other) const;
        void checkCompatibility() const;

    public:
        Graph();
        void loadGraph(const std::vector<std::vector<int>> &matrix, bool directed);
        std::string printGraph() const;
        const std::vector<std::vector<int>> &getAdjacencyMatrix() const;

        // Check if the graph is directed
        bool getIsDirected() const;

        bool getIsNegativeEdges() const;
        int getEdgeCount() const;
        // Arithmetic operators
        Graph operator+(const Graph &other) const;
        Graph operator+() const;
        Graph operator-(const Graph &other) const;
        Graph operator-() const;
        Graph &operator+=(const Graph &other);
        Graph &operator-=(const Graph &other);
        Graph &operator*=(int scalar);
        Graph operator*(const Graph &other) const; // Graph multiplication

        // Increment and decrement
        Graph &operator++();   // Pre-increment
        Graph operator++(int); // Post-increment
        Graph &operator--();   // Pre-decrement
        Graph operator--(int); // Post-decrement

        // Comparison operators
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
        bool operator>(const Graph &other) const;
        bool operator<(const Graph &other) const;
        bool operator>=(const Graph &other) const;
        bool operator<=(const Graph &other) const;

        // Output operator
        friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
    };
}
#endif // GRAPH_HPP