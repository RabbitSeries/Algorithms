#include <bits/stdc++.h>
using namespace std;
class Solution {
   public:
    int trapRainWater( vector<vector<int>>& heightMap ) {
        size_t row = heightMap.size(), col = heightMap[0].size();
        vector<vector<int>> floodMap = heightMap;
        vector<vector<bool>> visited( heightMap.size(), vector<bool>( heightMap[0].size(), false ) );
        for ( size_t i = 0; i < row; i++ ) {
            {
                for ( size_t j = 0; j < col; j++ ) {
                    if ( !visited[i][j] ) {
                    }
                }
            }
        }
        return 0;
    }
    void Flood( vector<vector<int>>& floodMap, vector<vector<bool>>& visited, pair<int, int> const& pos ) {
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq{ greater<>{}, { { pos.first, pos.second, floodMap[pos.first][pos.second] } } };
        while ( !pq.empty() ) {
            auto [x, y, Height] = pq.top();
            pq.pop();
            if ( visited[x][y] ) {
                // TODO  DO DFS , Updating height and Enque logic.
            }
        }
    }
};
int main() {
    vector<vector<int>> test{ { 1, 4, 3, 1, 3, 2 }, { 3, 2, 1, 3, 2, 4 }, { 2, 3, 3, 2, 3, 1 } };
    cout << Solution().trapRainWater( test );
}
