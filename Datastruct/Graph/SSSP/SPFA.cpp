#include <bits/stdc++.h>
int vcnt = 100;

typedef struct edgeInfo {
    int nextV;
    int edgeW;
} edgeInfo;

typedef struct nodeInfo {
    std::vector<edgeInfo> nextVList;
} nodeInfo;

std::vector<nodeInfo> graph(vcnt);
std::vector<int> dis(vcnt,1<<30);
std::vector<bool> inQueue(vcnt,false);
std::vector<int> inQueueTimes(vcnt,0);

bool SPFA(int s) {
    dis[s]=0;
    std::fill(inQueueTimes.begin(),inQueueTimes.end(),0);
    std::fill(inQueue.begin(),inQueue.end(),false);

    std::queue<int> relaxVQ;
    relaxVQ.push(s);
    inQueue[s] = true;
    inQueueTimes[s]++;
    while(!relaxVQ.empty()) {
        int node = relaxVQ.front();
        relaxVQ.pop();
        inQueue[node] = 0;
        std::vector<edgeInfo> nextVList = graph[node].nextVList;
        for(int i = 0 ; i < nextVList.size(); i++) {
            int nextV = nextVList[i].nextV;
            int edgeW = nextVList[i].edgeW;
            if(! inQueue[nextV] && dis[node] + edgeW < dis[nextV]) {
                relaxVQ.push(nextV);
                inQueue[nextV] = true;
                inQueueTimes[nextV]++;
                if(inQueueTimes[nextV] > vcnt - 1) {
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
