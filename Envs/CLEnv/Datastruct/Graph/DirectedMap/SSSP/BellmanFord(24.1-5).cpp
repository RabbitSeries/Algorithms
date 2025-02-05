/**
 * @file 24.1-4.cpp Introduction to Algorithms Practice
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-09-04
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define _UNREACHEABLE 1<<30
#define vcnt 100


std::vector<std::vector<std::pair<int, int>>> graph(vcnt);
std::vector<int> dis(vcnt, _UNREACHEABLE);
std::vector<std::set<int>> pre(vcnt);                       // Shortest path tree.

int  bellman_ford_minEdge(int v) {// O(VE), O(V + (V-1)E + VE + E) = O(V(1+2E))
    std::fill(dis.begin(), dis.end(), _UNREACHEABLE);
    dis[0] = 0;

    // Perform |V| - 1 times relax to each edge which guarantees every shortest path form source to desitination (which has less than |V| - 1 edges) to be relaxed in a traversal sequential order.
    for(int traversal = 0; traversal < vcnt - 1; traversal++) { // Each i-th traversal relaxes (more than) the i-th edge in each shortest path. So after |V| - 1 times traversal, the sequential order traversal is at least performed once.
        bool relaexed = false;
        for(int i = 0; i < graph.size(); i++) {
            auto nextVList = graph[i];
            for(auto [nextV, edgeW] : nextVList) {
                if(dis[i] != _UNREACHEABLE && dis[nextV] > dis[i] + edgeW) {
                    dis[nextV] = dis[i] + edgeW;
                    relaexed = true;                            // During each traversal, if no relax procedure is performed, all shortest paths have been found.
                    pre[nextV].clear();
                    pre[nextV].emplace(i);
                } else if(dis[i] != _UNREACHEABLE && dis[nextV] == dis[i] + edgeW) {
                    pre[nextV].emplace(i);
                }
            }
        }
        if(!relaexed) break;
    }

    int minEdge = _UNREACHEABLE;
    for(int i = 0; i < graph.size(); i++) { // Continue to perform edge relaxation traversal to find all post-negative-cycle vertexes.
        // Suppose a shortest path from s to v, : <s to v> <v to others>
        // To obtain min{u to v for u in V}, just calculate min{u to v for u as start point of an edge}
        auto nextVList = graph[i];
        for(auto [nextV, edgeW] : nextVList) {
            if(nextV == v && edgeW < minEdge) {
                minEdge = edgeW;
            }
        }
    }

    return minEdge;
}
