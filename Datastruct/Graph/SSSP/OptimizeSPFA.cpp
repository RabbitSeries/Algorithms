#include <vector>
using namespace std;
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        vector<double> multiProb(n, 0);
        multiProb[start_node] = 1;
        for(int i = 0; i < edges.size(); i++) {
            bool relaxed = false;
            for(int j = 0; j < edges.size(); j++) {
                if(multiProb[edges[j][0]] > 0 && multiProb[edges[j][0]] * succProb[j] > multiProb[edges[j][1]]) {
                    multiProb[edges[j][1]] = multiProb[edges[j][0]] * succProb[j];
                    relaxed = true;
                }
                // If the graph is an undirected map.
                if(multiProb[edges[j][1]] > 0 && multiProb[edges[j][1]] * succProb[j] > multiProb[edges[j][0]]) {
                    multiProb[edges[j][0]] = multiProb[edges[j][1]] * succProb[j];
                    relaxed = true;
                }
            }
            if(!relaxed) break;
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