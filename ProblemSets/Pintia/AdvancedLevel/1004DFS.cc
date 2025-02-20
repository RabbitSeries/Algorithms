#include <bits/stdc++.h>
using namespace std;
int maxDepth = 0;
void DFS( vector<vector<int>>const& childList, vector<int>& DepthLeaveCnt, int s, int h ) {
    maxDepth = max( h, maxDepth );
    if( childList[s].empty() )
        DepthLeaveCnt[h]++;
    else
        for( int pid : childList[s] ) DFS( childList, DepthLeaveCnt, pid, h + 1 );
}
int main() {
    int nodeCnt, parentCnt, id, childCnt, childId;
    cin >> nodeCnt >> parentCnt;
    vector<vector<int>> childList( nodeCnt + 1 );
    vector<int>leaveCnt( nodeCnt + 1 );
    for( int i = 0; i < parentCnt; i++ ) {
        cin >> id >> childCnt;
        for( int j = 0; j < childCnt; j++ ) {
            cin >> childId;
            childList[id].push_back( childId );
        }
    }
    DFS( childList, leaveCnt, 1, 1 );
    for( int i = 1; i <= maxDepth; i++ ) cout << ( i == 1 ? "" : " " ) << leaveCnt[i];
    return 0;
}
// Anthor DFS
// void DFS( vector<vector<int>>const& childList, vector<int>& DepthLeaveCnt, int s ) {
//     curDepth++;
//     maxDepth = max( curDepth, maxDepth );
//     if( childList[s].empty() ) {
//         DepthLeaveCnt[curDepth]++;
//         return;
//     } else
//         for( int pid : childList[s] ) {
//             DFS( childList, DepthLeaveCnt, pid );
//             curDepth--;
//         }
// }