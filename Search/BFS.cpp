#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> numList;
void BFS( int root ) {
    queue<int> q( { root } );
    set<int> visited{ root };
    while ( !q.empty() ) {
        auto curNode = move( const_cast<int&>( q.front() ) );
        q.pop();
        for ( auto nextV : numList[curNode] ) {
            if ( !visited.contains( nextV ) ) {
                visited.emplace( nextV );
                q.emplace( nextV );
            }
        }
    }
}
