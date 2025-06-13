#include <bits/stdc++.h>
using namespace std;
int main() {
    int tWkTime, wkCnt;
    cin >> tWkTime >> wkCnt;
    vector<pair<int, int>> workSheet( wkCnt + 1 );
    for ( int i = 1; i <= wkCnt; i++ ) {
        cin >> workSheet[i].first >> workSheet[i].second;
    }
    vector<int> dp = vector<int>( tWkTime + 1, 0 );  // Self-roll
    for ( int i = 1; i <= wkCnt; i++ ) {
        auto [cost, val] = workSheet[i];
        for ( int j = tWkTime; j >= cost; j-- ) {
            dp[j] = max( dp[j], dp[j - cost] + val );
        }
    }
    cout << dp[tWkTime];
}