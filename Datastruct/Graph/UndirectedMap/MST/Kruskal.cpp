// Edge greedy, union search set.
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#define vmax 100
int vcnt = vmax;

typedef struct edgeInfo {
    edgeInfo(int _edgeW) : edgeW(_edgeW) {};
    int nextV;
    int edgeW;
    bool visited = false;
}edgeInfo;

typedef struct nodeInfo {
    std::vector<edgeInfo> outEdgeList;
}nodeInfo;

std::vector<nodeInfo> graph(vcnt);

std::vector<int> father(vcnt);

typedef struct mstNode {
    std::vector<int> outEdgeList;
    int inDegree = 0;
}mstNode;

std::vector<mstNode> mstTree(vcnt);
std::vector<int> mstPre(vcnt);

int findFather(int s) {
    if (s = father[s]) return s;
    else {
        father[s] = findFather(father[s]);
        return father[s];
    }
}

void addToSet(int s, int des) {
    father[des] = findFather(s);
}

void Kruskal() {
    for_each(graph.begin(), graph.end(), [](nodeInfo node) {
        for_each(node.outEdgeList.begin(), node.outEdgeList.end(), [](edgeInfo edge) {
            edge.visited = false;
        });
    });
    for (int i = 0; i < vcnt; i++) {
        father[i] = i;
    }
    for (int EdgeTraversal = 0; EdgeTraversal < vcnt - 1; EdgeTraversal++) {
        int minEdgeSourceNode = -1, edgeIndex = -1;
        edgeInfo minEdge(1 << 30);
        for (int i = 0; i < vcnt; i++) {
            std::vector<edgeInfo> edgeList = graph[i].outEdgeList;
            for (int j = 0; j < edgeList.size(); j++) {
                edgeInfo edge = edgeList[j];
                if (!edge.visited && edge.edgeW < minEdge.edgeW) {
                    minEdgeSourceNode = i;
                    edgeIndex = j;
                    minEdge = edge;
                }
            }
        }
        if (minEdgeSourceNode == -1) return;

        graph[minEdgeSourceNode].outEdgeList[edgeIndex].visited = true;

        int nextV = graph[minEdgeSourceNode].outEdgeList[edgeIndex].nextV;
        if (findFather(minEdgeSourceNode) != findFather(nextV)) {
            addToSet(minEdgeSourceNode, nextV);
            // Once found the minimal edge in the unvisited edge-set, add it directly to the mstTree.
            mstTree[minEdgeSourceNode].outEdgeList.push_back(nextV);
            mstTree[nextV].inDegree++;
        }
    }
}

void mstTraverse() {
    int start = -1;
    for (int i = 0; i < vcnt; i++) {
        if (mstTree[i].inDegree == 0) {
            start = i;
            break;
        }
    }
    std::queue<int> printQue;
    printQue.push(start);
    while (!printQue.empty()) {
        int levelSize = printQue.size();
        for (int i = 0; i < levelSize; i++) {
            int parent = printQue.front();
            printQue.pop();
            std::cout << parent << " ";
            for (int j = 0; j < mstTree[parent].outEdgeList.size(); j++) {
                printQue.push(mstTree[parent].outEdgeList[j]);
            }
        }
        std::cout << std::endl;
    }
}