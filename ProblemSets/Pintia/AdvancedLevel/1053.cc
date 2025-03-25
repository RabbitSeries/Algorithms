#include <bits/stdc++.h>
using namespace std;
int N, M, S, nextVCnt;
vector<vector<int>> pathList;
unordered_map<int, vector<int>> nextVList;
vector<int> weightList;
vector<int> curPath;
void DFS( int curNode ) {
    curPath.emplace_back( curNode );
    if ( nextVList.contains( curNode ) ) {
        for ( int nextV : nextVList.at( curNode ) )
            DFS( nextV );
    } else if ( accumulate( curPath.begin(), curPath.end(), 0, []( int init, int nodeId ) { return init + weightList[nodeId]; } ) == S ) {
        pathList.emplace_back( curPath );
    }
    curPath.pop_back();
}
int main() {
    cin >> N >> M >> S;
    weightList.resize( N );
    for ( int i = 0; i < N; i++ ) cin >> weightList[i];
    for ( int i = 0; i < M; i++ ) {
        int curVId;
        cin >> curVId >> nextVCnt;
        nextVList[curVId].resize( nextVCnt );
        for ( int j = 0; j < nextVCnt; j++ )
            cin >> nextVList[curVId][j];
    }
    DFS( 0 );
    sort( pathList.begin(), pathList.end(), []( vector<int> const& p1, vector<int> const& p2 ) {
        int minLen = min( p1.size(), p2.size() );
        for ( int i = 0; i < minLen; i++ ) {
            if ( weightList[p1[i]] != weightList[p2[i]] ) {
                return weightList[p1[i]] > weightList[p2[i]];
            }
        }
        return false;
    } );
    stringstream buf;
    for ( auto const& path : pathList ) {
        stringstream pathBuf;
        for ( int const& id : path ) {
            pathBuf << " " << weightList[id];
        }
        buf << pathBuf.str().substr( 1 ) << endl;
    }
    cout << buf.str();
}