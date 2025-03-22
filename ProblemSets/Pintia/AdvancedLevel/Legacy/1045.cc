#include <bits/stdc++.h>
using namespace std;
int maxLength = INT_MIN;
unordered_map<int, int> hashMap;
vector<int> favList, stripeList;
void dfs( int curLenth = 0, int i = 0, int j = 0 /* , vector<int> resList = vector<int>{}  */ ) {
    if ( i == favList.size() || j == stripeList.size() ) {
        if ( curLenth >= maxLength ) {
            // for_each( resList.begin(), resList.end(), []( int val ) { cout << val << " "; } );
            // cout << endl;
            maxLength = curLenth;
        }
        return;
    }
    auto keep = find_if( favList.begin() + i, favList.end(), [&]( int fav ) { return fav == stripeList[j]; } );
    if ( keep != favList.end() ) {
        // resList.push_back( *keep );
        dfs( curLenth + 1, keep - favList.begin(), j + 1 /* , resList */ );
        // resList.pop_back();
    }
    dfs( curLenth, i, j + 1 /* , resList */ );  // O (2^n)
}
int main() {
    int totalFav, curStripe;
    cin >> totalFav >> totalFav;
    favList.resize( totalFav );
    for ( int i = 0; i < totalFav; i++ ) {
        cin >> favList[i];
        hashMap[favList[i]] = i;
    }
    cin >> totalFav;
    for ( int i = 0; i < totalFav; i++ ) {
        cin >> curStripe;
        if ( hashMap.contains( curStripe ) )  // Lower the search time cost by filtering useless data.
            stripeList.push_back( curStripe );
    }
    vector<int> dp( stripeList.size() + 1, 0 );
    for ( int i = stripeList.size(); i >= 0; i-- ) {
        for ( int j = i + 1; j <= stripeList.size(); j++ ) {
            if ( hashMap[stripeList[i]] <= hashMap[stripeList[j]] ) {
                dp[i] = max( dp[i], dp[j] + 1 );
            }
        }
        maxLength = max( maxLength, dp[i] );
    }
    // dfs();
    cout << maxLength;
}