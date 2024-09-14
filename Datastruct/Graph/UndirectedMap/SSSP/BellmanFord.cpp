// Undirected graph, SSSP (single source shortest path).
// O(VE)
#include<vector>
#define VMAXN 200
#define UNREACHABLE 1<<30
int vmax = VMAXN;
typedef struct edgeInfo {
    int nextV;
    int edgeW;
} edgeInfo;

std::vector<std::vector<edgeInfo>> graph(vmax);
std::vector<int> dis(vmax, UNREACHABLE);

bool bellmanFord_negativeRing(int s) {
    std::fill(dis.begin(), dis.end(), UNREACHABLE);
    dis[s] = 0;
    for (int edgeTraversal = 0; edgeTraversal < vmax - 1; edgeTraversal++) {
        for (int i = 0; i < vmax; i++) {
            std::vector<edgeInfo> nextVList = graph[i];
            for (int j = 0; j < nextVList.size(); j++) {
                int nextV = nextVList[j].nextV;
                int edgeW = nextVList[j].edgeW;
                if (dis[i] < UNREACHABLE && dis[i] + edgeW < dis[nextV]) {
                    dis[nextV] = dis[i] + edgeW;
                }
            }
        }
    }

    for (int edgeTraversal = 0; edgeTraversal < vmax - 1; edgeTraversal++) {
        for (int i = 0; i < vmax; i++) {
            std::vector<edgeInfo> nextVList = graph[i];
            for (int j = 0; j < nextVList.size(); j++) {
                int nextV = nextVList[j].nextV;
                int edgeW = nextVList[j].edgeW;
                if (dis[i] < UNREACHABLE && dis[i] + edgeW < dis[nextV]) {
                    return true;
                }
            }
        }
    }
    return false;
}
