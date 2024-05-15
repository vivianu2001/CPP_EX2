/*
ID : 0857
GMAIL : Umanskyvivian@gmail.com
*/
#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <climits> // For INT_MAX
#include <algorithm>
#include <sstream>
namespace ariel
{
    std::string Algorithms::constructPath(const std::vector<int> &path)
    {
        std::string pathStr;
        for (size_t i = 0; i < path.size(); ++i)
        {
            pathStr += std::to_string(path[i]);
            if (i < path.size() - 1)
            {
                pathStr += "->";
            }
        }
        return pathStr;
    }

    bool Algorithms::isConnected(const Graph &graph)
    {
        const std::vector<std::vector<int>> &matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        if (n <= 1)
        {
            // Consider an empty graph as connected.
            return true;
        }
        if (graph.countEdges() == 0)
        {
            return false;
        }

        if (graph.getIsDirected())
        {
            // For directed graphs, check if the graph is strongly connected.
            return isStronglyConnected(graph);
        }

        // Find a starting node that is not isolated (if possible)
        size_t start = n; // Initialized to n, which is an invalid index.
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                if (matrix[i][j] != 0)
                {
                    start = i;
                    break; // Break from the inner loop only.
                }
            }
            if (start != n)
            {
                break; // Break from the outer loop if a start node has been found.
            }
        }

        if (start == n)
        {
            // If no starting node has been found, all nodes are isolated.
            return false;
        }

        // Use breadth-first search (BFS) from the start node to check connectivity.
        return bfs(matrix, start);
    }

    bool Algorithms::isStronglyConnected(const Graph &graph)
    {
        const std::vector<std::vector<int>> &matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();

        // Perform DFS from each vertex to check for strong connectivity
        for (size_t i = 0; i < n; ++i)
        {
            std::vector<bool> visited(n, false); // vector of nodes for visited

            dfs(matrix, visited, i);

            // If any vertex cannot be reached from the current vertex, return false
            for (bool v : visited)
            {
                if (!v)
                {
                    return false; // Return false if any vertex is not visited
                }
            }
        }
        return true; // Return true if all vertices are strongly connected
    }

    void Algorithms::dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, size_t node)
    {
        visited[node] = true;

        for (size_t i = 0; i < matrix.size(); ++i)
        {

            if (matrix[node][i] != 0 && !visited[i])
            {
                dfs(matrix, visited, i);
            }
        }
    }
    bool Algorithms::bfs(const std::vector<std::vector<int>> &matrix, size_t start)
    {
        size_t n = matrix.size();
        std::vector<bool> visited(n, false);
        std::queue<size_t> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            size_t node = q.front();
            q.pop();

            for (size_t i = 0; i < n; ++i)
            {
                if (matrix[node][i] != 0 && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        // Check if all nodes were visited
        for (bool v : visited)
        {
            if (!v)
                return false;
        }

        return true;
    }

    bool Algorithms::isCycleUtil(const std::vector<std::vector<int>> &matrix, size_t v, std::vector<bool> &visited, std::vector<int> &cyclePath, std::vector<bool> &recStack, size_t parent)
    {
        // Mark the current vertex as visited and part of the recursion stack
        visited[v] = true;
        recStack[v] = true;
        cyclePath.push_back(static_cast<int>(v)); // Add the current vertex to the cycle path

        // Iterate over all adjacent vertices of the current vertex
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            // If there is an edge from the current vertex to vertex i and it is not a self-loop
            if (matrix[v][i] != 0 && v != i) // Ignore self-loops by checking v != i
            {
                // If vertex i has not been visited, recursively call isCycleUtil
                if (!visited[i])
                {
                    if (isCycleUtil(matrix, i, visited, cyclePath, recStack, v))
                    {
                        return true; // If a cycle is detected, return true
                    }
                }
                // If vertex i is in the recursion stack and not the parent vertex
                else if (recStack[i] && i != parent)
                {
                    // Find the position of vertex i in the cycle path
                    auto startIt = std::find(cyclePath.begin(), cyclePath.end(), static_cast<int>(i));
                    // Erase all vertices in the cycle path before vertex i
                    cyclePath.erase(cyclePath.begin(), startIt);
                    return true; // Return true indicating a cycle is found
                }
            }
        }

        // Backtrack: Mark the current vertex as not part of the recursion stack
        recStack[v] = false;
        // Remove the current vertex from the cycle path
        cyclePath.pop_back();
        return false; // No cycle found, return false
    }

    std::string Algorithms::isContainsCycle(const Graph &graph)
    {
        const std::vector<std::vector<int>> &matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        if (n == 0 || graph.countEdges() == 0)
        {
            // Handle empty graph
            return "No cycle found.";
        }

        std::vector<bool> visited(n, false);
        std::vector<int> cyclePath;
        std::vector<bool> recStack(n, false);

        for (size_t i = 0; i < n; ++i)
        {
            if (!visited[i])
            {

                if (isCycleUtil(matrix, i, visited, cyclePath, recStack, std::numeric_limits<size_t>::max()))
                {
                    return "The cycle is: " + constructPath(cyclePath) + "->" + std::to_string(cyclePath.front());
                }
            }
        }
        return "No cycle found.";
    }

    std::string Algorithms::buildBipartiteResult(const std::vector<int> &color)
    {
        std::vector<int> A, B;
        for (size_t i = 0; i < color.size(); ++i)
        {
            if (color[i] == 0)
                A.push_back(static_cast<int>(i));
            else if (color[i] == 1)
                B.push_back(static_cast<int>(i));
        }

        std::ostringstream result;
        result << "The graph is bipartite: A={";
        for (size_t i = 0; i < A.size(); ++i)
        {
            result << A[i];
            if (i < A.size() - 1)
                result << ", ";
        }
        result << "}, B={";
        for (size_t i = 0; i < B.size(); ++i)
        {
            result << B[i];
            if (i < B.size() - 1)
                result << ", ";
        }
        result << "}";
        return result.str();
    }
    std::vector<std::vector<int>> Algorithms::createUndirectedMatrix(const std::vector<std::vector<int>> &directedMatrix)
    {
        size_t n = directedMatrix.size();
        std::vector<std::vector<int>> undirectedMatrix(n, std::vector<int>(n, 0));

        for (size_t u = 0; u < n; ++u)
        {
            for (size_t v = 0; v < n; ++v)
            {
                // If there's a directed edge from u to v but not from v to u
                if (directedMatrix[u][v] != 0 && directedMatrix[v][u] == 0)
                {
                    undirectedMatrix[u][v] = directedMatrix[u][v]; // Add edge from u to v
                    undirectedMatrix[v][u] = directedMatrix[u][v]; // Add edge from v to u to make it bidirectional
                }
                // If there's a directed edge from v to u but not from u to v
                else if (directedMatrix[v][u] != 0 && directedMatrix[u][v] == 0)
                {
                    undirectedMatrix[u][v] = directedMatrix[v][u]; // Add edge from u to v
                    undirectedMatrix[v][u] = directedMatrix[v][u]; // Add edge from v to u to make it bidirectional
                }
                // If edges exist in both directions or none
                else
                {
                    undirectedMatrix[u][v] = std::max(directedMatrix[u][v], directedMatrix[v][u]);
                    undirectedMatrix[v][u] = undirectedMatrix[u][v]; // Ensure the graph remains symmetric
                }
            }
        }

        return undirectedMatrix;
    }

    std::string Algorithms::isBipartite(const Graph &graph)
    {
        const std::vector<std::vector<int>> &originalMatrix = graph.getAdjacencyMatrix();
        size_t n = originalMatrix.size();
        std::vector<int> color(n, -1); // Initializing colors to -1 to indicate unvisited nodes

        if (n <= 1)
        {
            return "The graph is not bipartite."; // Directly handle the empty graph case
        }

        std::vector<std::vector<int>> matrixToUse = originalMatrix;

        if (graph.getIsDirected())
        {
            std::vector<std::vector<int>> tempMatrix = createUndirectedMatrix(originalMatrix);
            matrixToUse = tempMatrix; // Use the temporary undirected matrix for bipartite checking
        }

        // Check each component of the graph
        for (size_t i = 0; i < n; ++i)
        {
            if (color[i] == -1) // If this component isn't colored yet
            {
                if (!checkBipartite(matrixToUse, color, i))
                {
                    return "The graph is not bipartite.";
                }
            }
        }

        return buildBipartiteResult(color); // Assuming this function builds the result string based on colors
    }

    bool Algorithms::checkBipartite(const std::vector<std::vector<int>> &matrix, std::vector<int> &color, size_t start)
    {
        std::queue<size_t> q; // Use size_t for queue to align with the vector indexing
        q.push(start);
        color[start] = 0; // Properly using size_t for index

        while (!q.empty())
        {
            size_t u = q.front(); // Use size_t for index
            q.pop();

            for (size_t v = 0; v < matrix.size(); ++v)
            { // Use size_t for index
                if (matrix[u][v] != 0)
                { // There is an edge
                    if (color[v] == -1)
                    {                            // If not colored
                        color[v] = 1 - color[u]; // Color with the opposite color
                        q.push(v);
                    }
                    else if (color[v] == color[u])
                    {                 // If same color as parent
                        return false; // Not bipartite
                    }
                }
            }
        }
        return true;
    }

    std::string Algorithms::negativeCycle(const Graph &graph)
    {
        const std::vector<std::vector<int>> &matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        std::vector<int> dist, prev;

        if (n == 0 || graph.countEdges() == 0)
        {
            // Handle empty graph
            return "No negative cycle found";
        }
        // Find the first vertex with outgoing edges
        int startVertex = -1;
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                if (matrix[i][j] != 0)
                {
                    startVertex = static_cast<int>(i);
                    break;
                }
            }
            if (startVertex != -1)
                break;
        }

        if (startVertex == -1)
        {
            // No outgoing edges found from any vertex
            return "No negative cycle found";
        }

        if (!bellmanFord(matrix, startVertex, dist, prev))
        {
            // Find and construct the negative cycle path
            for (size_t u = 0; u < n; ++u)
            {
                for (size_t v = 0; v < n; ++v)
                {
                    if (matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
                    {
                        std::vector<int> cycle;
                        int x = v;
                        do
                        {
                            cycle.push_back(static_cast<int>(x));
                            x = prev[static_cast<size_t>(x)];
                        } while (x != v);
                        cycle.push_back(static_cast<int>(v));
                        std::reverse(cycle.begin(), cycle.end());

                        return "Negative cycle found: " + constructPath(cycle);
                    }
                }
            }
        }

        return "No negative cycle found";
    }

    std::string Algorithms::shortestPath(const Graph &graph, int start, int end)
    {
        const std::vector<std::vector<int>> &matrix = graph.getAdjacencyMatrix();
        size_t n = matrix.size();
        if (n == 0 || graph.countEdges() == 0)
        {
            return "No shortest path in empty graph";
        }

        // Ensure start and end are within the valid range and non-negative
        if (start < 0 || static_cast<size_t>(start) >= n || end < 0 || static_cast<size_t>(end) >= n)
        {
            return "Invalid start or end vertex."; // Return an error message for invalid vertices
        }

        size_t s = static_cast<size_t>(start);

        // Check for negative cycles using the existing negativeCycle function
        std::string negativeCycleResult = negativeCycle(graph);
        if (negativeCycleResult.find("Negative cycle found") != std::string::npos)
        {
            return "Negative cycle detected, shortest path not defined.";
        }

        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::vector<int> prev(n, -1);

        if (graph.getIsNegativeEdges())
        {
            // Use Bellman-Ford algorithm for graphs with negative edges
            dist[s] = 0; // Now using s which is of type size_t

            if (!bellmanFord(matrix, static_cast<int>(s), dist, prev))

            {
                return "Negative cycle detected, shortest path not defined.";
            }

            return constructPathFromPrev(prev, end, s);
        }
        else
        {
            // Use Dijkstra's algorithm for graphs without negative edges
            std::vector<int> prev = dijkstra(matrix, static_cast<int>(s));

            return constructPathFromPrev(prev, end, s);
        }
    }
    std::string Algorithms::constructPathFromPrev(const std::vector<int> &prev, int end, size_t start)
    {
        std::vector<int> path;
        int current = end;

        // Track back from end to start using the prev array
        while (current != -1 && static_cast<size_t>(current) != start)
        {
            path.push_back(current);
            current = prev[static_cast<size_t>(current)];
        }

        if (current == -1)
        {
            // If current is -1, it means we've hit a vertex with no predecessor before hitting start
            return "No path available"; // or any other indication that no path exists
        }

        // Only add start to path if it's part of the path
        path.push_back(static_cast<int>(start));
        std::reverse(path.begin(), path.end());

        return constructPath(path);
    }

    bool Algorithms::bellmanFord(const std::vector<std::vector<int>> &matrix, int source, std::vector<int> &dist, std::vector<int> &prev)
    {
        size_t n = matrix.size();
        if (source < 0 || static_cast<size_t>(source) >= n)
        {
            std::cout << "Invalid source index provided." << std::endl;
            return false;
        }

        // Initialize distances and predecessors
        dist.assign(n, std::numeric_limits<int>::max());
        prev.assign(n, -1);
        dist[static_cast<size_t>(source)] = 0;

        bool updated = false;
        // Relax all edges |V-1| times
        for (size_t i = 0; i < n - 1; ++i)
        {
            updated = false;
            for (size_t u = 0; u < n; ++u)
            {
                if (dist[u] == std::numeric_limits<int>::max())
                {
                    continue; // Skip if u is unreachable
                }

                for (size_t v = 0; v < n; ++v)
                {
                    if (matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + matrix[u][v];
                        prev[v] = static_cast<int>(u);
                        updated = true;
                    }
                }
            }
            if (!updated)
            {
                break;
            }
        }

        // Check for negative weight cycles
        for (size_t u = 0; u < n; ++u)
        {
            if (dist[u] == std::numeric_limits<int>::max())
            {
                continue; // Skip if u is unreachable
            }

            for (size_t v = 0; v < n; ++v)
            {
                if (matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
                {

                    return false;
                }
            }
        }

        return true; // No negative cycles found
    }

    std::vector<int> Algorithms::dijkstra(const std::vector<std::vector<int>> &matrix, int start)
    {
        size_t n = matrix.size();
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        std::vector<int> prev(n, -1);
        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>>
            pq;

        if (start < 0 || static_cast<size_t>(start) >= n)
        {
            throw std::invalid_argument("Invalid start vertex"); // Ensuring start is within range
        }

        size_t s = static_cast<size_t>(start);
        dist[s] = 0;
        pq.push({0, static_cast<int>(s)});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            size_t su = static_cast<size_t>(u);
            if (d > dist[su])
                continue;

            for (size_t v = 0; v < n; ++v)
            {
                if (matrix[su][v] != 0)
                { // Ensure su is used for indexing
                    int new_dist = dist[su] + matrix[su][v];
                    if (new_dist < dist[v])
                    {
                        dist[v] = new_dist;
                        prev[v] = u;
                        pq.push({new_dist, static_cast<int>(v)});
                    }
                }
            }
        }

        return prev;
    }

} // namespace ariel