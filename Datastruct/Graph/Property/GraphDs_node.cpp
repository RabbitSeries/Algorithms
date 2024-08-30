#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;
int vmax = 100;
int nodeN = vmax;


typedef struct edgeInfo {
    int nextV;  // Next vertex index.
    int edgeW;  // Weight of the edge.
    bool visited;
} edgeInfo;

typedef struct nodeInfo {
    vector<edgeInfo> outEdgeList;     // Index List of adjacent nodes.
    vector<int> preEdgeList;     // Index List of adjacent nodes.
    int outDegree = 0;               // inDegree of this node.
    int inDegree = 0;               // inDegree of this node.
    int nodeW;
} nodeInfo;

typedef struct nodeInfo_Complex {
    std::vector<int> nextV;
    std::vector<int> edgeW;
    int inDegree = 0;
    int nodeW;
}nodeInfo_Complex;

#define AL
#ifdef AL
// Adjacency List
vector<nodeInfo> graph(vmax);
#else
// Adjacency Matrix
vector<vector<int>> graph(vmax, vector<int>(vmax, 1 << 31));
vector<int> nodeInDegree(vmax, 0);
vector<int> nodeWeight(vmax);
vector<vector<int>> preNodeList(vmax);
#endif

