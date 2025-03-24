#include <bits/stdc++.h>
using namespace std;
int main() {
    int exitCnt, queryCnt;
    cin >> exitCnt;
    vector<int> dis( exitCnt + 2, 0 );
    for ( int i = 1; i <= exitCnt; i++ ) {
        cin >> dis[i + 1];
        dis[i + 1] = dis[i] + dis[i + 1];
    }
    cin >> queryCnt;
    for ( int i = 0; i < queryCnt; i++ ) {
        int l, r;
        cin >> l >> r;
        if ( r < l )
            cout << min( dis[exitCnt + 1] - dis[l] + dis[r], dis[l] - dis[r] ) << endl;
        else
            cout << min( dis[r] - dis[l], dis[l] + dis[exitCnt + 1] - dis[r] ) << endl;
    }
    return 0;
}