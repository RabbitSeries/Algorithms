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
#include <iostream>
#include <queue>
#include <algorithm>
#define _UNREACHEABLE 1<<30
#define vcnt 100


std::vector<std::vector<std::pair<int, int>>> graph = { std::vector<std::pair<int,int>>{std::pair<int,int>(1,1)},
std::vector<std::pair<int,int>>{std::pair<int,int>(2,1),std::pair<int,int>(4,1)},
std::vector<std::pair<int,int>>{std::pair<int,int>(3,1)},
std::vector<std::pair<int,int>>{std::pair<int,int>(1,-3)},
std::vector<std::pair<int,int>>()
};
std::vector<int> dis(vcnt, _UNREACHEABLE);
std::vector<int> cyclePath;
bool  bellman_ford_findRingPath() {// O(VE), O(V + (V-1)E + VE + E) = O(V(1+2E))
    std::fill(dis.begin(), dis.end(), _UNREACHEABLE);
    dis[0] = 0;
    // Perform |V| - 1 times relax to each edge which guarantees every shortest path form source to desitination (which has less than |V| - 1 edges) to be relaxed in a traversal sequential order.
    for(int traversal = 0; traversal < vcnt - 1; traversal++) { // Each i-th traversal relaxes (more than) the i-th edge in each shortest path. So after |V| - 1 times traversal, the sequential order traversal is at least performed once.
        for(int i = 0; i < graph.size(); i++) {
            auto nextVList = graph[i];
            for(auto [nextV, edgeW] : nextVList) {
                if(dis[i] != _UNREACHEABLE && dis[nextV] > dis[i] + edgeW) {
                    dis[nextV] = dis[i] + edgeW;
                }
            }
        }
    }
    int beginCycle = -1;
    for(int i = 0; i < graph.size(); i++) {
        auto nextVList = graph[i];
        for(auto [nextV, edgeW] : nextVList) {
            if(dis[i] != _UNREACHEABLE && dis[nextV] > dis[i] + edgeW) {
                beginCycle = i;
                break;
            }
        }
        if(beginCycle != -1) break;
    }
    void dfs(int begin);
    if(beginCycle != -1)
        dfs(beginCycle);
    else return false;
    if(cyclePath.size() > 2 && cyclePath.front() == cyclePath.back()) return true;
    return false;
}

void dfs(int begin) {
    cyclePath.push_back(begin);
    if(cyclePath.size() > 2 && cyclePath.front() == cyclePath.back()) return;
    auto nextVList = graph[begin];
    for(auto [nextV, edgeW] : nextVList) {
        if(dis[begin] < _UNREACHEABLE && dis[nextV] > dis[begin] + edgeW) {
            dis[nextV] = dis[begin] + edgeW;
            dfs(nextV);
            if(cyclePath.size() > 2 && cyclePath.front() == cyclePath.back()) return;
        }
    }
    cyclePath.pop_back();
    return;
}

void printCycle() {
    std::for_each(cyclePath.begin(), cyclePath.end() - 1, [](int index) {
        std::cout << index << " ";
    });
    return;
}

int main() {
    if(bellman_ford_findRingPath())printCycle();
    return 0;
}