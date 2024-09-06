#include <vector>
#include <queue>
#include "../../DirectedMap/DAG/headertest.h"
using namespace std;
class Solution {
public:

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<vector<pair<int, double>>> nextVList(n);
        vector<bool> visitedR(n, false);
        vector<double> multiProb(n, 0);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> multiProbPQ;
        for(int i = 0; i < edges.size(); i++) {
            if(edges[i][0] != end_node && edges[i][1] != start_node)
                nextVList[edges[i][0]].push_back(pair<int, double>(edges[i][1], succProb[i]));
            if(edges[i][1] != end_node && edges[i][0] != start_node)
                nextVList[edges[i][1]].push_back(pair<int, double>(edges[i][0], succProb[i]));
        }
        multiProb[0] = 1;
        multiProbPQ.emplace(1, 0);
        for(int i = 0; i < n && !multiProbPQ.empty(); i++) {
            auto [maxProb, index] = multiProbPQ.top();
            visitedR[index] = true;
            for(int j = 0; j < nextVList[index].size(); j++) {
                auto [nextV, edgeW] = nextVList[index][j];
                if(!visitedR[nextV] && multiProb[index] * edgeW > multiProb[nextV]) {
                    multiProb[nextV] = multiProb[index] * edgeW;
                    multiProbPQ.emplace(multiProb[edgeW], nextV);
                }
            }
        }
        return multiProb[end_node];
    }

    // private:
        // vector<vector<pair<int, double>>> nextVList;
        // vector<int> inDegree;
        // vector<double> multiProb;
        // vector<bool> visitedR;
};

int main() {
    Solution s;
    vector<vector<int>> edges = vector<vector<int>>{ vector<int>{2,3},vector<int>{1,2},vector<int>{0,1} };
    vector<double> succProb = vector<double>{ 0.5,0.5,0.5 };
    s.maxProbability(4, edges, succProb, 0, 3);
}
