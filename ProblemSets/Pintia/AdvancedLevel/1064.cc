#include <bits/stdc++.h>
using namespace std;
vector<int> tree, nodeList;
void Create( int N, int root = 1 ) {
    static int nodeId = 0;
    if ( root > N ) return;
    Create( N, 2 * root );
    tree[root] = nodeList[nodeId++];
    Create( N, 2 * root + 1 );
}
int main() {
    int N;
    cin >> N;
    tree.resize( N + 1 );
    nodeList.resize( N );
    for ( int i = 0; i < N; i++ ) cin >> nodeList[i];
    sort( nodeList.begin(), nodeList.end() );
    Create( N );
    ostringstream os;
    for ( int i = 1; i <= N; i++ ) os << " " << tree[i];
    cout << os.str().substr( 1 );
    return 0;
}