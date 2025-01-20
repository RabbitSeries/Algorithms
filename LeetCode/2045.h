#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static vector<vector<int>> data;
    int n, time, change;
    typedef struct pos {
        pos( int c, int x ) : now( c ), id( x ) {};
        int now;
        int id;
        bool operator>( const pos p )const {
            return now > p.now;
        }
        vector<vector<pair<int, int>>> path;
    }pos;

    int secondMinimum( int n, vector<vector<int>>& edges, int time, int change ) {
        this->n = n;
        this->time = time;
        this->change = change;

        map<int, int> runtimeCost;

        map<int, map<int, bool>> adjMap;
        for( auto edge : edges ) {
            if( edge.size() == 2 ) {
                runtimeCost[edge[0]] = INT_MAX;
                runtimeCost[edge[1]] = INT_MAX;
                adjMap[edge[0]][edge[1]] = true;
                adjMap[edge[1]][edge[0]] = true;
            }
        }

        vector<vector<pair<int, int>>> optimalPath = findAllPath( runtimeCost, adjMap );

        int curShortest = INT_MAX;
        if( optimalPath.size() ) {
            curShortest = optimalPath[0].back().second;
            cout << "Current shortest path cost " << optimalPath[0].back().second << endl;
        }
        else {
            cout << "No shortest path cost" << endl;
            return 0;
        }

        int secondMin = INT_MAX;
        int tmp = 0;
        tmp = shortestCostFrom( { getNextCost( 0, time, change, 2 ),1 }, runtimeCost, adjMap, INT_MAX, INT_MAX );
        if( tmp != curShortest ) {
            secondMin = min( secondMin, tmp );
        }
        for( auto p : optimalPath ) {
            auto it = p.begin();
            for( ; it != p.end() - 1; it++ ) {
                auto [s, sCost] = *it;
                auto [t, tCost] = *next( it );
                tmp = shortestCostFrom( { sCost,s }, runtimeCost, adjMap, s, t );
                for( auto& ele : runtimeCost ) {
                    ele.second = INT_MAX;
                }
                if( tmp != curShortest ) {
                    secondMin = min( secondMin, tmp );
                    // break;
                }
                // cout << "Foudnd second min at " << s << " " << t << " " << "with value " << tmp << endl;
            }
        }
        cout << "Second shortest path cost " << secondMin << endl;
        return secondMin;
    }

    vector<vector<pair<int, int>>> findAllPath( map<int, int> runtimeCost, map<int, map<int, bool>> const& adjMap ) {
        vector<vector<pair<int, int>>> optimalPath;

        priority_queue<pos, vector<pos>, greater<pos>> pq;

        int min_Cost = INT_MAX;
        pq.push( pos( 0, 1 ) );
        runtimeCost[1] = 0;

        while( !pq.empty() ) {
            pos curPos = pq.top();
            pq.pop();

            if( min_Cost != INT_MAX && curPos.now != min_Cost ) {
                break;
            }

            if( curPos.path.empty() ) {
                assert( curPos.now == 0 );
                curPos.path = { {{curPos.id,curPos.now},}, };
            }
            else {
                for( auto& p : curPos.path ) {
                    p.push_back( { curPos.id,curPos.now } );
                }
            }

            if( curPos.id == n ) {
                min_Cost = curPos.now;
                for( auto p : curPos.path ) {
                    optimalPath.push_back( p );
                }
                continue;
            }

            int nextCost = getNextCost( curPos.now, time, change );

            for( auto [nextV, _] : adjMap.at( curPos.id ) ) {
                if( nextCost <= runtimeCost.at( nextV ) ) {
                    runtimeCost[nextV] = nextCost;
                    pos nextPos( nextCost, nextV );
                    if( nextCost < runtimeCost.at( nextV ) ) {
                        nextPos.path = curPos.path;
                    }
                    else {
                        for( auto p : curPos.path ) {
                            nextPos.path.push_back( p );
                        }
                    }
                    pq.push( nextPos );
                }
            }
        }

        // cout << optimalPath.size() << endl;

        return optimalPath;
    }

    int shortestCostFrom( pos s, map<int, int>& runtimeCost, map<int, map<int, bool>> const& adjMap, int removeEdgeS, int removeEdgeT ) {
        priority_queue<pos, vector<pos>, greater<pos>> pq;
        pq.push( s );
        runtimeCost[s.id] = s.now;

        vector<vector<pair<int, int>>> optimalPath;

        while( !pq.empty() ) {

            pos curPos = pq.top();
            pq.pop();

            if( curPos.id == n ) {
                return curPos.now;
            }

            int nextCost = getNextCost( curPos.now, time, change );

            for( auto [nextV, _] : adjMap.at( curPos.id ) ) {
                if( !( curPos.id == removeEdgeT && nextV == removeEdgeS ) && !( curPos.id == removeEdgeS && nextV == removeEdgeT ) ) {
                    if( nextCost < runtimeCost.at( nextV ) ) {
                        runtimeCost[nextV] = nextCost;
                        pos nextPos( nextCost, nextV );
                        pq.push( nextPos );
                    }
                }
            }
        }
        return INT_MAX;
    }

    int getNextCost( int nowCost, int time, int change, int depth = 1 ) {
        int nextCost = ( nowCost / change ) % 2 == 0 ? nowCost + time : nowCost + change - ( nowCost ) % change + time;
        if( depth == 1 ) {
            return nextCost;
        }
        else {
            return getNextCost( nextCost, time, change, depth - 1 );
        }
    }

};