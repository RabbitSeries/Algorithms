#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
struct node {
    node() {};
    node( ull v ) : val( v ) {}
    node* l = NULL, * r = NULL;
    ull val = 0;
};
// Inorder
// 2 3 1 5 7 6 4
// Preorder
// 1 2 3 4 5 6 7
// BFS
// 1 2 4 3 5 6 7
node* createTree( vector<ull> const& preOrder, pair<int, int> preBoundary, vector<ull>const& inOrder, pair<int, int> inBoundary ) {
    // Split array
    ull rootVal = preOrder[preBoundary.first];
    auto root = new node( rootVal );
    size_t leftLen = find( inOrder.begin() + inBoundary.first, inOrder.begin() + inBoundary.second + 1, rootVal ) - ( inOrder.begin() + inBoundary.first );
    size_t rightLen = inBoundary.second - inBoundary.first + 1 - 1 - leftLen;
    if( leftLen == 0 ) {
        // left tree is empty
        root->l = NULL;
    } else {
        root->l = createTree( preOrder, { preBoundary.first + 1,preBoundary.first + 1 + leftLen - 1 }, inOrder, { inBoundary.first,inBoundary.first + leftLen - 1 } );
    }

    if( rightLen == 0 ) {
        // right tree is empty
        root->r = NULL;
    } else {
        root->r = createTree( preOrder, { preBoundary.first + 1 + leftLen,preBoundary.second }, inOrder, { inBoundary.second - rightLen + 1 ,inBoundary.second } );
    }
    return root;
}

int main() {
    int numCnt;
    cin >> numCnt;
    vector<ull>  preOrder( numCnt ), inOrder( numCnt );
    for( int i = 0; i < numCnt; i++ ) {
        cin >> inOrder[i];
    }
    for( int i = 0; i < numCnt; i++ ) {
        cin >> preOrder[i];
    }
    pair<int, int> inBoundary{ 0,numCnt - 1 }, preBoundary{ 0,numCnt - 1 };
    node* root = createTree( preOrder, preBoundary, inOrder, inBoundary );
    queue<node*> q;
    q.push( root );
    bool first = true;
    while( !q.empty() ) {
        node* curNode = q.front();
        q.pop();
        if( curNode ) {
            cout << ( first ? "" : " " ) << curNode->val;
            first = false;
        }
        if( curNode->l )
            q.push( curNode->l );
        if( curNode->r ) {
            q.push( curNode->r );
        }
    }
    return 0;
}