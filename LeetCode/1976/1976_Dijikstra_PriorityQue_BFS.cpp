#include <vector>
#include <queue>
#include <tuple>
#include <limits>

using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const int MOD = 1e9 + 7;

        // Graph representation
        vector<vector<pair<int, int>>> graph(n);
        for(const auto& road : roads) {
            int u = road[0], v = road[1], time = road[2];
            graph[u].emplace_back(v, time);
            graph[v].emplace_back(u, time);
        }

        // Min-time and count arrays
        vector<long long> minTime(n, LLONG_MAX);
        vector<int> count(n, 0);

        // Priority queue for Dijkstra's algorithm
        /**
         * @brief pair.first = time pair.second = index
         * 
         */
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

        // Start from node 0
        minTime[0] = 0;
        count[0] = 1;
        pq.emplace(0, 0);

        while(!pq.empty()) {
            auto [current_time, u] = pq.top();
            pq.pop();

            if(current_time > minTime[u]) continue;// Already relaxed in a queue before.

            for(auto& [v, time] : graph[u]) {
                long long new_time = current_time + time;

                if(new_time < minTime[v]) {
                    minTime[v] = new_time;
                    count[v] = count[u];
                    pq.emplace(new_time, v);
                }
                else if(new_time == minTime[v]) {
                    count[v] = (count[v] + count[u]) % MOD;
                }
            }
        }
        return count[n - 1];
    }
};
int main() {
    return 0;
}