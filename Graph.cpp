#include "Graph.hpp"
#include <stdexcept>
#include <sstream>

namespace ariel
{
    Graph::Graph() : isDirected(false), NegativeEdges(false), edgeCount(0)
    {
    }
    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix, bool directed)
    {
        if (matrix.empty())
        {
            throw std::invalid_argument("The adjacency matrix is empty.");
        }

        size_t size = matrix.size();
        for (size_t i = 0; i < size; ++i)
        {
            if (matrix[i].size() != size)
            {
                throw std::invalid_argument("The adjacency matrix must be square.");
            }

            for (size_t j = (directed ? 0 : i); j < size; ++j)
            {
                if ((i == j) && matrix[i][j] != 0)
                {
                    throw std::invalid_argument("No self-loops allowed.");
                }
                if (matrix[i][j] < 0)
                {
                    NegativeEdges = true;
                }
                if (!directed && matrix[i][j] != matrix[j][i])
                {
                    throw std::invalid_argument("Matrix must be symmetric for undirected graphs.");
                }
            }
        }

        // If validation is successful, update the graph state
        isDirected = directed;
        adjacencyMatrix = matrix;
        edgeCount = countEdges();
    }
    const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

    int Graph::countEdges()
    {
        int edges = 0;
        size_t size = adjacencyMatrix.size();

        // Adjust starting index for undirected graphs to only count the upper triangle
        for (size_t i = 0; i < size; ++i)
        {
            size_t start_j = isDirected ? 0 : i; // Start from 0 if directed, from i if undirected
            for (size_t j = start_j; j < size; ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    edges++;
                    if (adjacencyMatrix[i][j] < 0)
                    {
                        NegativeEdges = true;
                    }
                }
                // Check the symmetric element only if it's an undirected graph and i != j
                if (!isDirected && i != j && adjacencyMatrix[j][i] != 0 && adjacencyMatrix[j][i] != adjacencyMatrix[i][j])
                {
                    edges++;
                    if (adjacencyMatrix[j][i] < 0)
                    {
                        NegativeEdges = true;
                    }
                }
            }
        }
        return edges;
    }

    int Graph::getEdgeCount() const
    {
        return edgeCount;
    }

    bool Graph::getIsDirected() const
    {
        return isDirected;
    }
    bool Graph::getIsNegativeEdges() const
    {
        return NegativeEdges;
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
    void Graph::checkCompatibility(const Graph &other) const
    {
        if (isDirected != other.isDirected)
        {
            throw std::invalid_argument("Both graphs must be either directed or undirected.");
        }
        if (adjacencyMatrix.size() != other.adjacencyMatrix.size())
        {
            throw std::invalid_argument("Graphs must be of the same size.");
        }
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
        {
            if (adjacencyMatrix[i].size() != other.adjacencyMatrix[i].size())
            {
                throw std::invalid_argument("Graph rows must be of the same length.");
            }
        }
    }

    Graph Graph::operator+(const Graph &other) const
    {
        checkCompatibility(other);

        Graph result;
        result.adjacencyMatrix.resize(adjacencyMatrix.size());
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            result.adjacencyMatrix[i].resize(adjacencyMatrix[i].size());
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                result.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }
        result.isDirected = isDirected;
        result.edgeCount = result.countEdges();

        return result;
    }
    // Graph operator- (Subtraction)
    Graph Graph::operator-(const Graph &other) const
    {
        checkCompatibility(other);
        Graph result;
        result.adjacencyMatrix.resize(adjacencyMatrix.size());
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {

            result.adjacencyMatrix[i].resize(adjacencyMatrix[i].size());
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                result.adjacencyMatrix[i][j] = adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
        }
        result.isDirected = isDirected;
        result.edgeCount = result.countEdges();
        return result;
    }

    // Graph operator-= (Subtraction Assignment)
    Graph &Graph::operator-=(const Graph &other)
    {
        checkCompatibility(other);
        
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }
        this->edgeCount = this->countEdges();
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
        this->edgeCount = this->countEdges();
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
        this->edgeCount = this->countEdges();
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
        checkCompatibility(other);
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }
        this->edgeCount = this->countEdges();
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
        this->edgeCount = this->countEdges();
        return *this;
    }
    Graph Graph::operator*(const Graph &other) const
    {
        checkCompatibility(other);
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

        result.isDirected = isDirected;
        result.edgeCount = result.countEdges();
        return result;
    }
    Graph Graph::operator+() const
    {
        // Returns a copy of the graph as it is
        Graph result = *this;
        return result;
    }
    Graph Graph::operator-() const
    {
        Graph result;
        result.adjacencyMatrix.resize(adjacencyMatrix.size(), std::vector<int>(adjacencyMatrix.size(), 0));
        result.isDirected = isDirected;
        result.edgeCount = edgeCount;
        for (size_t i = 0; i < adjacencyMatrix.size(); i++)
        {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); j++)
            {
                result.adjacencyMatrix[i][j] = -adjacencyMatrix[i][j];
            }
        }
        result.isDirected = isDirected;
        result.edgeCount = result.countEdges();
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
            return true;
        if (isContaining(other))
            return false;
        int edges1 = getEdgeCount();
        int edges2 = other.getEdgeCount();
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
        if (*this == other)
        {
            return false;
        }
        size_t numOtherRows = other.adjacencyMatrix.size();
        size_t numOtherCols = other.adjacencyMatrix[0].size();

        // Ensure the 'other' matrix isn't larger than the 'this' matrix
        if (numOtherRows > adjacencyMatrix.size() || (adjacencyMatrix.size() > 0 && numOtherCols > adjacencyMatrix[0].size()))
        {
            return false;
        }

        // Iterate over each potential starting row and column in 'this' adjacency matrix
        for (size_t startRow = 0; startRow <= adjacencyMatrix.size() - numOtherRows; ++startRow)
        {
            for (size_t startCol = 0; startCol <= adjacencyMatrix[startRow].size() - numOtherCols; ++startCol)
            {
                // Check if the current set of rows and columns matches the smaller matrix
                bool subMatrixMatch = true;
                for (size_t i = 0; i < numOtherRows; ++i)
                {
                    for (size_t j = 0; j < numOtherCols; ++j)
                    {
                        if (adjacencyMatrix[startRow + i][startCol + j] != other.adjacencyMatrix[i][j])
                        {
                            subMatrixMatch = false;
                            break;
                        }
                    }
                    if (!subMatrixMatch)
                        break; // Break out of the outer loop if a mismatch is found
                }
                if (subMatrixMatch)
                    return true; // A matching sub-matrix has been found
            }
        }
        return false; // No matching sub-matrix found
    }

    bool Graph::isContaining(const Graph &other) const
    {
        // Check if all edges in `other` are contained in *this with at least the same weights
        return other.isContained(*this);
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return !(*this < other) || (*this == other);
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return !(*this > other) || (*this == other);
    }
    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        int numEdges = graph.getEdgeCount();
        int numVertices = graph.adjacencyMatrix.size();

        os << "Graph with " << numVertices << " vertices and " << numEdges << " edges.\n";
        os << "The graph is " << (graph.isDirected ? "directed." : "undirected.") << "\n";

        return os;
    }

}
