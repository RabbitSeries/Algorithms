#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    typedef struct pos {
        pos( int c, int x ) : now( c ), id( x ) {};
        int now;
        int evalutate = INT_MAX;
        int id;
        bool operator>( const pos p )const {
            return evalutate != INT_MAX ? evalutate > p.evalutate : now > p.now;
        }
        vector<vector<pair<int, int>>> path;
    }pos;

    int secondMinimum( int n, vector<vector<int>>& edges, int time, int change ) {
        map<int, map<int, bool>> adjMap;
        for( auto edge : edges ) {
            adjMap[edge[0]][edge[1]] = true;
            adjMap[edge[1]][edge[0]] = true;
        }
        int k_times = 0;
        priority_queue<pos, vector<pos>, greater<>> pq;
        pos sPos( 0, 1 );
        map<int, int> distanceTo;
        sPos.evalutate = dijkstra( 1, n, adjMap, time, change, distanceTo );
        pq.push( sPos );
        int min_cost = INT_MAX;
        while( !pq.empty() ) {
            pos curPos = pq.top();
            pq.pop();
            if( curPos.id == n ) {
                if( min_cost == INT_MAX || curPos.now > min_cost ) {
                    k_times++;
                    min_cost = min( min_cost, curPos.now );
                }
                if( k_times == 2 ) {
                    cout << curPos.now;
                    return curPos.now;
                }
            }

            for( auto [nextV, _] : adjMap.at( curPos.id ) ) {
                int nextCost = getNextCost( curPos.now, time, change );
                pos nextPos( nextCost, nextV );
                nextPos.evalutate = nextPos.now + dijkstra( nextV, n, adjMap, time, change, distanceTo );
                pq.push( nextPos );
            }
        }
        return INT_MAX;
    }

    int  dijkstra( int s, int n, map<int, map<int, bool>> const& adjMap, int time, int change, map<int, int>& distanceTo ) {
        if( distanceTo.contains( s ) ) {
            return distanceTo[s];
        }
        vector<int> cost( adjMap.size() + 1 );
        fill( cost.begin(), cost.end(), INT_MAX );
        priority_queue<pos, vector<pos>, greater<>> pq;
        pq.push( { 0,s } );
        cost[s] = 0;
        while( !pq.empty() ) {
            pos curPos = pq.top();
            pq.pop();
            if( curPos.id == n ) {
                distanceTo[s] = curPos.now;
                return curPos.now;
            }
            for( auto [nextV, _] : adjMap.at( curPos.id ) ) {
                int nextCost = getNextCost( curPos.now, time, change );
                if( nextCost < cost[nextV] ) {
                    cost[nextV] = nextCost;
                    pq.push( { nextCost,nextV } );
                }
            }
        }
        cout << "Run time error" << endl;
        return INT_MAX;
    }

    inline int getNextCost( int now, int time, int change ) {
        return ( now / change ) % 2 == 0 ? now + time : now + change - ( now ) % change + time;
    }
};