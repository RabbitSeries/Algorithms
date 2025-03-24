#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
int main() {
    int totalFav, curStripe;
    cin >> totalFav;
    // vector<int> hashMap( totalFav + 1, -1 );  // Array: 60 ms
    gp_hash_table<int, int> hashMap;  // Array: 60 ms
    hashMap.insert( make_pair( 1, 2 ) );
    cin >>
        totalFav;
    for ( int i = 1; i <= totalFav; i++ ) {
        cin >> curStripe;
        hashMap[curStripe] = i;
    }
    cin >> totalFav;
    vector<int> stripeList;
    for ( int i = 0; i < totalFav; i++ ) {
        cin >> curStripe;
        if ( hashMap[curStripe] > 0 )
            stripeList.emplace_back( curStripe );
    }
    int totalLen = stripeList.size();
    int maxLength = INT_MIN;
    vector<int> dp( totalLen, 1 );  // stripe split starts with
    for ( int i = totalLen - 1; i >= 0; i-- ) {
        for ( int j = i + 1; j < totalLen; j++ ) {
            if ( hashMap[stripeList[i]] <= hashMap[stripeList[j]] )
                dp[i] = max( dp[i], dp[j] + 1 );
        }
        maxLength = max( maxLength, dp[i] );
    }
    cout << maxLength;
}
// for ( int i = 0; i < totalLen; i++ ) {
//     for ( int j = 0; j < i; j++ ) {
//         if ( hashMap[stripeList[i]] >= hashMap[stripeList[j]] )
//             dp[i] = max( dp[i], dp[j] + 1 );
//     }
//     maxLength = max( maxLength, dp[i] );
// }