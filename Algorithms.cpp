#include "Algorithms.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <climits> // For INT_MAX

namespace ariel
{

    bool Algorithms::isConnected(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        if (n == 0)
        {

            return true;
        }

        if (g.getIsDirected())
        {
            return isStronglyConnected(g);
        }
        else
        {
            // Find a starting node that is not isolated (if possible)
            int start = -1;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (matrix[i][j] != 0)
                    {
                        start = i;
                        break;
                    }
                }
                if (start != -1)
                    break;
            }

            if (start == -1)
                return false; // Graph is empty or all nodes are isolated

            return bfs(matrix, start);
        }
    }

    bool Algorithms::isStronglyConnected(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();

        // Perform DFS from each vertex to check for strong connectivity
        for (int i = 0; i < n; ++i)
        {
            std::vector<bool> visited(n, false);
            dfs(matrix, visited, i);

            // If any vertex cannot be reached from the current vertex, return false
            for (bool v : visited)
            {
                if (!v)
                    return false;
            }
        }
        return true;
    }

    void Algorithms::dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, int node)
    {
        visited[node] = true;

        for (int i = 0; i < static_cast<int>(matrix.size()); ++i)

        {
            if (matrix[node][i] && !visited[i])
            {
                dfs(matrix, visited, i);
            }
        }
    }
    bool Algorithms::bfs(const std::vector<std::vector<int>> &matrix, int start)
    {
        int n = matrix.size();
        std::vector<bool> visited(n, false);
        std::queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int i = 0; i < n; ++i)
            {
                if (matrix[node][i] && !visited[i])
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

    bool Algorithms::isCycleUtil(const std::vector<std::vector<int>> &matrix, int v, std::vector<bool> &visited, std::vector<int> &cyclePath, std::vector<bool> &recStack, int parent)
    {
        visited[v] = true;
        recStack[v] = true;
        cyclePath.push_back(v);

        for (int i = 0; i < static_cast<int>(matrix.size()); ++i)
        {
            if (matrix[v][i])
            {
                if (!visited[i] && isCycleUtil(matrix, i, visited, cyclePath, recStack, v))
                {
                    return true;
                }
                else if (recStack[i] && i != parent) // Check if it's a back edge but not to the parent
                {
                    // Cycle found, extract the cycle path
                    auto startIt = std::find(cyclePath.begin(), cyclePath.end(), i);
                    cyclePath.erase(cyclePath.begin(), startIt);
                    return true;
                }
            }
        }
        recStack[v] = false;
        cyclePath.pop_back();
        return false;
    }

    std::string Algorithms::isContainsCycle(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        if (n == 0)
        {
            // Handle empty graph
            return "No negative cycle found";
        }
        std::vector<bool> visited(n, false);
        std::vector<int> cyclePath;
        std::vector<bool> recStack(n, false);

        for (int i = 0; i < n; ++i)
        {
            if (!visited[i])
            {
                if (isCycleUtil(matrix, i, visited, cyclePath, recStack, -1)) // Pass -1 as the parent for the root
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
        for (int i = 0; i < color.size(); ++i)
        {
            if (color[i] == 0)
                A.push_back(i);
            else if (color[i] == 1)
                B.push_back(i);
        }

        std::string result = "The graph is bipartite: A={";
        for (size_t i = 0; i < A.size(); ++i)
        {
            result += std::to_string(A[i]);
            if (i < A.size() - 1)
                result += ", ";
        }
        result += "}, B={";
        for (size_t i = 0; i < B.size(); ++i)
        {
            result += std::to_string(B[i]);
            if (i < B.size() - 1)
                result += ", ";
        }
        result += "}";
        return result;
    }

    std::string Algorithms::isBipartite(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<int> color(n, -1);
        if (n == 0)
        {
            // Handle empty graph
            return "The graph is not bipartite";
        }

        for (int i = 0; i < n; ++i)
        {
            if (color[i] == -1)
            { // If this component isn't colored yet
                if (!checkBipartite(matrix, color, i))
                {
                    return "The graph is not bipartite.";
                }
            }
        }

        return buildBipartiteResult(color);
    }

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
    bool Algorithms::checkBipartite(const std::vector<std::vector<int>> &matrix, std::vector<int> &color, int start)
    {
        std::queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int v = 0; v < matrix.size(); ++v)
            {
                if (matrix[u][v] != 0)
                { // There is an edge
                    if (color[v] == -1)
                    {                            // If not colored
                        color[v] = 1 - color[u]; // Color with opposite color
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

    std::string Algorithms::negativeCycle(const Graph &g)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        std::vector<int> dist, prev;
        if (n == 0)
        {
            // Handle empty graph
            return "No negative cycle found";
        }

        if (!bellmanFord(matrix, 0, dist, prev))
        {
            // Find and construct the negative cycle path
            for (int u = 0; u < n; ++u)
            {
                for (int v = 0; v < n; ++v)
                {
                    if (matrix[u][v] != 0 && dist[u] + matrix[u][v] < dist[v])
                    {
                        std::vector<int> cycle;
                        int x = v;
                        do
                        {
                            cycle.push_back(x);
                            x = prev[x];
                        } while (x != v);
                        cycle.push_back(v);
                        std::reverse(cycle.begin(), cycle.end());

                        return "Negative cycle found: " + constructPath(cycle);
                    }
                }
            }
        }

        return "No negative cycle found";
    }

    std::string Algorithms::shortestPath(const Graph &g, int start, int end)
    {
        const std::vector<std::vector<int>> &matrix = g.getAdjacencyMatrix();
        int n = matrix.size();
        if (n == 0)
        {
            // Handle empty graph
            return "No shortest path in empty graph";
        }

        // Check if start and end vertices are valid
        if (start < 0 || start >= n || end < 0 || end >= n)
        {
            return "Invalid start or end vertex."; // Return an error message for invalid vertices
        }

        // Check for negative cycles using the existing negativeCycle function
        std::string negativeCycleResult = negativeCycle(g);
        if (negativeCycleResult.find("Negative cycle found") != std::string::npos)
        {
            // If a negative cycle is found, shortest path cannot be determined
            return "Negative cycle detected, shortest path not defined.";
        }

        if (g.NegativeEdges)
        {
            // Use Bellman-Ford algorithm for graphs with negative edges
            std::vector<int> dist(n, std::numeric_limits<int>::max());
            std::vector<int> prev(n, -1);

            if (!bellmanFord(matrix, start, dist, prev))
            {
                // Negative cycle detected, return appropriate message
                return "Negative cycle detected, shortest path not defined.";
            }

            // Reconstruct the shortest path
            std::vector<int> path;
            int current = end;
            while (current != -1)
            {
                path.push_back(current);
                current = prev[current];
            }
            std::reverse(path.begin(), path.end());

            return constructPath(path);
        }
        else
        {
            // Use Dijkstra's algorithm for graphs without negative edges
            std::vector<int> prev = dijkstra(matrix, start);

            // Reconstruct the shortest path if it exists
            if (prev[end] == -1)
            {
                return "-1"; // No path exists between start and end vertices
            }
            else
            {
                // Reconstruct the shortest path
                std::vector<int> path;
                int current = end;
                while (current != -1)
                {
                    path.push_back(current);
                    current = prev[current];
                }
                std::reverse(path.begin(), path.end());

                return constructPath(path);
            }
        }
    }

    bool Algorithms::bellmanFord(const std::vector<std::vector<int>> &matrix, int source, std::vector<int> &dist, std::vector<int> &prev)
    {
        int n = matrix.size();
        dist.assign(n, std::numeric_limits<int>::max());
        prev.assign(n, -1);

        dist[source] = 0; // Initialize the source vertex distance to zero

        // Relax all edges |V-1| times
        for (int i = 0; i < n - 1; ++i)
        {
            for (int u = 0; u < n; ++u)
            {
                for (int v = 0; v < n; ++v)
                {
                    if (matrix[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + matrix[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + matrix[u][v];
                        prev[v] = u;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int u = 0; u < n; ++u)
        {
            for (int v = 0; v < n; ++v)
            {
                if (matrix[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + matrix[u][v] < dist[v])
                {
                    // Negative cycle detected
                    return false;
                }
            }
        }

        return true; // No negative cycles found
    }

    std::vector<int> Algorithms::dijkstra(const std::vector<std::vector<int>> &matrix, int start)
    {
        int n = matrix.size();
        std::vector<int> dist(n, INT_MAX);
        std::vector<int> prev(n, -1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u])
                continue;

            for (int v = 0; v < n; ++v)
            {
                if (matrix[u][v] != 0)
                {
                    int new_dist = dist[u] + matrix[u][v];
                    if (new_dist < dist[v])
                    {
                        dist[v] = new_dist;
                        prev[v] = u;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        return prev; // Return the vector of predecessors
    }
} // namespace ariel