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
        // vector<int> cost1( adjMap.size() + 1 ,INT_MAX);
        map<int, int> cost1;
        // // fill( cost1.begin(), cost1.end(), INT_MAX );
        // vector<int> cost2( adjMap.size() + 1 ,INT_MAX);
        map<int, int> cost2;
        // // fill( cost2.begin(), cost2.end(), INT_MAX );
        for( auto edge : edges ) {
            cost1[edge[0]] = INT_MAX;
            cost1[edge[1]] = INT_MAX;
            cost2[edge[0]] = INT_MAX;
            cost2[edge[1]] = INT_MAX;
            adjMap[edge[0]][edge[1]] = true;
            adjMap[edge[1]][edge[0]] = true;
        }
        int k_times = 0;
        priority_queue<pos, vector<pos>, greater<>> pq;
        // queue<pos> pq;
        pos sPos( 0, 1 );
        map<int, int> distanceTo;
        sPos.evalutate = dijkstra( 1, n, adjMap, time, change, distanceTo );
        sPos.evalutate = sPos.now;
        pq.push( sPos );
        int min_cost = INT_MAX;

        cost1[1] = 0;
        while( !pq.empty() ) {
            pos curPos = pq.top();
            // pos curPos = pq.front();
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
                nextPos.evalutate = nextPos.now;
                nextPos.evalutate = nextPos.now + dijkstra( nextV, n, adjMap, time, change, distanceTo );
                if( nextPos.evalutate < cost1[nextV] ) {
                    cost1[nextV] = nextPos.evalutate;
                    pq.push( nextPos );
                }
                else if( nextPos.evalutate > cost1[nextV] && nextPos.evalutate < cost2[nextV] ) {
                    cost2[nextV] = nextPos.evalutate;
                    pq.push( nextPos );
                }
            }
        }
        return INT_MAX;
    }

    int  dijkstra( int s, int n, map<int, map<int, bool>> const& adjMap, int time, int change, map<int, int>& distanceTo ) {
        if( distanceTo.count( s ) ) {
            return distanceTo[s];
        }
        vector<int> cost( adjMap.size() + 1, INT_MAX );
        priority_queue<pos, vector<pos>, greater<>> pq;
        pq.emplace( 0, s );
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
                    pq.emplace( nextCost, nextV );
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