#include <bits/stdc++.h>
using namespace std;
int main() {
    int dmdCnt, pay, minLost = INT_MAX;
    cin >> dmdCnt >> pay;
    vector<int> diamonds( dmdCnt + 1 ), partialSum( dmdCnt + 1, 0 );
    for ( int i = 1; i <= dmdCnt; i++ )
        cin >> diamonds[i];
    for ( int i = 1; i <= dmdCnt; i++ )
        partialSum[i] = partialSum[i - 1] + diamonds[i];
    vector<pair<int, int>> resList;
    resList.reserve( 100000 );
    for ( int cut = 1; cut <= dmdCnt; cut++ ) {
        int id = [&]() -> int {
            int l = cut, r = dmdCnt;
            while ( l <= r ) {
                int mid = ( l + r ) / 2, curSum = partialSum[mid] - partialSum[cut - 1];
                if ( curSum >= pay ) {
                    r = mid;
                    if ( l == r ) return l;
                } else {
                    l = mid + 1;
                }
            }
            return -1;
        }();
        if ( id != -1 ) {
            int curSum = partialSum[id] - partialSum[cut - 1];
            if ( curSum < minLost ) {
                minLost = curSum;
                resList.clear();
                resList.emplace_back( cut, id );
            } else if ( curSum == minLost ) {
                resList.emplace_back( cut, id );
            }
        }
    }
    for_each( resList.begin(), resList.end(), []( pair<int, int> const &p ) { cout << p.first << "-" << p.second << endl; } );
}