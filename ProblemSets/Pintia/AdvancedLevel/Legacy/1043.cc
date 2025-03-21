#include <bits/stdc++.h>
using namespace std;
using node = struct node {
    struct node *l = nullptr, *r = nullptr;
    int val = -1;
};
void PreOrderCreate( node *&curNode, int l, int r, vector<int> &originList, bool isMirror ) {
    if ( l >= r ) return;
    curNode = new node{ nullptr, nullptr, originList[l] };
    int split;
    if ( !isMirror ) {
        split = find_if( originList.begin() + l + 1, originList.begin() + r, [&]( int val ) { return val >= originList[l]; } ) - originList.begin();
        while ( r - 1 > l && originList[r - 1] < originList[l] ) r--;
    } else {
        split = find_if( originList.begin() + l + 1, originList.begin() + r, [&]( int val ) { return val < originList[l]; } ) - originList.begin();
        while ( r - 1 > l && originList[r - 1] >= originList[l] ) r--;
    }
    PreOrderCreate( curNode->l, l + 1, split, originList, isMirror );
    PreOrderCreate( curNode->r, split, r, originList, isMirror );
}
void midOrder( node *curNode, vector<int> &midList ) {
    if ( !curNode ) return;
    midOrder( curNode->l, midList );
    midList.push_back( curNode->val );
    midOrder( curNode->r, midList );
}
void PostOrder( node *curNode, vector<int> &postList ) {
    if ( !curNode ) return;
    PostOrder( curNode->l, postList );
    PostOrder( curNode->r, postList );
    postList.push_back( curNode->val );
}
int main() {
    vector<int> preList, postList, originList, midList;
    node *root = new node;
    int n, val;
    cin >> n;
    for ( int i = 0; i < n; i++ ) {
        cin >> val;
        originList.push_back( val );
    }
    if ( originList.size() > 1 && originList[1] >= originList[0] ) {
        PreOrderCreate( root->l, 0, n, originList, true );
        sort( originList.begin(), originList.end(), greater<>{} );
    } else {
        PreOrderCreate( root->l, 0, n, originList, false );
        sort( originList.begin(), originList.end() );
    }
    midOrder( root->l, midList );
    if ( midList == originList ) {
        PostOrder( root->l, postList );
        cout << "YES" << endl
             << accumulate( postList.begin(), postList.end(), string( "" ), []( string const &init, int val ) {
                    return ( stringstream() << init << " " << val ).str();
                } ).substr( 1 );
    } else
        cout << "NO";
    return 0;
}