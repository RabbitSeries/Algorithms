#include <bits/stdc++.h>
using namespace std;
vector<int> BFS( int root, vector<vector<int>>const& nextVMap, size_t totalNode, unordered_set<int>& visited ) {
    unordered_set<int> curVisited;
    vector<int> curLevelNode;
    queue<int> q;
    visited.insert( root );
    curVisited.insert( root );
    q.push( root );
    while( !q.empty() ) {
        curLevelNode.clear();
        while( !q.empty() ) {
            auto curNode = q.front();
            q.pop();
            curLevelNode.push_back( curNode );
        }
        for( auto curNode : curLevelNode ) {
            for( auto nextNode : nextVMap.at( curNode ) ) {
                if( !curVisited.count( nextNode ) ) {
                    curVisited.insert( nextNode );
                    visited.insert( nextNode );
                    q.push( nextNode );
                }
            }
        }
    }
    return curVisited.size() == totalNode ? curLevelNode : vector<int>{};
}
int main() {
    int nodeCnt;
    cin >> nodeCnt;
    vector<vector<int>> nextVMap( nodeCnt );
    for( int i = 0; i < nodeCnt - 1; i++ ) {
        int s, d;
        cin >> s >> d;
        nextVMap[s].push_back( d );
        nextVMap[d].push_back( s );
    }
    unordered_set<int> visited;
    set<int, less<>> res;
    int componentsCnt = 0;
    // Some nodes is isolated thus unordered_map will not record this infomation, remember manually processing for all nodes and access safety checkings.
    for( int i = 1; i <= nodeCnt; i++ ) {
        if( !visited.count( i ) ) {
            componentsCnt++;
            auto deepest = BFS( i, nextVMap, nodeCnt, visited );
            if( !deepest.empty() ) {
                auto nextDeepest = BFS( deepest[0], nextVMap, nodeCnt, visited );
                assert( !nextDeepest.empty() );
                for( auto key : deepest ) res.insert( key );
                for( auto key : nextDeepest )  res.insert( key );
                for( auto key : res )  cout << key << endl;
                return 0;
            }
        }
    }
    printf( "Error: %d components", componentsCnt );
    return 0;
}