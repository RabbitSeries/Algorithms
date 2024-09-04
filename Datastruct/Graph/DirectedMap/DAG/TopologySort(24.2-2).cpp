#include<vector>
#include<queue>
#include<map>
#include<algorithm>
typedef struct nodeInfo {
    std::vector<int> nextVList;
    std::vector<int> edgeWList;
    int inDegree = 0;
}nodeInfo;

#define vmaxn 100
#define _UNREACHABLE 1<<30
std::vector<nodeInfo> graph(vmaxn);
std::queue<int> searchQue;
std::vector<int> sortIndex;
std::vector<int> dis;
std::vector<std::vector<int>> pre; // No deprecated pre id will be stacked, just use vector.
void createGraph(int nodeN, int s[], int d[], int dis[]) {
    for(int i = 0; i < nodeN; i++) {
        graph[s[i]].nextVList.push_back(d[i]);
        graph[s[i]].edgeWList.push_back(d[i]);
        graph[d[i]].inDegree++;
    }
}

bool topologySort(int vcnt) {
    for(int i = 0; i < vcnt; i++) {
        if(graph[i].inDegree == 0) {
            searchQue.push(i);
        }
    }
    while(!searchQue.empty()) {
        int nextV = searchQue.front();
        searchQue.pop();
        sortIndex.push_back(nextV);

        int nextN = graph[nextV].nextVList.size();
        for(int i = 0; i < nextN; i++) {
            int nextID = graph[nextV].nextVList[i];
            graph[nextID].inDegree--;
            if(graph[nextID].inDegree == 0) {
                searchQue.push(nextID);
            }
        }
    }
    if(sortIndex.size() == vcnt)return true; else return false;
}

void bellman_ford_after_topology(int source) {
    std::fill(dis.begin(), dis.end(), _UNREACHABLE);
    dis[source] = 0;
    std::for_each(pre.begin(), pre.end(), [](std::vector<int> preList) {
        preList.clear();
    });
    for(int i = 0; i < sortIndex.size() - 1; i++) { // <path to s> <path from s to {v | for v that s can reach}>
        int topIndex = sortIndex[i];
        auto nextVList = graph[topIndex].nextVList;
        auto edgeWList = graph[topIndex].edgeWList;
        for(int j = 0; j < nextVList.size(); j++) {
            auto nextV = nextVList[j];
            if(dis[nextV] != _UNREACHABLE && dis[nextV] > dis[topIndex] + edgeWList[topIndex]) {
                dis[nextV] = dis[topIndex] + edgeWList[topIndex];
                pre[nextV].clear();
                pre[nextV].push_back(topIndex);
            }
            else if(dis[nextV] != _UNREACHABLE && dis[nextV] == dis[topIndex] + edgeWList[topIndex]) {
                pre[nextV].push_back(topIndex);
            }
        }
    }

}

int main() {
    return 0;
}