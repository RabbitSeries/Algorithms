#include <bits/stdc++.h>
using namespace std;
int main() {
    using ll = long long;
    vector<vector<ll>> list( 2 );
    for ( ll i = 0; i < 2; i++ ) {
        ll listSize;
        cin >> listSize;
        list[i].resize( listSize );
        for ( ll j = 0; j < listSize; j++ ) {
            cin >> list[i][j];
        }
    }
    vector<ll> mergeList;
    ll i = 0, j = 0;
    while ( i < list[0].size() && j < list[1].size() ) {
        if ( list[0][i] < list[1][j] ) {
            mergeList.push_back( list[0][i++] );
        } else {
            mergeList.push_back( list[1][j++] );
        }
    }
    while ( i < list[0].size() ) {
        mergeList.push_back( list[0][i++] );
    }
    while ( j < list[1].size() ) {
        mergeList.push_back( list[1][j++] );
    }
    cout << mergeList[( mergeList.size() - 1 ) / 2];
    return 0;
}