#include <bits/stdc++.h>
using namespace std;
// This problem is also disgusting, please explain the purpose of setting the maximal capacity?
struct pos {
    int id, cost;
    pos( int i, int c ) : id( i ), cost( c ) {}
    vector<int> pathList;
    bool operator>( pos const& p ) const {
        return cost != p.cost ? cost > p.cost : id > p.id;
        // If donot sort id:
        // return cost > p.cost;
        // Change filter condition to:
        // if( found && curPos.cost != cost[destination] ) {
    }
};

vector<vector<int>> Dijkstra( vector<vector<pair<int, int>>> const& cityMap, int cityCnt, int destination ) {
    vector<int> cost( cityCnt + 1, INT_MAX );
    priority_queue<pos, vector<pos>, greater<>> pq;
    pq.push( { 0,0 } );
    cost[0] = 0;
    bool found = false;
    vector<vector<int>> pathList;
    while( !pq.empty() ) {
        pos curPos = pq.top();
        pq.pop();
        if( found && curPos.id != destination ) {
            break;
        } else if( curPos.cost > cost[curPos.id] ) {
            continue;
        }
        curPos.pathList.push_back( curPos.id );
        if( curPos.id == destination ) {
            found = true;
            pathList.emplace_back( curPos.pathList );
            continue;
        }
        for( auto [nextId, dis] : cityMap.at( curPos.id ) ) {
            pos nextPos{ nextId,curPos.cost + dis };
            if( nextPos.cost <= cost[nextId] ) {
                cost[nextId] = nextPos.cost;
                nextPos.pathList = curPos.pathList;
                pq.push( nextPos );
            }
        }
    }
    return pathList;
}

tuple<int, vector<int>, int> getRoute( vector<int> const& bikeMap, vector<vector<int>> pathList, int capacity ) {
    vector<int> resPath;
    pair<int, int> resZodiac{ INT_MAX,INT_MAX };
    for_each( pathList.begin(), pathList.end(), [ & ]( vector<int> const& p ) -> void {
        int required = 0, take = 0;
        int limit = capacity / 2;
        int pathLen = p.size();
        for( size_t i = 1; i < pathLen; i++ ) {
            if( bikeMap.at( p[i] ) > limit ) {
                // Fuck fuck fuck, how blind you are.
                // take += bikeMap.at( p[i] ) - 5;
                take += bikeMap.at( p[i] ) - limit;
            } else {
                if( take > limit - bikeMap.at( p[i] ) ) {
                    take -= limit - bikeMap.at( p[i] );
                } else {
                    required += ( limit - bikeMap.at( p[i] ) - take );
                    take = 0;
                }
            }
        }
        if( required < resZodiac.first || ( required == resZodiac.first && take < resZodiac.second ) ) {
            resZodiac = { required,take };
            resPath = move( p );
        }
    } );
    return { resZodiac.first, resPath,resZodiac.second };
}

int main() {
    int capacity, cityCnt, destination, roadCnt;
    cin >> capacity >> cityCnt >> destination >> roadCnt;
    vector<int> bikeMap( cityCnt + 1, 0 );
    for( int i = 1; i <= cityCnt; i++ ) {
        cin >> bikeMap[i];
    }
    vector<vector<pair<int, int>>>  cityMap( cityCnt + 1 );
    for( int i = 0; i < roadCnt; i++ ) {
        int source, dest, cost;
        cin >> source >> dest >> cost;
        cityMap[source].push_back( { dest,cost } );
        cityMap[dest].push_back( { source,cost } );
    }
    vector<vector<int>> searchPath = Dijkstra( cityMap, cityCnt, destination );
    tuple<int, vector<int>, int> result = getRoute( bikeMap, searchPath, capacity );
    cout << get<0>( result ) << " ";
    vector<int> const& path = get<1>( result );
    for( size_t i = 0; i < path.size(); i++ ) {
        cout << path[i] << ( i == path.size() - 1 ? "" : "->" );
    }
    cout << " " << get<2>( result );
}