#include "Graph.hpp"
#include <stdexcept>
#include <sstream>

namespace ariel
{
    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix)
    {
        adjMatrix = matrix;
    }

    std::string Graph::printGraph() const
    {
        std::ostringstream oss;
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            oss << "[";
            for (size_t j = 0; j < adjMatrix[i].size(); j++)
            {
                oss << adjMatrix[i][j];
                if (j < adjMatrix[i].size() - 1)
                {
                    oss << ", ";
                }
            }
            oss << "]";
            if (i < adjMatrix.size() - 1)
            {
                oss << "\n";
            }
        }
        return oss.str();
    }

    Graph Graph::operator+(const Graph &other) const
    {
        if (adjMatrix.size() != other.adjMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to add");
        }
        Graph result;
        result.adjMatrix.resize(adjMatrix.size());
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            if (adjMatrix[i].size() != other.adjMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            result.adjMatrix[i].resize(adjMatrix[i].size());
            for (size_t j = 0; j < adjMatrix[i].size(); j++)
            {
                result.adjMatrix[i][j] = adjMatrix[i][j] + other.adjMatrix[i][j];
            }
        }
        return result;
    }
    // Graph operator- (Subtraction)
    Graph Graph::operator-(const Graph &other) const
    {
        if (adjMatrix.size() != other.adjMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to subtract");
        }
        Graph result;
        result.adjMatrix.resize(adjMatrix.size());
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            if (adjMatrix[i].size() != other.adjMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            result.adjMatrix[i].resize(adjMatrix[i].size());
            for (size_t j = 0; j < adjMatrix[i].size(); j++)
            {
                result.adjMatrix[i][j] = adjMatrix[i][j] - other.adjMatrix[i][j];
            }
        }
        return result;
    }

    // Graph operator-= (Subtraction Assignment)
    Graph &Graph::operator-=(const Graph &other)
    {
        if (adjMatrix.size() != other.adjMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to subtract");
        }
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            if (adjMatrix[i].size() != other.adjMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            for (size_t j = 0; j < adjMatrix[i].size(); j++)
            {
                adjMatrix[i][j] -= other.adjMatrix[i][j];
            }
        }
        return *this;
    }
    // Pre-increment and Post-increment
    Graph &Graph::operator++()
    {
        // Pre-increment
        for (auto &row : adjMatrix)
        {
            for (auto &val : row)
            {
                ++val;
            }
        }
        return *this;
    }

    Graph Graph::operator++(int)
    {
        // Post-increment
        Graph temp = *this;
        ++(*this); // Use the pre-increment
        return temp;
    }

    // Pre-decrement and Post-decrement
    Graph &Graph::operator--()
    {
        // Pre-decrement
        for (auto &row : adjMatrix)
        {
            for (auto &val : row)
            {
                --val;
            }
        }
        return *this;
    }

    Graph Graph::operator--(int)
    {
        // Post-decrement
        Graph temp = *this;
        --(*this); // Use the pre-decrement
        return temp;
    }
    Graph &Graph::operator+=(const Graph &other)
    {
        if (adjMatrix.size() != other.adjMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size to add");
        }
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            if (adjMatrix[i].size() != other.adjMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length");
            }
            for (size_t j = 0; j < adjMatrix[i].size(); j++)
            {
                adjMatrix[i][j] += other.adjMatrix[i][j];
            }
        }
        return *this;
    }
    Graph &Graph::operator*=(int scalar)
    {
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjMatrix[i].size(); j++)
            {
                adjMatrix[i][j] *= scalar; // Directly modify the matrix
            }
        }
        return *this; // Return a reference to the current object
    }
    Graph Graph::operator*(const Graph &other) const
    {
        if (adjMatrix.size() != other.adjMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same dimension to multiply");
        }
        Graph result;
        size_t n = adjMatrix.size();
        result.adjMatrix.resize(n, std::vector<int>(n, 0)); // Initialize result matrix

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                for (size_t k = 0; k < n; k++)
                {
                    result.adjMatrix[i][j] += adjMatrix[i][k] * other.adjMatrix[k][j];
                }
            }
        }
        return result;
    }
    bool Graph::operator==(const Graph &other) const
    {
        if (adjMatrix.size() != other.adjMatrix.size())
            return false;
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            if (adjMatrix[i] != other.adjMatrix[i])
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
        return adjMatrix.size() > other.adjMatrix.size();
    }

    bool Graph::operator<(const Graph &other) const
    {
        return other > *this;
    }

    bool Graph::isContained(const Graph &other) const
    {
        // Check if all edges in *this are contained in `other` with at least the same weights
        for (size_t i = 0; i < adjMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjMatrix[i].size(); j++)
            {
                if (adjMatrix[i][j] > other.adjMatrix[i][j])
                    return false;
            }
        }
        return true;
    }

    bool Graph::isContaining(const Graph &other) const
    {
        // Check if all edges in `other` are contained in *this with at least the same weights
        return other.isContained(*this);
    }

    int Graph::countEdges() const
    {
        int count = 0;
        for (const auto &row : adjMatrix)
        {
            for (int weight : row)
            {
                if (weight > 0)
                    count++;
            }
        }
        return count;
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
        for (const auto &row : graph.adjMatrix)
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
