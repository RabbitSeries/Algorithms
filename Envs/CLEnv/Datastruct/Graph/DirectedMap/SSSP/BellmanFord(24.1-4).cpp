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

bool  bellman_ford_setUnreachableNode() {// O(VE), O(V + (V-1)E + VE + E) = O(V(1+2E))
    bool hasNegativeCycle = false;
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
        if(!relaexed) return false;                             // If there is a negative cycle in the graph, relaxed should always be true. So there won't be a negative cycle if relaxed is false.
    }

    for(int traversal = 0; traversal < vcnt; traversal++) { // Continue to perform edge relaxation traversal to find all post-negative-cycle vertexes.
        // Suppose a path among those start from source and have a negative cycle in it: <s,v_1> <v_1, v2> ... <v_k, ng_1> <ng_1 ... ng_1> <ng_1 v_m> <v_m ... v_n>
        // If take the nagetive cycle <ng_1 ... ng_1> as a zoro weight edge" <s,v_1> <v_1, v2> ... <v_k, ng_1> <ng_1 ng_1> <ng_1 v_m> v_m ... v_n>
        // Then there is no negative cycle in the path from source s to v_n.
        // So after performming the same analogization to the paths that have nagative cycles, the must exist a shortest path from s to ng_1 and from ng_1 to all its reachable vetexes:
        // <shortest path from s to ng_1> <ng_1 ... ng_1> <shortest path from ng_1 to {NGV}>
        // Note that s can be ng_1, {NGV} can be empty, so <ng_1 ... ng_1> can have |V| edges.
        // So i-th traversal will skip those edges in the shortest path befre ng_1, and visit each i-th edge in both negative cycle <ng_1 ... ng_1> and <shortest path from ng_1 to {NGV}>.
        // Then mark those edges and perform relaxation so that {i+1}-th edge will at least be relaxed in the next traversal.
        // At the end of each traversal, mark the start vertexes of those edges as UNREACHABLE.
        std::vector<int> setList;
        for(int i = 0; i < graph.size(); i++) {
            auto nextVList = graph[i];
            for(auto [nextV, edgeW] : nextVList) {
                if(dis[i] != _UNREACHEABLE && dis[nextV] > dis[i] + edgeW) {
                    dis[nextV] = dis[i] + edgeW;                // This time, if
                    setList.push_back(i);
                    hasNegativeCycle = true;
                }
            }
        }
        if(!hasNegativeCycle) return false;
        std::for_each(setList.begin(), setList.end(), [](int i) {
            dis[i] = _UNREACHEABLE;
        });
    }
    // At last set those end vertexes of edges with UNREACHABLE start vertex to UNREACHABLE.
    for(int i = 0; i < graph.size(); i++) {
        auto nextVList = graph[i];
        for(auto [nextV, edgeW] : nextVList) {
            if(dis[i] == _UNREACHEABLE) {
                dis[nextV] = _UNREACHEABLE;
            }
        }
    }
    return true;
}
