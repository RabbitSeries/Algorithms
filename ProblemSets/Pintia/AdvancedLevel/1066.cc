#include <bits/stdc++.h>
using namespace std;
struct node {
    typedef int Elem_Type;
    int elem, height;
    node *l, *r;
    node( int _elem ) : elem{ _elem }, height{ 1 }, l( nullptr ), r{ nullptr } {}
    friend int updateHeight( node *root ) {
        if ( !root ) return 0;
        int lHeight = updateHeight( root->l ), rHeight = updateHeight( root->r );
        return root->height = std::max( lHeight, rHeight ) + 1;
    }
    friend void RR( node *&root ) {
        node *right = root->r;
        root->r = right->l;
        right->l = root;
        root = right;
        updateHeight( root );
    }
    friend void RL( node *&root ) {
        node *right = root->r, *newRoot = root->r->l;
        root->r = newRoot->l;
        newRoot->l = root;
        right->l = newRoot->r;
        newRoot->r = right;
        root = newRoot;
        updateHeight( root );
    }
    friend void LL( node *&root ) {
        node *left = root->l;
        root->l = left->r;
        left->r = root;
        root = left;
        updateHeight( root );
    }
    friend void LR( node *&root ) {
        node *left = root->l, *newRoot = left->r;
        root->l = newRoot->r;
        newRoot->r = root;
        left->r = newRoot->l;
        newRoot->l = left;
        root = newRoot;
        updateHeight( root );
    }
    friend inline int getBlcIndex( node *root ) {
        int lHeight = root->l ? root->l->height : 0, rHeight = root->r ? root->r->height : 0;
        return lHeight - rHeight;
    }
    friend void BalanceTree( node *&root ) {
        int blcIndex = getBlcIndex( root );
        if ( blcIndex == 2 ) {                   // left is higher
            if ( getBlcIndex( root->l ) > 0 ) {  // 2 0
                LL( root );
            } else if ( root->l->r ) {           // 3 1
                LR( root );
            }
        } else if ( blcIndex == -2 ) {           // right is higher
            if ( getBlcIndex( root->r ) < 0 ) {  // 1 3
                RR( root );
            } else {                             // 0 2
                RL( root );
            }
        }
    }
    friend void insert( node *&root, int _elem, function<bool( int, int )> const &leftIs ) {
        if ( root == nullptr ) {
            root = new node{ _elem };
            return;
        }
        if ( leftIs( _elem, root->elem ) ) {
            insert( root->l, _elem, leftIs );
        } else {
            insert( root->r, _elem, leftIs );
        }
        updateHeight( root );
        BalanceTree( root );
    }
};
int main() {
    node *root{ nullptr };
    int elemCnt = 0;
    cin >> elemCnt;
    for ( int val, i = 0; i < elemCnt && cin >> val; i++ ) {
        insert( root, val, less<>{} );
    }
    cout << ( root ? to_string( root->elem ) : "" );
}