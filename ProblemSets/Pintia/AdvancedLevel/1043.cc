#include <bits/stdc++.h>
using namespace std;
vector<int> originList, postList;
void PostCreate( int l, int r, bool isMirror ) {
    if ( l == r ) return;
    int split;
    if ( !isMirror ) {
        split = find_if( originList.begin() + l + 1, originList.begin() + r, [&]( int val ) { return val >= originList[l]; } ) - originList.begin();
        r = find_if( originList.begin() + split, originList.begin() + r, [&]( int val ) { return val < originList[l]; } ) - originList.begin();
    } else {
        split = find_if( originList.begin() + l + 1, originList.begin() + r, [&]( int val ) { return val < originList[l]; } ) - originList.begin();
        r = find_if( originList.begin() + split, originList.begin() + r, [&]( int val ) { return val >= originList[l]; } ) - originList.begin();
    }
    PostCreate( l + 1, split, isMirror );
    PostCreate( split, r, isMirror );
    postList.push_back( originList[l] );
}
int main() {
    int n, val;
    cin >> n;
    originList.reserve( n );
    for ( int i = 0; i < n; i++ ) {
        cin >> val;
        originList.push_back( val );
    }
    if ( originList.size() > 1 && originList[1] >= originList[0] ) {
        PostCreate( 0, n, true );
    } else
        PostCreate( 0, n, false );
    if ( (int)postList.size() == n ) {
        cout << "YES" << endl;
        cout << postList[0];
        for_each( postList.begin() + 1, postList.end(), []( int val ) { printf( " %d", val ); } );
    } else
        cout << "NO";
    return 0;
}