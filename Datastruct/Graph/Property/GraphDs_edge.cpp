#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
int emax = 100;
int edgeN = emax;

typedef struct edgeInfo {
    int startV;
    int nextV;
    int edgeW;
}edgeInfo;

std::vector<edgeInfo> graph(emax);

std::vector<bool> visited(emax,false);

