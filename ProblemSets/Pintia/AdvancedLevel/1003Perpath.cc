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
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.emplace( 0, s, 0 );
    cost[s] = 0;            //Only init cost
    while( !pq.empty() ) {
        auto [curCost, curPos, curTeam] = pq.top();
        pq.pop();
        if( curCost > cost[curPos] ) {
            continue;                   //Hack data, if wrong node is not excluded the res will be wrong. Perpath implementation must equipped with Filter technique
        }
        pathCnt[curPos]++;
        teamCnt[curPos] = max( curTeam + teamList[curPos], teamCnt[curPos] );
        for( auto [nextPos, edgeCost] : nextVList[curPos] ) {
            int nextCost = curCost + edgeCost;
            if( nextCost <= cost[nextPos] ) {
                cost[nextPos] = nextCost;
                pq.emplace( nextCost, nextPos, teamCnt[curPos] );
            }
        }
    }
    cout << pathCnt[t] << " " << teamCnt[t];
    return 0;
}

// Hack data
// 4 4 0 3
// 1 1 1 1
// 0 1 1
// 0 2 1
// 1 3 2
// 2 3 1
// output
// 1 3