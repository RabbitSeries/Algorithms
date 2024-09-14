// Undirected Simple graph,Undirected cyclic/acyclic graph, SSSP.
// Note that, perform every dijikstra algorithm to every node in the graph, we can still have the APSP result, specifically in scattered graph.
// Dijikstra algorithm can't be used as a ring judgement method.
// In the process of dijikstra minimal distance node caculation, the node found will be set as visited, thus no further relax procedure will be performed.

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

vector<bool> vis(vmax, false);
// vector<int> dis(vmax, 1 << 31);// This will disable the highlight
vector<int> dis(vmax, 1 << 31 >> 0);
vector<vector<int>> pre(vmax);
// queue<int> path;
// vector<queue<int>> paths;
vector<vector<vector<int>>> paths(vmax);

void dijikstra(int s) {
    dis[s] = 0;
    for(int i = 0; i < nodeN; i++) {
        int minId = -1, minDis = 1 << 31;
        for(int j = 0; j < nodeN; j++) {
            if(!vis[j] && dis[j] < minDis) {
                minDis = dis[j];
                minId = j;
            }
        }
        if(minId == -1) {
            return;
        }
        vis[minId] = true;// Set as visited making the node unable to be relaxed as a <nextV> thereafter.
        vector<vector<int>> minIdPath = paths[minId];
        for(int i = 0; i < graph[minId].outEdgeList.size(); i++) {
            int relaxId = graph[minId].outEdgeList[i].nextV;
            int edgeW = graph[minId].outEdgeList[i].edgeW;
            vector<vector<int>>& relaxPaths = paths[relaxId];
            if(!vis[relaxId]) {
                if(dis[minId] + edgeW < dis[relaxId]) {
                    dis[relaxId] = dis[minId] + edgeW;
                    relaxPaths.clear();
                    relaxPaths = minIdPath;
                    if(relaxPaths.empty()) relaxPaths.push_back(vector<int>(1, minId));
                    else {
                        for_each(relaxPaths.begin(), relaxPaths.end(), [ = ](vector<int> path) {
                            path.push_back(minId);
                        });
                    }
                } else if(dis[minId] + edgeW == dis[relaxId]) { // May loose the trace info.
                    if(relaxPaths.empty()) relaxPaths.push_back(vector<int>(1, minId)); // This line is actually not executed.
                    else {
                        for_each(minIdPath.begin(), minIdPath.end(), [ &, minIdPath ](vector<int> path) {
                            vector<int> tempPath = path;
                            tempPath.push_back(minId);
                            relaxPaths.push_back(tempPath);
                        });
                    }
                }
            }
        }
    }
}


// void dfs(int end, int s) {
//     path.push(end);
//     if (end == s) {
//         paths.push_back(path);
//     }
//     for (int i = 0; i < pre[end].size(); i++) {
//         dfs(pre[end][i], s);
//     }
//     path.pop();
//     return;
// }


void printPath(int des) {
    for_each(paths[des].begin(), paths[des].end(), [](vector<int> sPath) {
        for(int i = 0; i < sPath.size(); i++) {
            std::cout << sPath[i] << " ";
        }
        std::cout << std::endl;
    });
}

int main() {
    return 0;
}
