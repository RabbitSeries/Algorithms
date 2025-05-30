# Multiple ways for optimizing dijkstra

If the one-step-cost is same from level to level in the BFS order, do **not** use priority_queue, because under this circumstance dijkstra can be replaced equivalently by BFS, and priority_queue sorting will add up to the time cost. (Maybe, I'll test tomorrow)

Problem template: [Leetcode - 1976. Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)

## Summary

### Filter Technique

Both ways ensure optimal relaxed state to be processed only once, thus `assert( distances[u] == distance );` will always succeed.

- **Visited Array**: Visited array to keep track of relaxed nodes. This makes sure the Dijkstra min distance node to be processed only once.
- **Distance Filter**: Some nodes are pushed in queue before they are completely relaxed, this fake relaxed state must be excluded as the above **Visited Array** mechanism. Under circumstances producing a fake relaxed state, thoes fake states are processed after their real relaxed state due to priority queue heap sorting. See this diagram:
![Fake Relax State](https://i-blog.csdnimg.cn/direct/036ea4154710426c90695af5695b488d.png)

### Statistic technique

- **DP** (**Safe** even without **Filter Techinque**): Process **cost array**, **weight array**, **pathCnt array**, **second shortest path** and all other statistics in search extending process. Reduced redundant counting with DP method.
- **Record perpath** (**Must** equipped with **Filter Techinque**) (Slower in dense graph with multiple same cost path): Process statistics when visiting a valid node. Eh, I think this is the universal way to count all path info without DFS after dijkstra or other process, everything is clear in the logical process of dijkstra searching. This method will also have the simplest queue push principle.

### Pruning technique

Both ways can work for DP and Perpath statistic technique.

- **Prune by cost**: Only sort node's cost in Priority Queue (but the node must also carry the id infomation).
- **Prune by id**: Sort both node's cost and id in Priority Queue.

## Visited array + DP

```cpp
#include "bits/stdc++.h"
using namespace std;
class Solution {
public:
    using ll = long long;
    const int MOD = 1e9 + 7;                                                // Modulo value for the number of paths.
    int countPaths( int n, vector<vector<int>> roads ) {                    // Graph represented as adjacency list, where g[u] holds pairs (v, t) for edge u-v with travel time t.
        vector<vector<pair<int, ll>>> graph( n );                           // Build the graph from road information.
        for( auto& road : roads ) {
            graph[road[0]].emplace_back( road[1], road[2] );
            graph[road[1]].emplace_back( road[0], road[2] );
        }
        vector<ll> distances( n, LLONG_MAX );                               // Initialize distances array with infinite distances and set start node distance to 0.
        vector<ll> ways( n, 0 );                                            // Ways array to hold the number of ways to reach each node.
        vector<bool> visited( n, false );                                   // Visited array to keep track of visited nodes.
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq; // Using priority queue to hold pairs of (distance, node), for getting the next closest unvisited node.
        distances[0] = 0;                                                   // Initialize starting values for node 0.
        ways[0] = 1;                                                        // Initialize starting ways for node 0.
        pq.push( { 0, 0 } );
        while( !pq.empty() ) {                                              // Dijkstra's algorithm for shortest paths.
            auto [distance, u] = pq.top();
            pq.pop();
            if( visited[u] )
                continue;
            visited[u] = true;
            for( auto& [v, t] : graph[u] ) {                                // Iterate over all neighbors of the current node.
                assert( distances[u] == distance );
                ll nextDistance = distances[u] + t;
                if( distances[v] > nextDistance ) {                         // If a shorter path is found, update distance and ways.
                    distances[v] = nextDistance;
                    ways[v] = ways[u];
                    pq.push( { nextDistance, v } );
                } else if( distances[v] == nextDistance ) {                 // If an equal distance path is found, add ways.
                    ways[v] = ( ways[v] + ways[u] ) % MOD;
                }
            }
        }
        return ways[n - 1];                                                 // Return the number of ways to reach the last node.
    }
};
```

## Distance Filter + DP

```cpp
#include "bits/stdc++.h"
using namespace std;
class Solution {
public:
    using ll = long long;
    const int MOD = 1e9 + 7; // Modulo value for the number of paths.
    int countPaths( int n, vector<vector<int>> roads ) {
        vector<vector<pair<int, ll>>> graph( n );
        for( auto& road : roads ) {
            graph[road[0]].emplace_back( road[1], road[2] );
            graph[road[1]].emplace_back( road[0], road[2] );
        }
        vector<ll> distances( n, LONG_LONG_MAX );
        vector<ll> ways( n, 0 );
        distances[0] = 0;
        ways[0] = 1;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.emplace( 0, 0 );
        while( !pq.empty() ) {
            auto [distance, u] = pq.top();
            pq.pop();
            if( distance > distances[u] )
                continue;
            for( auto& [v, t] : graph[u] ) {
                assert( distances[u] == distance );
                ll nextDistance = distances[u] + t;
                if( nextDistance < distances[v] ) {
                    distances[v] = nextDistance;
                    ways[v] = ways[u];
                    pq.push( { nextDistance, v } );
                } else if( nextDistance == distances[v] ) {
                    ways[v] = ( ways[v] + ways[u] ) % MOD;
                }
            }
        }
        return ways[n - 1];
    }
};
```

## Distance filter + Process perpath (Time inefficient)

```cpp
#include "bits/stdc++.h"
using namespace std;
class Solution {
public:
    using ll = long long;
    const int MOD = 1e9 + 7; // Modulo value for the number of paths.
    int countPaths( int n, vector<vector<int>> roads ) {
        vector<vector<pair<int, ll>>> graph( n );
        for( auto& road : roads ) {
            graph[road[0]].emplace_back( road[1], road[2] );
            graph[road[1]].emplace_back( road[0], road[2] );
        }
        vector<ll> distances( n, LONG_LONG_MAX );
        vector<ll> ways( n, 0 );
        distances[0] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.emplace( 0, 0 );
        while( !pq.empty() ) {
            auto [distance, u] = pq.top();
            pq.pop();
            if( distance > distances[u] )
                continue;
            ways[u] = ( ways[u] + 1 ) % MOD;
            for( auto& [v, t] : graph[u] ) {
                assert( distances[u] == distance );
                ll nextDistance = distances[u] + t;
                // Record Perpath, just enqueue them all, every path is process once instead of DP
                if( nextDistance <= distances[v] ) {
                    distances[v] = nextDistance;
                    pq.push( { nextDistance, v } );
                }
            }
        }
        return ways[n - 1];
    }
};
```

## Test Data

```cpp
int main() {
    Solution a;
    cout << a.countPaths( 34, { {1,0,9611},{0,2,13741},{2,1,4130},{2,3,2339},{3,0,16080},{1,4,9725},{0,4,19336},{3,4,3256},{4,2,5595},{5,4,6224},{6,2,1303},{1,6,5433},{7,6,10824},{4,7,6532},{5,7,308},{7,1,16257},{6,8,14961},{8,4,10669},{8,0,30005},{5,8,4445},{8,3,13925},{8,7,4137},{2,8,16264},{9,4,12915},{0,9,32251},{8,9,2246},{10,7,14204},{0,10,40072},{6,10,25028},{10,8,10067},{10,3,23992},{10,2,26331},{10,1,30461},{4,10,20736},{5,10,14512},{9,10,7821},{11,4,3381},{12,4,27123},{9,12,14208},{10,12,6387},{8,12,16454},{12,0,46459},{7,12,20591},{12,5,20899},{2,12,32718},{12,11,23742},{1,12,36848},{6,12,31415},{5,13,25075},{13,10,10563},{3,13,34555},{13,12,4176},{13,8,20630},{13,1,41024},{13,11,27918},{13,7,24767},{4,13,31299},{2,13,36894},{10,14,8784},{12,14,2397},{4,14,29520},{6,14,33812},{9,14,16605},{14,3,32776},{5,14,23296},{14,2,35115},{8,14,18851},{7,14,22988},{10,15,9236},{15,3,33228},{15,0,49308},{15,12,2849},{4,16,41221},{16,8,30552},{10,16,20485},{16,11,37840},{16,6,45513},{16,14,11701},{3,16,44477},{1,16,50946},{16,5,34997},{16,7,34689},{12,16,14098},{16,0,60557},{16,13,9922},{2,16,46816},{16,9,28306},{17,9,36735},{17,3,52906},{16,17,8429},{8,17,38981},{7,17,43118},{6,17,53942},{4,17,49650},{17,14,20130},{17,13,18351},{17,10,28914},{17,11,46269},{1,17,59375},{15,17,19678},{17,12,22527},{15,18,27895},{18,12,30744},{18,11,54486},{18,4,57867},{3,18,61123},{18,16,16646},{13,18,26568},{18,8,47198},{1,18,67592},{17,18,8217},{0,18,77203},{6,18,62159},{18,14,28347},{19,13,32225},{11,19,60143},{5,19,57300},{19,15,33552},{10,19,42788},{6,19,67816},{7,19,56992},{19,18,5657},{19,1,73249},{16,19,22303},{8,19,52855},{17,19,13874},{19,3,66780},{19,9,50609},{19,0,82860},{19,4,63524},{4,20,69122},{18,20,11255},{3,20,72378},{11,20,65741},{14,20,39602},{10,20,48386},{1,20,78847},{20,5,62898},{20,15,39150},{20,19,5598},{16,20,27901},{12,20,41999},{0,20,88458},{8,20,58453},{20,13,37823},{20,7,62590},{9,20,56207},{2,20,74717},{20,17,19472},{17,21,26673},{16,21,35102},{3,21,79579},{21,18,18456},{21,9,63408},{21,20,7201},{2,21,81918},{21,11,72942},{14,22,50771},{22,19,16767},{22,18,22424},{22,15,50319},{22,13,48992},{22,3,83547},{6,22,84583},{22,5,74067},{22,10,59555},{16,22,39070},{22,20,11169},{22,12,53168},{4,22,80291},{22,2,85886},{22,8,69622},{22,21,3968},{22,17,30641},{0,22,99627},{11,22,76910},{22,7,73759},{2,23,87059},{23,6,85756},{5,23,75240},{23,21,5141},{9,23,68549},{14,23,51944},{20,23,12342},{1,23,91189},{8,23,70795},{11,23,78083},{23,13,50165},{23,22,1173},{12,23,54341},{23,3,84720},{23,10,60728},{23,17,31814},{21,24,5622},{14,24,52425},{24,20,12823},{7,24,75413},{24,2,87540},{25,1,101404},{13,25,60380},{25,7,85147},{9,25,78764},{15,25,61707},{19,25,28155},{25,22,11388},{25,17,42029},{25,5,85455},{16,25,50458},{25,4,91679},{25,23,10215},{25,14,62159},{24,25,9734},{25,21,15356},{25,10,70943},{25,20,22557},{3,25,94935},{0,25,111015},{19,26,31787},{14,26,65791},{26,3,98567},{26,15,65339},{26,25,3632},{24,26,13366},{9,26,82396},{18,26,37444},{26,17,45661},{26,1,105036},{22,26,15020},{26,5,89087},{10,26,74575},{26,2,100906},{11,26,91930},{13,26,64012},{26,12,68188},{26,4,95311},{20,26,26189},{0,26,114647},{26,21,18988},{0,27,100248},{21,27,4589},{2,27,86507},{4,27,80912},{27,9,67997},{14,27,51392},{27,15,50940},{27,10,60176},{27,11,77531},{27,13,49613},{0,28,124384},{28,12,77925},{28,27,24136},{28,26,9737},{28,10,84312},{28,13,73749},{28,16,63827},{20,28,35926},{28,23,23584},{29,6,100376},{29,23,14620},{29,17,46434},{29,25,4405},{22,29,15793},{29,15,66112},{5,29,89860},{0,29,115420},{13,29,64785},{29,4,96084},{29,19,32560},{29,21,19761},{29,26,773},{11,29,92703},{9,29,83169},{29,18,38217},{29,10,75348},{7,29,89552},{1,29,105809},{29,20,26962},{29,16,54863},{12,29,68961},{29,2,101679},{29,24,14139},{4,30,111360},{10,30,90624},{30,5,105136},{30,1,121085},{8,30,100691},{28,30,6312},{27,30,30448},{30,24,29415},{30,26,16049},{30,12,84237},{6,30,115652},{30,2,116955},{30,14,81840},{30,20,42238},{30,29,15276},{30,9,98445},{30,3,114616},{30,16,70139},{21,30,35037},{30,25,19681},{30,13,80061},{18,30,53493},{30,11,107979},{30,15,81388},{30,0,130696},{31,16,58739},{31,29,3876},{6,31,104252},{31,2,105555},{31,15,69988},{1,32,117525},{20,32,38678},{7,32,101268},{27,32,26888},{25,32,16121},{29,32,11716},{23,32,26336},{32,14,78280},{31,32,7840},{15,32,77828},{32,5,101576},{11,32,104419},{12,32,80677},{23,33,30143},{18,33,53740},{33,10,90871},{31,33,11647},{33,21,35284},{33,25,19928},{33,32,3807},{33,26,16296} } ) << endl;
 cout << a.countPaths( 7, { {0,6,7} ,{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2} } ) << endl;
}
```

Output:

```text
6347247
4
```

## Another Compare

[PintiA A1003](https://pintia.cn/problem-sets/994805342720868352/exam/problems/type/7?problemSetProblemId=994805523835109376)

### DP + Distance filter

```cpp
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
    pathCnt[s] = 1;
    teamCnt[s] = teamList[s];
    cost[s] = 0;
    while( !pq.empty() ) {
        auto [curCost, curPos] = pq.top();
        pq.pop();
        if( curCost > cost[curPos] ) {
            continue;// Safe even without distance filter
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

```

### Count perpath + Distance filter

```cpp
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
```

### Record perpath [all info per path]

```cpp
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
            continue;                           //Wrong nodes must be excluded 
        }
        if( found && curPos.pos != t ) {        // Prune by id
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
```

## Yet another one

PintiA [A1030 Travel Plan](https://pintia.cn/problem-sets/994805342720868352/exam/problems/type/7?problemSetProblemId=994805464397627392&page=0)

### DP + Distance Filter + Pos pruning

```cpp
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
        if ( curDist > dist[curPos] ) {
            continue;
        }
        if ( found && curPos != t ) {
            break;
        }
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
```

## Yet a strange one (In fact: Dijkstra is Greedy algorithm)

[PintiA A1033](https://pintia.cn/problem-sets/994805342720868352/exam/problems/type/7?problemSetProblemId=994805458722734080&page=0)

### DP + Distance(Cost/Fee) Filter + Id prune

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    double capacity, distance, disPerGasUnit, stationCnt;
    cin >> capacity >> distance >> disPerGasUnit >> stationCnt;
    vector<pair<double, double>> stationInfo( stationCnt );
    for ( int i = 0; i < stationCnt; i++ )
        cin >> stationInfo[i].first >> stationInfo[i].second;
    sort( stationInfo.begin(), stationInfo.end(), []( pair<double, double> const &p1, pair<double, double> const &p2 ) {
        return p1.second < p2.second;
    } );
    if ( stationInfo[0].second != 0 ) {
        cout << "The maximum travel distance = 0.00" << endl;
        return 0;
    }
    stationInfo.emplace_back( 0, distance );
    priority_queue<tuple<double, int, double>, vector<tuple<double, int, double>>, greater<>> pq;
    vector<unordered_map<double, double>> fee( stationCnt + 1 );  // remainGas( stationCnt, 0 )
    double maxDist = 0;
    fee[0][0] = 0;
    pq.emplace( 0, 0, 0 );
    while ( !pq.empty() ) {
        auto [curFee, curPos, curGasRemain] = pq.top();
        pq.pop();
        if ( curFee > fee[curPos][curGasRemain] ) continue;
        if ( curPos == stationCnt ) {
            cout << fixed << setprecision( 2 ) << curFee << endl;
            return 0;
        }
        for ( int nextPos = curPos + 1; nextPos < stationCnt + 1; nextPos++ ) {
            double deltaDis = stationInfo[nextPos].second - stationInfo[curPos].second;
            double gasRequired = deltaDis / disPerGasUnit;
            if ( gasRequired > capacity ) {
                maxDist = max( capacity * disPerGasUnit + stationInfo[curPos].second, maxDist );
                break;
            }
            double maxFee = curFee + ( capacity - curGasRemain ) * stationInfo[curPos].first;
            if ( !fee[nextPos].count( capacity - gasRequired ) || maxFee < fee[nextPos][capacity - gasRequired] ) {
                fee[nextPos][capacity - gasRequired] = maxFee;
                pq.emplace( maxFee, nextPos, capacity - gasRequired );
            }
            double nextFee = ( max( gasRequired, curGasRemain ) - curGasRemain ) * stationInfo[curPos].first + curFee;
            double nextGas = max( curGasRemain - gasRequired, (double)0 );
            if ( !fee[nextPos].count( nextGas ) || nextFee < fee[nextPos][nextGas] ) {
                fee[nextPos][nextGas] = nextFee;
                pq.emplace( nextFee, nextPos, nextGas );
            }
        }
    }
    cout << "The maximum travel distance = " << fixed << setprecision( 2 ) << maxDist;
    return 0;
}

// TODO prove this logic
// if ( stationInfo[curPos].first < stationInfo[nextPos].first ) {
//     double maxFee = curFee + ( capacity - curGasRemain ) * stationInfo[curPos].first;
//     if ( !fee[nextPos].count( capacity - gasRequired ) || maxFee < fee[nextPos][capacity - gasRequired] ) {
//         fee[nextPos][capacity - gasRequired] = maxFee;
//         pq.emplace( maxFee, nextPos, capacity - gasRequired );
//     }
// } else {
//     double nextFee = ( max( gasRequired, curGasRemain ) - curGasRemain ) * stationInfo[curPos].first + curFee;
//     double nextGas = max( curGasRemain - gasRequired, (double)0 );
//     if ( !fee[nextPos].count( nextGas ) || nextFee < fee[nextPos][nextGas] ) {
//         fee[nextPos][nextGas] = nextFee;
//         pq.emplace( nextFee, nextPos, nextGas );
//     }
// }
```
