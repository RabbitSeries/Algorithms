#include<vector>
typedef struct nodeInfo {
    std::vector<int> nextV;
    std::vector<int> edgeW;
    int inDegree = 0;
}nodeInfo;

#define vmaxn 100

std::vector<nodeInfo> graph(vmaxn);

void createGraph(int nodeN, int s[], int d[], int dis[]) {
    for (int i = 0; i < nodeN; i++) {
        graph[s[i]].nextV.push_back(d[i]);
        graph[s[i]].edgeW.push_back(d[i]);
        graph[d[i]].inDegree++;
    }
}

bool topologicalSort(int nodeN) {
    int counter = 0;
    int eliminate = -1;
    std::vector<bool> visited(nodeN, false);
    while (1) {
        for (int i = 0; i < nodeN; i++) {
            if (!visited[i] && !graph[i].inDegree) {
                eliminate = i;
                counter++;
                break;
            }
        }
        if (eliminate == -1) {
            if (counter == nodeN)return true; else return false;
        }
        int nextN = graph[eliminate].nextV.size();
        for (int i = 0; i < nextN; i++) {
            int nextID = graph[eliminate].nextV[i];
            graph[nextID].inDegree--;
        }
    }
}

int main() {
    return 0;
}