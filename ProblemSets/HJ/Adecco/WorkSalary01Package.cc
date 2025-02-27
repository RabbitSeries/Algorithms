#include <bits/stdc++.h>
using namespace std;
int main() {
    int totalWorkTime, workCnt;
    cin >> totalWorkTime >> workCnt;
    vector<pair<int, int>> workSheet( workCnt + 1 );
    for ( int i = 1; i <= workCnt; i++ ) {
        cin >> workSheet[i].first >> workSheet[i].second;
    }
    int maxValue = 0;
    vector<vector<int>> dp( workCnt + 1, vector<int>( totalWorkTime + 1, 0 ) );
    for ( int i = 1; i <= workCnt; i++ ) {
        auto [cost, val] = workSheet[i];
        for ( int j = totalWorkTime; j >= cost; j-- ) {
            dp[i][j] = max( dp[i - 1][j], dp[i - 1][j - cost] + val );
            maxValue = max( maxValue, dp[i][j] );
        }
    }
    cout << maxValue;
}