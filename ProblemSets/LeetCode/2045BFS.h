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
        map<int, int> dis1, dis2;
        for( auto edge : edges ) {
            dis1[edge[0]] = dis1[edge[1]] = INT_MAX;
            dis2[edge[0]] = dis2[edge[1]] = INT_MAX;
            adjMap[edge[0]][edge[1]] = true;
            adjMap[edge[1]][edge[0]] = true;
        }
        queue<pos> q;
        dis1[1] = 0;
        q.emplace( 0, 1 );
        while( !q.empty() ) {
            pos curPos = q.front();
            q.pop();
            if( curPos.id == n ) {
                if( dis2[n] != INT_MAX ) {
                    cout << dis2[n];
                    return dis2[n];
                }
            }
            int nextCost = getNextCost( curPos.now, time, change );
            for( auto [nextV, _] : adjMap.at( curPos.id ) ) {
                if( nextCost < dis1[nextV] ) {
                    dis1[nextV] = nextCost;
                    q.emplace( nextCost, nextV );
                }
                else if( nextCost > dis1[nextV] && nextCost < dis2[nextV] ) {
                    dis2[nextV] = nextCost;
                    q.emplace( nextCost, nextV );
                }
                // If this node is not either extreme optimized node or second optimized queue, leave it alone.
                // This algorithm only need the k <= 2 shortest path, instead of any k shortest path.
                // This algorithm actually obtained k-shortest path from source to any target.
                // q.emplace( nextCost, nextV );
                // This algorithm only works if the cost to next level is the same.
            }
        }
        return INT_MAX;
    }


    static constexpr int getNextCost( int now, int time, int change ) {
        return ( now / change ) % 2 == 0 ? now + time : now + change - ( now ) % change + time;
    }
};