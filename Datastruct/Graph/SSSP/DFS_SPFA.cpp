#include <vector>
using namespace std;
class Solution {
public:

    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        nextVList = vector<vector<pair<int, double>>>(n);
        visitedR = vector<bool>(n, false);
        for(int i = 0; i < edges.size(); i++) {
            nextVList[edges[i][0]].push_back(pair<int, double>(edges[i][1], succProb[i]));
            nextVList[edges[i][1]].push_back(pair<int, double>(edges[i][0], succProb[i]));
        }
        multiProb = vector<double>(n, 0);
        multiProb[start_node] = 1;

        for(int traversal = 0; traversal < n - 1; traversal++) {
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < nextVList[i].size(); j++) {
                    if(multiProb[i] * nextVList[i][j].second > multiProb[nextVList[i][j].first]) {
                        multiProb[nextVList[i][j].first] = multiProb[i] * nextVList[i][j].second;
                    }
                }
            }
        }

        return multiProb[end_node];
    }

    void dfs(int s, int end) {        // dfs(start_node,end_node);
        if(s == end) return;
        visitedR[s] = true;
        for(int i = 0; i < nextVList[s].size(); i++) {
            if(visitedR[nextVList[s][i].first] == false && multiProb[s] * nextVList[s][i].second > multiProb[nextVList[s][i].first]) {
                multiProb[nextVList[s][i].first] = multiProb[s] * nextVList[s][i].second;
                dfs(nextVList[s][i].first,end);
            }
        }
        visitedR[s] = false;
        return;
    }
private:
    vector<vector<pair<int, double>>> nextVList;
    vector<double> multiProb;
    vector<bool> visitedR;
};