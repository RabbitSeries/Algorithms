#include <bits/stdc++.h>
template <typename _Elem_Type, typename _Cmp = std::less<>>
    requires std::default_initializable<_Cmp> && requires( const _Cmp& cmp, const _Elem_Type& a, const _Elem_Type& b ) {
        { cmp( a, b ) } -> std::convertible_to<bool>;
        { cmp( b, a ) } -> std::convertible_to<bool>;
    }
struct node {
    using Elem_Type = _Elem_Type;
    using nodeType = node<_Elem_Type, _Cmp>;
    Elem_Type elem;
    int height;
    nodeType *l, *r;
    node( Elem_Type _elem ) : elem{ _elem }, height{ 1 }, l( nullptr ), r{ nullptr } {}
    friend inline int getHeight( nodeType* root ) {
        return root ? root->height : 0;
    }
    friend inline void updateHeight( nodeType* root ) {
        // if ( root == nullptr ) return; // Actually there is no null root under AVL circumstances
        root->height = std::max<int>( getHeight( root->l ), getHeight( root->r ) ) + 1;
    }
    friend inline Elem_Type getBlcIndex( nodeType* root ) {
        return getHeight( root->l ) - getHeight( root->r );
    }
    friend void RR( nodeType*& root ) {
        nodeType* right = root->r;
        root->r = right->l;
        right->l = root;
        root = right;
        updateHeight( root->l );
    }
    friend void RL( nodeType*& root ) {
        nodeType *right = root->r, *newRoot = root->r->l;
        root->r = newRoot->l;
        newRoot->l = root;
        right->l = newRoot->r;
        newRoot->r = right;
        root = newRoot;
        updateHeight( root->r );
        updateHeight( root->l );
    }
    friend void LL( nodeType*& root ) {
        nodeType* left = root->l;
        root->l = left->r;
        left->r = root;
        root = left;
        updateHeight( root->r );
    }
    friend void LR( nodeType*& root ) {
        nodeType *left = root->l, *newRoot = left->r;
        root->l = newRoot->r;
        newRoot->r = root;
        left->r = newRoot->l;
        newRoot->l = left;
        root = newRoot;
        updateHeight( root->r );
        updateHeight( root->l );
    }
    friend void BalanceTree( nodeType*& root ) {
        int blcIndex = getBlcIndex( root );
        if ( blcIndex == 2 ) {                   // left is higher
            if ( getBlcIndex( root->l ) > 0 ) {  // 2 0
                LL( root );
            } else if ( root->l->r ) {           // 3 1
                LR( root );
            }
            updateHeight( root );
        } else if ( blcIndex == -2 ) {           // right is higher
            if ( getBlcIndex( root->r ) < 0 ) {  // 1 3
                RR( root );
            } else {                             // 0 2
                RL( root );
            }
            updateHeight( root );
        }
    }
    friend void insert( nodeType*& root, Elem_Type _elem, _Cmp&& cmp = _Cmp{} ) {
        if ( root == nullptr ) {
            root = new nodeType{ _elem };
            return;
        }
        if ( cmp( _elem, root->elem ) ) {
            insert( root->l, _elem, forward<_Cmp>( cmp ) );
        } else {
            // insert( root->r, _elem, cmp );  // after the first recursion, leftis  becomes lvalue. better to use forward
            insert( root->r, _elem, forward<_Cmp>( cmp ) );
        }
        updateHeight( root );
        BalanceTree( root );
    }
    friend void BFS( nodeType* root ) {
        using namespace std;
        queue<nodeType*> q( { root } );
        ostringstream os;
        while ( !q.empty() ) {
            queue<nodeType*> nextLevel;
            while ( !q.empty() ) {
                nodeType* curNode = q.front();
                q.pop();
                if ( !curNode )
                    os << " ";
                else {
                    os << " " << curNode->elem;
                    nextLevel.push( curNode->l );
                    nextLevel.push( curNode->r );
                }
            }
            os << endl;
            q = nextLevel;
        }
        cout << os.str();
    }
    friend void logger( nodeType* root ) {
        using namespace std;
        cout << "Tree: " << endl;
        BFS( root );
        cout << "Input:";
    }
};
using namespace std;
int main() {
    node<int, less<>>* root{ nullptr };
    int elemCnt = 0;
    cin >> elemCnt;
    for ( int val, i = 0; i < elemCnt && cin >> val; i++ ) {
        insert( root, val );
        // logger( root );
    }
    cout << ( root ? to_string( root->elem ) : "" );
}