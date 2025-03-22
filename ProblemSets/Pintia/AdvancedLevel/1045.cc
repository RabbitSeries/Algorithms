#include <bits/stdc++.h>
using namespace std;
// unordered_map<int, int> hashMap;
vector<int> hashMap( 201, -1 );  // Array: 60 ms
int main() {
    ios::sync_with_stdio( false );
    cin.tie( nullptr );
    int totalFav, curStripe;
    cin >> totalFav;
    // hashMap.reserve( totalFav + 1 );
    cin >> totalFav;
    int maxLength = INT_MIN;
    vector<int> stripeList;
    for ( int i = 0; i < totalFav; i++ ) {
        cin >> curStripe;
        hashMap[curStripe] = i;
    }
    cin >> totalFav;
    for ( int i = 0; i < totalFav; i++ ) {
        cin >> curStripe;
        // if ( hashMap.contains( curStripe ) )
            if ( hashMap[curStripe] >= 0 )
            stripeList.push_back( curStripe );
    }
    int totalLen = stripeList.size();
    vector<int> dp( totalLen, 1 );
    for ( int i = 0; i < totalLen; i++ ) {
        for ( int j = 0; j < i; j++ ) {
            if ( hashMap[stripeList[i]] >= hashMap[stripeList[j]] )
                dp[i] = max( dp[i], dp[j] + 1 );
        }
        maxLength = max( maxLength, dp[i] );
    }
    cout << maxLength;
}

// if ( hashMap[ curStripe ]>=0 )  // Lower the search time cost by filtering useless data. hashMap set to -1;
// if ( totalLen < 1000 )
// for ( int i = totalLen - 1; i >= 0; i-- ) {
//     for ( int j = i + 1; j < totalLen; j++ ) {
//         if ( hashMap[stripeList[i]] <= hashMap[stripeList[j]] ) {
//             dp[i] = max( dp[i], dp[j] + 1 );
//         }
//     }
//     maxLength = max( maxLength, dp[i] );
// }