// Smaller distance first.
// Large distance first.

#include <bits/stdc++.h>
#define UNREACHABLE 1<<30
int vcnt = 100;

typedef struct edgeInfo {
    int nextV;
    int edgeW;
} edgeInfo;

typedef struct nodeInfo {
    std::vector<edgeInfo> nextVList;
    bool inQueue = false;
    int inQueueTimes = 0;
    int dis = UNREACHABLE; // Distance from source point.
} nodeInfo;

std::vector<nodeInfo> graph(vcnt);
std::vector<int> dis(vcnt, UNREACHABLE);

bool SPFA(int s) {
    dis[s] = 0;
    std::for_each(graph.begin(), graph.end(), [](nodeInfo node) {node.inQueueTimes = 0; });
    std::for_each(graph.begin(), graph.end(), [](nodeInfo node) {node.inQueue = false; });

    std::deque<int> relaxVQ;
    int queueSize = 0;
    int queueDisSum = 0;

    relaxVQ.push_back(s);
    graph[s].inQueue = true;
    graph[s].inQueueTimes++;

    queueSize++;
    queueDisSum += dis[s];

    while (!relaxVQ.empty()) {
        while (dis[relaxVQ.front()] * queueSize > queueDisSum) {
            int frontId = relaxVQ.front();
            relaxVQ.pop_front();
            relaxVQ.push_back(frontId);
        }
        int nodeIndex = relaxVQ.front();
        nodeInfo& node = graph[nodeIndex];
        relaxVQ.pop_front();
        graph[nodeIndex].inQueueTimes = 0;
        std::vector<edgeInfo> nextVList = graph[nodeIndex].nextVList;
        for (int i = 0; i < nextVList.size(); i++) {
            int nextV = nextVList[i].nextV;
            int edgeW = nextVList[i].edgeW;
            nodeInfo& nextNode = graph[nextV];
            if (!nextNode.inQueue && dis[nodeIndex] + edgeW < dis[nextV]) {
                dis[nextV] = dis[nodeIndex] + edgeW;
                if (!relaxVQ.empty() && dis[nextV] < dis[relaxVQ.back()])
                    relaxVQ.push_front(nextV);
                else
                    relaxVQ.push_back(nextV);
                nextNode.inQueue = true;
                nextNode.inQueueTimes++;
                if (nextNode.inQueueTimes > vcnt) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    return 0;
}
