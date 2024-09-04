#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <set>
int emax = 100;
int edgeN = emax;

typedef struct edgeInfo {
    std::set<int> bilateralN;
    int startV;
    int nextV;
    int edgeW;
}edgeInfo;

std::vector<edgeInfo> graph(emax);

std::vector<bool> visited(emax,false);

