#include <bits/stdc++.h>
using namespace std;
vector<int> coins;
vector<int> mapToCoins( string const& bitmask ) {
    vector<int> res;
    for ( size_t i = 1; i < bitmask.size(); i++ ) {
        if ( bitmask[i] == '1' ) {
            res.emplace_back( coins[i] );
        }
    }
    sort( res.begin(), res.end() );
    return res;
}
vector<vector<int>> dp;  // bitmask
vector<int> res;
void dfs( int i, int j, string& bitmask ) {
    if ( i == 0 || j == 0 ) {
        const vector<int> curRes = mapToCoins( bitmask );
        if ( res.empty() || curRes < res ) {
            res = move( curRes );
        }
        return;
    }
    /**
     * @brief In search, if j >= coins[i] && dp[i-1][j - coins[i]] + coins[i] > dp[i-1][j], higher value select is a must.
     *          If j >= coins[i] && dp[i-1][j - coins[i]] + coins[i] == dp[i-1][j], equal value, but if selected,
     *              this choice can split result into smaller shoices( so sort the weight list is a must).
     *          Otherwise remaining j < coins[i], current item should not be selected.
     * @ref ./Legacy/1068_DFS.cc
     */
    if ( j >= coins[i] ) {
        if ( dp[i - 1][j] <= dp[i - 1][j - coins[i]] + coins[i] ) {
            bitmask[i] = '1';
            dfs( i - 1, j - coins[i], bitmask );
        } else {
            dfs( i - 1, j, bitmask );
        }
        return;
    }
    dfs( i - 1, j, bitmask );
}
int main() {
    size_t coinCnt;
    int money;
    cin >> coinCnt >> money;
    coins.resize( coinCnt + 1, 0 );
    dp.resize( coinCnt + 1, vector<int>( money + 1, 0 ) );
    for ( size_t i = 1; i <= coinCnt; i++ ) {
        cin >> coins[i];
    }
    sort( coins.begin() + 1, coins.end(), greater<>{} );
    for ( size_t i = 1; i <= coinCnt; i++ ) {
        for ( int j = 0; j <= money; j++ ) {
            dp[i][j] = j >= coins[i] ? max( dp[i - 1][j], dp[i - 1][j - coins[i]] + coins[i] ) : dp[i - 1][j];
        }
    }
    if ( dp[coinCnt][money] == money ) {
        string tempmask( coinCnt + 1, '0' );
        dfs( coinCnt, money, tempmask );
    }
    if ( res.empty() ) {
        cout << "No Solution";
        return 0;
    }
    cout << *res.begin();
    for ( auto itr = ++res.cbegin(); itr != res.cend(); itr++ ) {
        cout << " " << ( *itr );
    }
    return 0;
}