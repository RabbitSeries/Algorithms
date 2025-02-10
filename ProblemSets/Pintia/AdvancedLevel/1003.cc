#include <bits/stdc++.h>
using namespace std;

pair<int, int> Dijkstra( vector<pair<int, map<int, vector<int>>>>const& nextVList, int s, int t ) {
    int PathCnt = 0, TeamCnt = 0;

    vector<int> mapCost( nextVList.size(), INT_MAX );

    typedef struct posInfo {
        posInfo( int _s, int _c ) : pos( _s ), cost( _c ) {};
        int pos = 0;
        int cost = 0;
        vector<vector<int>> pathTeamList{};
        bool operator> ( const posInfo& p ) const {
            return cost > p.cost;
        }
    }posInfo;

    priority_queue<posInfo, vector<posInfo>, greater<>> pq;
    pq.push( { s,0 } );
    mapCost[s] = 0;
    bool found = false;
    while( !pq.empty() ) {
        posInfo curPos = pq.top();
        pq.pop();
        // Add cost;

        // There might be some node with the same cost as t's and enqued for process, use this for optimization instead.
        if( found && mapCost[curPos.pos] > mapCost[t] ) {
            return { PathCnt,TeamCnt };
        }
        // if( found && curPos.pos != t ) {
        //     return { PathCnt,TeamCnt };
        // }

        if( mapCost[curPos.pos] < curPos.cost ) {
            continue;
        }

        if( curPos.pathTeamList.empty() ) {
            curPos.pathTeamList.push_back( { nextVList[curPos.pos].first, } );
        } else {
            for( auto& path : curPos.pathTeamList ) {
                path.push_back( nextVList[curPos.pos].first );
            }
        }

        if( curPos.pos == t ) {
            found = true;
            PathCnt++;
            for( auto const& path : curPos.pathTeamList ) {
                int acc = accumulate( path.begin(), path.end(), 0 );
                TeamCnt = max( acc, TeamCnt );
            }
            continue;
        }

        for( auto [nextPos, pathCost] : nextVList[curPos.pos].second ) {
            for( auto nextVCost : pathCost ) {
                int nextCost = curPos.cost + nextVCost;
                posInfo nextV{ nextPos,nextCost };
                // Simply enque them all.
                if( nextCost <= mapCost[nextPos] ) {
                    mapCost[nextPos] = nextCost;
                    nextV.pathTeamList = curPos.pathTeamList;
                    pq.push( nextV );
                }
            }
        }


    }
    return { PathCnt,TeamCnt };
}

int main() {
    vector<pair<int, map<int, vector<int>>>> nextVList;
    int cityCnt, edgeCnt, s, t;
    cin >> cityCnt >> edgeCnt >> s >> t;
    int i = 0;
    while( i++ < cityCnt ) {
        int nodeTeam;
        cin >> nodeTeam;
        nextVList.push_back( { nodeTeam,map<int, vector<int>>() } );
    }
    i = 0;
    while( i++ < edgeCnt ) {
        int ts, tt, cost;
        cin >> ts >> tt >> cost;
        nextVList[ts].second[tt].push_back( cost );
        nextVList[tt].second[ts].push_back( cost );
    }
    auto res = Dijkstra( nextVList, s, t );
    cout << res.first << " " << res.second;
    return 0;
}