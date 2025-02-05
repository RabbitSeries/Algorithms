// Point greedy, transformation form dijistra.
#include <vector>
// #include <bits/stdc++.h>
typedef struct edgeInfo {
    int nextV;
    int edgeW;
} edgeInfo;

typedef struct nodeInfo {
    std::vector<edgeInfo> outEdgeList;
    int nodeW;
} nodeInfo;

#define vmax 100

int vcnt = vmax;

std::vector<nodeInfo> graph(vmax);
std::vector<bool> visited(vmax, false);
std::vector<int> dis(vmax, 1 << 30 >> 0);

typedef struct mstNode {
    std::vector<int> outEdgeList;
} mstNode;

std::vector<mstNode> mstTree(vcnt);
std::vector<int> preNode(vcnt);

void prim(int s) {
    // std::memset() function will set value by byte, so only for bool C style array.
    std::fill(dis.begin(), dis.end(), 1 << 30);
    std::fill(preNode.begin(), preNode.end(), -1);
    dis[s] = 0;
    preNode[s] = -1;
    for (int traversal = 0; traversal < vcnt; traversal++) {
        int minId = -1, minW = 1 << 30;
        for (int i = 0; i < vcnt; i++) {
            // Find Minimal relaxed node in V-S set.
            if (!visited[i] && dis[i] < minW) {
                minId = i;
                minW = dis[i];
            }
            if (minId == -1) {
                return;
            }
            // Add into S set. And connect MST tree.
            visited[minId] = true;
            int preId = preNode[minId];
            if (preId != -1) mstTree[preId].outEdgeList.push_back(minId);
            std::vector<edgeInfo> outEdgeList = graph[minId].outEdgeList;
            for (int i = 0; i < outEdgeList.size(); i++) {
                int nextV = outEdgeList[i].nextV;
                int edgeW = outEdgeList[i].edgeW;
                if (!visited[nextV] && edgeW < dis[nextV]) {
                    dis[nextV] = edgeW;
                    preNode[nextV] = minId;
                }
            }
        }
    }
}
