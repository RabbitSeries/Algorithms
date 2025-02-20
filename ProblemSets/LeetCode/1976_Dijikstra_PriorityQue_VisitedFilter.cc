#include "bits/stdc++.h"
using namespace std;
class Solution {
public:
    using ll = long long;
    const int MOD = 1e9 + 7; // Modulo value for the number of paths.
    int countPaths( int n, vector<vector<int>> roads ) {// Graph represented as adjacency list, where g[u] holds pairs (v, t) for edge u-v with travel time t.
        vector<vector<pair<int, ll>>> graph( n );// Build the graph from road information.
        for( auto& road : roads ) {
            graph[road[0]].emplace_back( road[1], road[2] );
            graph[road[1]].emplace_back( road[0], road[2] );
        }
        vector<ll> distances( n, LLONG_MAX );// Initialize distances array with infinite distances and set start node distance to 0.
        vector<ll> ways( n, 0 );// Ways array to hold the number of ways to reach each node.
        vector<bool> visited( n, false );// Visited array to keep track of visited nodes.
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;// Using priority queue to hold pairs of (distance, node), for getting the next closest unvisited node.
        distances[0] = 0;   // Initialize starting values for node 0.
        ways[0] = 1;        // Initialize starting ways for node 0.
        pq.push( { 0, 0 } );
        while( !pq.empty() ) {  // Dijkstra's algorithm for shortest paths.
            auto [distance, u] = pq.top();
            pq.pop();
            if( visited[u] )
                continue;
            visited[u] = true;
            for( auto& [v, t] : graph[u] ) {// Iterate over all neighbors of the current node.
                assert( distances[u] == distance );
                ll nextDistance = distances[u] + t;
                if( distances[v] > nextDistance ) {// If a shorter path is found, update distance and ways.
                    distances[v] = nextDistance;
                    ways[v] = ways[u];
                    pq.push( { nextDistance, v } );
                } else if( distances[v] == nextDistance ) {// If an equal distance path is found, add ways.
                    ways[v] = ( ways[v] + ways[u] ) % MOD;
                }
            }
        }
        return ways[n - 1];// Return the number of ways to reach the last node.
    }
};
