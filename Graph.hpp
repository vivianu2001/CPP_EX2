
#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <string>
#include <iostream> // For std::ostream

namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> adjMatrix;

    public:
        // Graph management
        void loadGraph(const std::vector<std::vector<int>> &matrix);
        std::string printGraph() const;

        // Arithmetic operators
        Graph operator+(const Graph &other) const;
        Graph operator-(const Graph &other) const;
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
        bool isContained(const Graph &other) const;
        bool isContaining(const Graph &other) const;
        int countEdges() const;

        // Output operator
        friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
    };
}
#endif // GRAPH_HPP