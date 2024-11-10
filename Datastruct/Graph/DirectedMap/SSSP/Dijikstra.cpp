// Undirected Simple graph,Undirected cyclic/acyclic graph, SSSP.
// Note that, perform every dijikstra algorithm to every node in the graph, we can still have the APSP result, specifically in scattered graph.
// Dijikstra algorithm can't be used as a ring judgement method.
// In the standard Dijkstra algorithm, once a node is processed (marked as visited), it is added to the set S, and no further relaxation is performed on it.
// In the priority_queue-optimized Dijkstra algorithm, nodes are implicitly separated into sets S and V-S based on whether they have been relaxed and added to the queue.
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
int vmax = 100;
int nodeN = vmax;
typedef struct edgeInfo {
    int nextV;
    int edgeW;
} edgeInfo;

typedef struct nodeInfo {
    std::vector<edgeInfo> outEdgeList;
} nodeInfo;

#define AL

#ifdef AL
// Adjacency List
vector<nodeInfo> graph(vmax);
#else
// Adjacency Matrix
vector<vector<int>> graph(vmax, vector<int>(vmax, 1 << 31));
#endif

// vector<bool> vis(vmax, false);
// vector<int> dis(vmax, 1 << 31);// This will disable the highlight
vector<int> dis(vmax, 1 << 31 >> 0);
vector<vector<int>> pre(vmax);
// Element is sorted in greater order one by one, sort(function<e,e>->void cmp) accepts sorting function which true swaps two elememts, puts second element before first element.
// Max heap with default parameter declaration.
// When using priority_queue<pair<int, int>> without explicitly specifying parameters,
// it defaults to priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>>,
// which creates a max heap based on the pair's first element, and second element if needed.
priority_queue<pair<int, int>> traversal;
priority_queue<pair<int, int> , vector<pair<int,int>>, greater<>> traversal;
// queue<int> path;
// vector<queue<int>> paths;
vector<vector<vector<int>>> paths(vmax);

void dijikstra(int s) {
    dis[s] = 0;
    traversal.emplace(0, s);
    paths[s].push_back(vector<int>(1, s));
    while (!traversal.empty()) {
        auto [minDis, minId] = traversal.top();
        traversal.pop();
        // Shorter path has been obtained, and equal path's info is recorded in datastruct.
        if (dis[minId] <= minDis) {
            continue;
        }
        // vis[minId] = true;// Set as visited making the node unable to be relaxed as a <nextV> thereafter.
        vector<vector<int>> minIdPath = paths[minId];
        for (int i = 0; i < graph[minId].outEdgeList.size(); i++) {
            int relaxId = graph[minId].outEdgeList[i].nextV;
            int edgeW = graph[minId].outEdgeList[i].edgeW;
            vector<vector<int>>& relaxPaths = paths[relaxId];
            // if (!vis[relaxId]) {
            if (dis[minId] + edgeW < dis[relaxId]) {
                dis[relaxId] = dis[minId] + edgeW;
                relaxPaths.clear();
                relaxPaths = minIdPath;
                for_each(relaxPaths.begin(), relaxPaths.end(), [ = ](vector<int> path) {
                    path.push_back(relaxId);
                });
            }
            else if (dis[minId] + edgeW == dis[relaxId]) {
                // Within V-S set, one node align a edge are not used to relax the other, such that all paths in minIdPath should be added into relaxId's path and there will be no deprecated paths.
                for_each(minIdPath.begin(), minIdPath.end(), [ &, minIdPath ](vector<int> path) {
                    vector<int> tempPath = path;
                    tempPath.push_back(relaxId);
                    relaxPaths.push_back(tempPath);
                });
            }
        }
    }
}

void printPath(int des) {
    for_each(paths[des].begin(), paths[des].end(), [](vector<int> sPath) {
        for (int i = 0; i < sPath.size(); i++) {
            std::cout << sPath[i] << " ";
        }
        std::cout << std::endl;
    });
}

int main() {
    return 0;
}
