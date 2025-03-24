#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
int maxLength = INT_MIN;
// static vector<int> hashMap( 201, -1 );
using namespace __gnu_pbds;
gp_hash_table<int, int> hashMap;
vector<int> favList, stripeList;
int main() {
    int totalFav, curStripe;
    cin >> totalFav >> totalFav;
    favList.resize( totalFav + 1 );
    for ( int i = 1; i <= totalFav; i++ ) {
        cin >> favList[i];
        hashMap[favList[i]] = i;
    }
    cin >> totalFav;
    for ( int i = 0; i < totalFav; i++ ) {
        cin >> curStripe;
        if ( hashMap.find( curStripe ) != hashMap.end() )
            stripeList.push_back( curStripe );
    }
    maxLength = 0;
    for ( size_t i = 0; i < stripeList.size(); i++ ) {
        for ( int j = i; j <  stripeList.size(); j++ ) {
            if ( hashMap.find( stripeList[i] ) != hashMap.end() ) {
                maxLength = i + 1;
            }
            if ( hashMap.find( stripeList[i] ) != hashMap.end() ) {
                maxLength = i + 2;
            }
        }
    }
    // vector<int> dp( stripeList.size(), 0 );
    // for ( int i = stripeList.size() - 1; i >= 0; i-- ) {
    //     if ( hashMap[stripeList[i]] >= 0 ) {
    //         dp[i] = 1;
    //         for ( int j = i + 1; j < stripeList.size(); j++ ) {
    //             if ( hashMap[stripeList[j]] >= 0 && hashMap[stripeList[i]] <= hashMap[stripeList[j]] ) {
    //                 dp[i] = max( dp[i], dp[j] + 1 );
    //             }
    //         }
    //     }
    //     maxLength = max( maxLength, dp[i] );
    // }
    // dfs();
    cout << maxLength;
}
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