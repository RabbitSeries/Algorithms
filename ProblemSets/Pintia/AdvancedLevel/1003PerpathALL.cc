#include <bits/stdc++.h>
using namespace std;
pair<int, int> Dijkstra( vector<vector<pair<int, int>>> const& nextVList, vector<int> const& teamList, int s, int t ) {
    int PathCnt = 0, TeamCnt = 0;
    vector<int> cost( nextVList.size(), INT_MAX );
    using posInfo = struct posInfo {
        posInfo( int _s, int _c ) : pos( _s ), cost( _c ) {};
        int pos = 0;
        int cost = 0;
        vector<int> pathTeamList{};
        bool operator> ( const posInfo& p ) const {
            return cost == p.cost ? pos > p.pos : cost > p.cost;
        }
    };
    priority_queue<posInfo, vector<posInfo>, greater<>> pq;
    pq.push( { s,0 } );
    cost[s] = 0;
    bool found = false;
    while( !pq.empty() ) {
        posInfo curPos = pq.top();
        pq.pop();
        if( cost[curPos.pos] < curPos.cost ) {  // Thus, this line is a must for priority_queue implementation
            continue;//Wrong nodes must be excluded 
        }
        if( found && curPos.pos != t ) {
            return { PathCnt,TeamCnt };
        }
        curPos.pathTeamList.push_back( teamList[curPos.pos] );
        if( curPos.pos == t ) {
            found = true;
            PathCnt++;
            int acc = accumulate( curPos.pathTeamList.begin(), curPos.pathTeamList.end(), 0 );
            TeamCnt = max( acc, TeamCnt );
            continue;
        }
        for( auto [nextPos, nextVCost] : nextVList[curPos.pos] ) {
            int nextCost = curPos.cost + nextVCost;
            posInfo nextV{ nextPos,nextCost };
            // Simply enque them all.
            if( nextCost <= cost[nextPos] ) {
                cost[nextPos] = nextCost;
                nextV.pathTeamList = curPos.pathTeamList;
                pq.push( nextV );
            }
        }
    }
    return { PathCnt,TeamCnt };
}

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
        nextVList[ts].push_back( { tt,cost } );
        nextVList[tt].push_back( { ts,cost } );
    }
    auto res = Dijkstra( nextVList, teamList, s, t );
    cout << res.first << " " << res.second;
    return 0;
}
