#include <bits/stdc++.h>
using namespace std;
namespace Solution1 {
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
        if ( GetBlcIndex( root ) == 2 ) {
            root = GetBlcIndex( root->l ) > 0 ? LL( root ) : LR( root );
        }
    } else {
        root->r = insert( root->r, _elem, leftIs );
        if ( GetBlcIndex( root ) == -2 ) {
            root = GetBlcIndex( root->r ) < 0 ? RR( root ) : RL( root );
        }
    }
    UpdateHeight( root );
    return root;
}
int Solution( vector<int> const &input ) {
    node *root = NULL;
    for ( auto const &val : input ) {
        root = insert( root, val );
    }
    return root->elem;
}
}  // namespace Solution1
namespace Solution2 {
struct node {
    int val;
    struct node *left, *right;
};
node *rotateLeft( node *root ) {
    node *t = root->right;
    root->right = t->left;
    t->left = root;
    return t;
}
node *rotateRight( node *root ) {
    node *t = root->left;
    root->left = t->right;
    t->right = root;
    return t;
}
node *rotateLeftRight( node *root ) {
    root->left = rotateLeft( root->left );
    return rotateRight( root );
}
node *rotateRightLeft( node *root ) {
    root->right = rotateRight( root->right );
    return rotateLeft( root );
}
int getHeight( node *root ) {
    if ( root == NULL ) return 0;
    return max( getHeight( root->left ), getHeight( root->right ) ) + 1;
}
node *insert( node *root, int val ) {
    if ( root == NULL ) {
        root = new node();
        root->val = val;
        root->left = root->right = NULL;
    } else if ( val < root->val ) {
        root->left = insert( root->left, val );
        if ( getHeight( root->left ) - getHeight( root->right ) == 2 )
            root = val < root->left->val ? rotateRight( root ) : rotateLeftRight( root );
    } else {
        root->right = insert( root->right, val );
        if ( getHeight( root->left ) - getHeight( root->right ) == -2 )
            root = val > root->right->val ? rotateLeft( root ) : rotateRightLeft( root );
    }
    return root;
}
int Solution( vector<int> const &input ) {
    node *root = NULL;
    for ( auto const &val : input ) {
        root = insert( root, val );
    }
    return root->val;
}
}  // namespace Solution2
int main() {
    vector<int> input( 10000 );
    iota( input.begin(), input.end(), 0 );
    auto now = chrono::high_resolution_clock::now();
    Solution1::Solution( input );
    auto end = chrono::high_resolution_clock::now();
    cout << "Solution 1 time cost: " << chrono::duration_cast<chrono::milliseconds>( end - now ).count() << endl;
    now = end;
    Solution2::Solution( input );
    end = chrono::high_resolution_clock::now();
    cout << "Solution 2 time cost: " << chrono::duration_cast<chrono::milliseconds>( end - now ).count() << endl;
}