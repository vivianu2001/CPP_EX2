#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(const Graph &g);
        static bool isStronglyConnected(const Graph &g); // Add this declaration
        static std::string shortestPath(const Graph &g, int start, int end);

        static std::string isContainsCycle(const Graph &g);
        static std::string isBipartite(const Graph &g);
        static std::string negativeCycle(const Graph &g);

    private:
        static bool isCycleUtil(const std::vector<std::vector<int>> &matrix, int v, std::vector<bool> &visited, std::vector<int> &cyclePath, std::vector<bool> &recStack, int parent);
        static void dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, int node);
        static bool bfs(const std::vector<std::vector<int>> &matrix, int start);
        static bool checkBipartite(const std::vector<std::vector<int>> &matrix, std::vector<int> &color, int start);
        static std::string buildBipartiteResult(const std::vector<int> &color);
        static bool bellmanFord(const std::vector<std::vector<int>> &matrix, int source, std::vector<int> &dist, std::vector<int> &prev);
        static std::vector<int> dijkstra(const std::vector<std::vector<int>> &matrix, int start);
        static std::string constructPath(const std::vector<int> &path);
    };
}

#endif /* ALGORITHMS_HPP */