#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
struct node {
    node() {};
    node( ull v ) : val( v ) {}
    node* l = NULL, * r = NULL;
    ull val = 0;
};
// 7
// Postorder
// 2 3 1 5 7 6 4
// Inorder
// 1 2 3 4 5 6 7
// BFS
// 4 1 6 3 5 7 2
node* createTree( vector<ull>const& postOrder, pair<int, int> postBoundary, vector<ull> const& inOrder, pair<int, int> inBoundary ) {
    // Split array
    ull rootVal = postOrder[postBoundary.second];
    auto root = new node( rootVal );
    size_t leftLen = find( inOrder.begin() + inBoundary.first, inOrder.begin() + inBoundary.second + 1, rootVal ) - ( inOrder.begin() + inBoundary.first );
    size_t rightLen = inBoundary.second - inBoundary.first + 1 - 1 - leftLen;
    if( leftLen == 0 ) {
        // left tree is empty
        root->l = NULL;
    } else {
        root->l = createTree( postOrder, { postBoundary.first,postBoundary.first + leftLen - 1 }, inOrder, { inBoundary.first,inBoundary.first + leftLen - 1 } );
    }

    if( rightLen == 0 ) {
        // right tree is empty
        root->r = NULL;
    } else {
        root->r = createTree( postOrder, { postBoundary.first + leftLen ,postBoundary.second - 1 }, inOrder, { inBoundary.second - rightLen + 1,inBoundary.second } );
    }
    return root;
}

int main() {
    int numCnt;
    cin >> numCnt;
    vector<ull> postOrder( numCnt ), inOrder( numCnt );
    for( int i = 0; i < numCnt; i++ ) {
        cin >> postOrder[i];
    }
    for( int i = 0; i < numCnt; i++ ) {
        cin >> inOrder[i];
    }
    pair<int, int> postBoundary{ 0,numCnt - 1 }, inBoundary{ 0,numCnt - 1 };
    node* root = createTree( postOrder, postBoundary, inOrder, inBoundary );
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