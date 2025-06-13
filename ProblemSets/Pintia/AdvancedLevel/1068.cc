#include <bits/stdc++.h>
using namespace std;
int main() {
    size_t coinCnt;
    int money;
    cin >> coinCnt >> money;
    vector<int> coins( coinCnt + 1 ), dp( money + 1, 0 ), res;
    vector<vector<bool>> inPack( coinCnt + 1, vector( money + 1, false ) );  // Minimize space complexity.
    for ( size_t i = 1; i <= coinCnt; i++ ) {
        cin >> coins[i];
    }
    sort( coins.begin() + 1, coins.end(), greater<>{} );
    for ( size_t i = 1; i <= coinCnt; i++ ) {
        for ( int j = money; j >= coins[i]; j-- ) {
            if ( dp[j - coins[i]] + coins[i] >= dp[j] ) {
                dp[j] = dp[j - coins[i]] + coins[i];
                inPack[i][j] = true;  // See ./Legacy/1068_DFS.cc for selection reason.
            }
        }
    }
    if ( dp[money] != money ) {
        cout << "No Solution";
        return 0;
    }
    for ( int item = coinCnt, remainPay = money; item > 0 && remainPay > 0; item-- ) {
        if ( inPack[item][remainPay] ) {
            remainPay -= coins[item];
            res.emplace_back( coins[item] );
        }
    }
    for ( size_t i = 0; i < res.size(); i++ ) {
        cout << ( i == 0 ? "" : " " ) << res[i];
    }
    return 0;
}