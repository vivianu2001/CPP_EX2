/*
ID : 322880857
GMAIL : Umanskyvivian@gmail.com
*/
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>

namespace ariel
{
    class Algorithms
    {
    public:
        static bool isConnected(const Graph &Graph);
        static bool isStronglyConnected(const Graph &Graph);
        static std::string shortestPath(const Graph &Graph, int start, int end);

        static std::string isContainsCycle(const Graph &Graph);
        static std::string isBipartite(const Graph &Graph);
        static std::string negativeCycle(const Graph &Graph);

    private:
        static bool isCycleUtil(const std::vector<std::vector<int>> &matrix, size_t v, std::vector<bool> &visited, std::vector<int> &cyclePath,
                                std::vector<bool> &recStack, size_t parent);
        static void dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, size_t node);
        static bool bfs(const std::vector<std::vector<int>> &matrix, size_t start);
        static bool checkBipartite(const std::vector<std::vector<int>> &matrix, std::vector<int> &color, size_t start);
        static std::string buildBipartiteResult(const std::vector<int> &color);
        static bool bellmanFord(const std::vector<std::vector<int>> &matrix, int source, std::vector<int> &dist, std::vector<int> &prev);
        static std::vector<int> dijkstra(const std::vector<std::vector<int>> &matrix, int start);
        static std::string constructPath(const std::vector<int> &path);
        static std::string constructPathFromPrev(const std::vector<int> &prev, int end, size_t start);
        static std::vector<std::vector<int>> createUndirectedMatrix(const std::vector<std::vector<int>> &directedMatrix);
    };
}

#endif /* ALGORITHMS_HPP */