#include "Graph.hpp"
#include <stdexcept>
#include <sstream>

namespace ariel
{
    Graph::Graph(bool directed) : isDirected(directed) {}
    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix, bool directed)
    {
        // Load the graph from the given adjacency matrix
        isDirected = directed;

        // Check if the matrix is empty
        if (matrix.empty())
        {
            adjacencyMatrix.clear();
            return;
        }

        // Check if the matrix is square
        size_t size = matrix.size(); // number of rows
        for (const auto &row : matrix)
        {
            if (row.size() != size)
            {
                throw std::invalid_argument("The adjacency matrix must be square.");
            }
        }

        // If the graph is undirected, check for symmetry
        if (!isDirected)
        {
            for (size_t i = 0; i < size; i++)
            {
                for (size_t j = 0; j < i; j++)
                { // Check only half as matrix should be symmetric
                    if (matrix[i][j] != matrix[j][i])
                    {
                        throw std::invalid_argument("Matrix must be symmetric for undirected graphs");
                    }
                }
            }
        }
        // Check for negative weights
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                if (matrix[i][j] < 0)
                {
                    NegativeEdges = true;
                }
            }
        }

        NegativeEdges = false; // If we reach here, there are no negative edges

        adjacencyMatrix = matrix;
    }
    const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    int Graph::countEdges() const
    {
        int edges = 0;
        size_t size = adjacencyMatrix.size();
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = (isDirected ? 0 : i + 1); j < size; ++j)
            {
                // For directed graphs, count all non-zero edges
                // For undirected graphs, count only the upper triangular matrix
                if (!isDirected && i != j && adjacencyMatrix[j][i] != 0)
                {
                    edges++;
                }
                if (adjacencyMatrix[i][j] != 0)
                {
                    edges++;
                }
            }
        }
        return (isDirected ? edges : edges / 2); // Divide by 2 for undirected graphs
    }

    // Check if the graph is directed
    bool Graph::getIsDirected() const
    {
        return isDirected;
    }

    std::string Graph::printGraph() const
    {
        std::ostringstream oss;
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            oss << "[";
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                oss << adjacencyMatrix[i][j];
                if (j < adjacencyMatrix[i].size() - 1)
                {
                    oss << ", ";
                }
            }
            oss << "]";
            if (i < adjacencyMatrix.size() - 1)
            {
                oss << "\n";
            }
        }
        return oss.str();
    }

    Graph Graph::operator+(const Graph &other) const
    {
        if (adjacencyMatrix.size() != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to add");
        }
        Graph result;
        result.adjacencyMatrix.resize(adjacencyMatrix.size());
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            if (adjacencyMatrix[i].size() != other.adjacencyMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            result.adjacencyMatrix[i].resize(adjacencyMatrix[i].size());
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                result.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }
        return result;
    }
    // Graph operator- (Subtraction)
    Graph Graph::operator-(const Graph &other) const
    {
        if (adjacencyMatrix.size() != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to subtract");
        }
        Graph result;
        result.adjacencyMatrix.resize(adjacencyMatrix.size());
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            if (adjacencyMatrix[i].size() != other.adjacencyMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            result.adjacencyMatrix[i].resize(adjacencyMatrix[i].size());
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                result.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
        }
        return result;
    }

    // Graph operator-= (Subtraction Assignment)
    Graph &Graph::operator-=(const Graph &other)
    {
        if (adjacencyMatrix.size() != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to subtract");
        }
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            if (adjacencyMatrix[i].size() != other.adjacencyMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }
    /// Pre-increment
    Graph &Graph::operator++()
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &val : row)
            {
                if (val != 0)
                { // Increment only if the value is not 0
                    ++val;
                }
            }
        }
        return *this;
    }

    // Post-increment
    Graph Graph::operator++(int)
    {
        Graph temp = *this; // Make a copy of the current state
        ++(*this);          // Use the pre-increment
        return temp;
    }

    // Pre-decrement
    Graph &Graph::operator--()
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &val : row)
            {
                if (val != 0)
                { // Decrement only if the value is not 0
                    --val;
                }
            }
        }
        return *this;
    }

    // Post-decrement
    Graph Graph::operator--(int)
    {
        Graph temp = *this; // Make a copy of the current state
        --(*this);          // Use the pre-decrement
        return temp;
    }

    Graph &Graph::operator+=(const Graph &other)
    {
        if (adjacencyMatrix.size() != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to add");
        }
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            if (adjacencyMatrix[i].size() != other.adjacencyMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }
    Graph &Graph::operator*=(int scalar)
    {
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] *= scalar; // Directly modify the matrix
            }
        }
        return *this; // Return a reference to the current object
    }
    Graph Graph::operator*(const Graph &other) const
    {
        if (adjacencyMatrix.size() != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same dimension to multiply");
        }
        Graph result;
        size_t n = adjacencyMatrix.size();
        result.adjacencyMatrix.resize(n, std::vector<int>(n, 0)); // Initialize result matrix

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                for (size_t k = 0; k < n; k++)
                {
                    result.adjacencyMatrix[i][j] += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
                // Ensuring the diagonal is always zero
                result.adjacencyMatrix[i][i] = 0;
            }
        }
        return result;
    }

    bool Graph::operator==(const Graph &other) const
    {
        if (adjacencyMatrix.size() != other.adjacencyMatrix.size())
            return false;
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            if (adjacencyMatrix[i] != other.adjacencyMatrix[i])
                return false;
        }
        return true;
    }

    bool Graph::operator!=(const Graph &other) const
    {
        return !(*this == other);
    }
    bool Graph::operator>(const Graph &other) const
    {
        if (isContained(other))
            return false;
        if (isContaining(other))
            return true;
        int edges1 = countEdges();
        int edges2 = other.countEdges();
        if (edges1 != edges2)
            return edges1 > edges2;
        return adjacencyMatrix.size() > other.adjacencyMatrix.size();
    }

    bool Graph::operator<(const Graph &other) const
    {
        return other > *this;
    }

 bool Graph::isContained(const Graph &other) const
{
    // Check if all edges in *this are contained in `other` with at least the same weights
    for (size_t i = 0; i < adjacencyMatrix.size(); i++)
    {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
        {
            // Perform bounds check before accessing elements of other.adjacencyMatrix
            if (i < other.adjacencyMatrix.size() && j < other.adjacencyMatrix[i].size()) {
                if (adjacencyMatrix[i][j] > other.adjacencyMatrix[i][j])
                    return false;
            } else {
                // If (i, j) is out of bounds of other.adjacencyMatrix, it means that other does not have
                // an edge at this position. Depending on your requirements, you may choose to handle this
                // differently. For simplicity, we'll consider this a mismatch and return false.
                return false;
            }
        }
    }
    return true;
}


    bool Graph::isContaining(const Graph &other) const
    {
        // Check if all edges in `other` are contained in *this with at least the same weights
        return other.isContained(*this);
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return !(*this < other);
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return !(*this > other);
    }
    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        os << "Adjacency Matrix:\n";
        for (const auto &row : graph.adjacencyMatrix)
        {
            os << "[ ";
            for (int val : row)
            {
                os << val << " ";
            }
            os << "]\n";
        }
        return os;
    }

}
