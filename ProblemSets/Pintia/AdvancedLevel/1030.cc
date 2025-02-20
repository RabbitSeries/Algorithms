#include <bits/stdc++.h>
using namespace std;
void DFSPath( vector<int> &pre, int t ) {
    if ( t == -1 ) return;
    DFSPath( pre, pre[t] );
    cout << t << " ";
}
int main() {
    int cityCnt, edgeCnt, s, t;
    cin >> cityCnt >> edgeCnt >> s >> t;
    vector<vector<tuple<int, int, int>>> nextVList( cityCnt );
    for ( int i = 0; i < edgeCnt; i++ ) {
        int from, to, dist, fee;
        cin >> from >> to >> dist >> fee;
        nextVList[from].emplace_back( to, dist, fee );
        nextVList[to].emplace_back( from, dist, fee );
    }
    vector<int> pre( cityCnt, -1 );
    vector<int> dist( cityCnt, INT_MAX ), fee( cityCnt, 0 );
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace( 0, s );
    bool found = false;
    while ( !pq.empty() ) {
        auto [curDist, curPos] = pq.top();
        pq.pop();
        if ( curDist > dist[curPos] ) continue;
        if ( found && curPos != t ) break;
        if ( curPos == t ) {
            found = true;
            continue;
        }
        for ( auto [nextV, nextDist, nextFee] : nextVList[curPos] ) {
            if ( curDist + nextDist < dist[nextV] ) {
                dist[nextV] = curDist + nextDist;
                fee[nextV]  = fee[curPos] + nextFee;
                pre[nextV]  = curPos;
                pq.emplace( dist[nextV], nextV );
            } else if ( curDist + nextDist == dist[nextV] ) {
                if ( fee[curPos] + nextFee < fee[nextV] ) {
                    fee[nextV] = fee[curPos] + nextFee;
                    pre[nextV] = curPos;
                }
            }
        }
    }
    DFSPath( pre, t );
    cout << dist[t] << " " << fee[t];
}