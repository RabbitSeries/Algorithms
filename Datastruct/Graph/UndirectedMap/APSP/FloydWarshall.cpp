// Tripple loop, ijk, point-point-point relax.
// Undirected Graph APSP (All-paris shortest path)
#include <vector>
#define VMAXN 200   // O(V^3)
#define UNREACHABLE 1<<30
#define ISREACHABLE(dis) dis<UNREACHABLE?true:false

int vmax = VMAXN;
std::vector<std::vector<int>> graph(vmax, std::vector<int>(vmax, UNREACHABLE));
// std::vector<bool> visited(vmax,false);
void createGraph(std::vector<int> start, std::vector<int>end, std::vector<int> distance) {
    for (int i = 0; i < vmax; i++) {
        graph[i][i] = 0;
    }
    for (int i = 0; i < start.size(); i++) {
        graph[start[i]][end[i]] = distance[i];
        graph[end[i]][start[i]] = distance[i];
    }
}

void floyd() {
    for (int i = 0; i < vmax; i++) {
        for (int j = 0; j < vmax; j++) {
            for (int k = 0; k < vmax; k++) {
                if (ISREACHABLE(graph[i][k]) && ISREACHABLE(graph[k][j]) && graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}