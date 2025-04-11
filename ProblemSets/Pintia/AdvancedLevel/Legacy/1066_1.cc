#include <bits/stdc++.h>
using namespace std;
struct node {
    int elem, height;
    node *l, *r;
    node( int _elem ) : elem{ _elem }, height{ 1 }, l( nullptr ), r{ nullptr } {}
};
inline int getHeight( node *root ) { return root ? root->height : 0; }
inline void updateHeight( node *root ) {
    // if ( root == nullptr ) return; // Actually there is no null root under AVL circumstances
    root->height = std::max( getHeight( root->l ), getHeight( root->r ) ) + 1;
}
inline int GetBlcIndex( node *root ) {
    return getHeight( root->l ) - getHeight( root->r );
}
void RR( node *&root ) {
    node *right = root->r;
    root->r = right->l;  // right-> l might be null
    right->l = root;
    root = right;
    updateHeight( root->l );
}
void LL( node *&root ) {
    node *left = root->l;
    root->l = left->r;
    left->r = root;
    root = left;
    updateHeight( root->r );
}
void RL( node *&root ) {
    LL( root->r );
    RR( root );
}
void LR( node *&root ) {
    RR( root->l );
    LL( root );
}
void BalanceTree( node *&root ) {
    int blcIndex = GetBlcIndex( root );
    if ( blcIndex == 2 ) {                   // left is higher
        if ( GetBlcIndex( root->l ) > 0 ) {  // Left is left-higher
            LL( root );
            // } else if ( root->l->r ) {           // This also works, so there exsits a hack data
        } else {                             // Left is right-higher
            LR( root );
        }
        updateHeight( root );
    } else if ( blcIndex == -2 ) {           // Right is higher
        if ( GetBlcIndex( root->r ) < 0 ) {  // Right is right-higher
            RR( root );
        } else {                             // Right is left-higher
            RL( root );
        }
        updateHeight( root );
    }
}
void insert( node *&root, int _elem, function<bool( int, int )> const &leftIs = less<>{} ) {
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
int main() {
    node *root{ nullptr };
    int elemCnt = 0;
    cin >> elemCnt;
    for ( int val, i = 0; i < elemCnt && cin >> val; i++ ) {
        insert( root, val );
    }
    cout << ( root ? to_string( root->elem ) : "" );
}