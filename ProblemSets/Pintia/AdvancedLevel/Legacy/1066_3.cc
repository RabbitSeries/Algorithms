#include <bits/stdc++.h>
using namespace std;
struct node {
    int elem, height;
    node *l, *r;
};
inline void UpdateHeight( node *root ) { root->height = max( root->l ? root->l->height : 0, root->r ? root->r->height : 0 ) + 1; }
inline int GetBlcIndex( node *root ) { return ( root->l ? root->l->height : 0 ) - ( root->r ? root->r->height : 0 ); }
node *RR( node *root ) {
    node *right = root->r;
    root->r = right->l;
    right->l = root;
    UpdateHeight( root );
    return right;
}
node *LL( node *root ) {
    node *left = root->l;
    root->l = left->r;
    left->r = root;
    UpdateHeight( root );
    return left;
}
node *RL( node *root ) {
    root->r = LL( root->r );
    return RR( root );
}
node *LR( node *root ) {
    root->l = RR( root->l );
    return LL( root );
}
node *insert( node *root, int _elem, function<bool( int, int )> const &leftIs = less<>{} ) {
    if ( root == nullptr ) {
        return new node{ _elem, 1, nullptr, nullptr };
    } else if ( leftIs( _elem, root->elem ) ) {
        root->l = insert( root->l, _elem, leftIs );
        if ( GetBlcIndex( root ) == 2 ) {   // left is higher
            root = GetBlcIndex( root->l ) > 0 ? LL( root ) : LR( root );
        }
    } else {
        root->r = insert( root->r, _elem, leftIs );
        if ( GetBlcIndex( root ) == -2 ) {  // Right is higher
            root = GetBlcIndex( root->r ) < 0 ? RR( root ) : RL( root );
        }
    }
    UpdateHeight( root );                     // pure Update is only for GetBlcIndex, but root's height is not required before GetBlcIndex
    // only required before GetBlcIndex, so put it in the return stack
    return root;
}
int main() {
    node *root{ nullptr };
    int elemCnt = 0;
    cin >> elemCnt;
    for ( int val, i = 0; i < elemCnt && cin >> val; i++ ) {
        root = insert( root, val );
    }
    cout << ( root ? to_string( root->elem ) : "" );
}