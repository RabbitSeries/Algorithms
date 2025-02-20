#include <bits/stdc++.h>
using namespace std;
int main() {
    int cityCnt, edgeCnt, s, t;
    cin >> cityCnt >> edgeCnt >> s >> t;
    vector<vector<pair<int, int>>> nextVList( cityCnt );
    vector<int> teamList( cityCnt );
    for( int i = 0; i < cityCnt; i++ ) {
        cin >> teamList[i];
    }
    for( int i = 0; i < edgeCnt; i++ ) {
        int ts, tt, cost;
        cin >> ts >> tt >> cost;
        nextVList[ts].emplace_back( tt, cost );
        nextVList[tt].emplace_back( ts, cost );
    }
    vector<int> cost( nextVList.size(), INT_MAX ), pathCnt( nextVList.size(), 0 ), teamCnt( nextVList.size(), 0 );
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace( 0, s );
    pathCnt[s] = 1;                         //Init
    teamCnt[s] = teamList[s];
    cost[s] = 0;
    while( !pq.empty() ) {
        auto [curCost, curPos] = pq.top();
        pq.pop();
        if( curCost > cost[curPos] ) {
            continue;                       // Safe even without distance filter
        }
        for( auto [nextPos, edgeCost] : nextVList[curPos] ) {
            int nextCost = curCost + edgeCost;
            if( nextCost <= cost[nextPos] ) {
                cost[nextPos] = nextCost;
                pathCnt[nextPos] = pathCnt[curPos];
                teamCnt[nextPos] = teamCnt[curPos] + teamList[nextPos];
                pq.emplace( nextCost, nextPos );
            } else if( nextCost == cost[nextPos] ) {
                pathCnt[nextPos] += pathCnt[curPos];
                teamCnt[nextPos] = max( teamCnt[curPos] + teamList[nextPos], teamCnt[nextPos] );
            }
        }
    }
    cout << pathCnt[t] << " " << teamCnt[t];
    return 0;
}
