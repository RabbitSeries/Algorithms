#include "bits/stdc++.h"
#include "climits"
using namespace std;
class Solution {
public:
public:
    typedef long long ll;
    // Constants for the problem limits.
    const ll INF = LLONG_MAX / 2; // Define infinity as half the maximum value to avoid overflow.
    const int MOD = 1e9 + 7; // Modulo value for the number of paths.

    int countPaths(int n, vector<vector<int>>& roads) {
        // Graph represented as adjacency list, where g[u] holds pairs (v, t) for edge u-v with travel time t.
        vector<vector<pair<int, ll>>> graph(n);
        // Initialize distances array with infinite distances and set start node distance to 0.
        vector<ll> distances(n, INF);
        // Ways array to hold the number of ways to reach each node.
        vector<ll> ways(n, 0);
        // Visited array to keep track of visited nodes.
        vector<bool> visited(n, false);

        // Build the graph from road information.
        for(auto& road : roads) {
            int u = road[0], v = road[1];
            ll t = road[2];
            graph[u].emplace_back(v, t);
            graph[v].emplace_back(u, t);
        }

        // Using priority queue to hold pairs of (distance, node), for getting the next closest unvisited node.
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

        // Initialize starting values for node 0.
        distances[0] = 0;
        ways[0] = 1;
        pq.push({ 0, 0 });

        // Dijkstra's algorithm for shortest paths.
        while(!pq.empty()) {
            auto [distance, u] = pq.top();
            pq.pop();
            if(visited[u])
                continue;
            visited[u] = true;

            // Iterate over all neighbors of the current node.
            for(auto& [v, t] : graph[u]) {
                ll nextDistance = distances[u] + t;
                // If a shorter path is found, update distance and ways.
                if(distances[v] > nextDistance) {
                    distances[v] = nextDistance;
                    ways[v] = ways[u];
                    pq.push({ nextDistance, v });
                    // If an equal distance path is found, add ways.
                } else if(distances[v] == nextDistance) {
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }

        // Return the number of ways to reach the last node.
        return ways[n - 1];
    }
};
