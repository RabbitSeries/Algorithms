#include <bits/stdc++.h>
template <typename _Elem_Type, typename _Cmp = std::less<>>
    requires std::default_initializable<_Cmp> && requires( const _Cmp& cmp, const _Elem_Type& a, const _Elem_Type& b ) {
        { cmp( a, b ) } -> std::convertible_to<bool>;
        { cmp( b, a ) } -> std::convertible_to<bool>;
    }
struct node {
    using Elem_Type = _Elem_Type;
    using NodeType = node<_Elem_Type, _Cmp>;
    Elem_Type elem;
    int height;
    NodeType *l, *r;
    node( Elem_Type _elem ) : elem{ _elem }, height{ 1 }, l( nullptr ), r{ nullptr } {}
    friend inline int getHeight( NodeType* root ) { return root ? root->height : 0; }
    friend inline void updateHeight( NodeType* root ) {
        // if ( root == nullptr ) return; // Actually there is no null root under AVL circumstances
        root->height = std::max( getHeight( root->l ), getHeight( root->r ) ) + 1;
    }
    friend inline int getBlcIndex( NodeType* root ) { return getHeight( root->l ) - getHeight( root->r ); }
    friend NodeType* RR( NodeType* root ) {
        NodeType* right = root->r;
        root->r = right->l;
        right->l = root;
        updateHeight( root );
        return right;
    }
    friend NodeType* RL( NodeType* root ) {
        root->r = LL( root->r );
        return RR( root );
    }
    friend NodeType* LL( NodeType* root ) {
        NodeType* left = root->l;
        root->l = left->r;
        left->r = root;
        updateHeight( root );
        return left;
    }
    friend NodeType* LR( NodeType* root ) {
        root->l = RR( root->l );
        return LL( root );
    }
    friend NodeType* insert( NodeType* root, Elem_Type _elem, _Cmp&& cmp = _Cmp{} ) {
        if ( root == nullptr ) {
            return new NodeType{ _elem };
        } else if ( cmp( _elem, root->elem ) ) {
            root->l = insert( root->l, _elem, forward<_Cmp>( cmp ) );
            if ( getBlcIndex( root ) == 2 ) {
                // root = ( getBlcIndex( root->l ) > 0 ? LL( root ) : LR( root ) ); // Both works
                root = ( cmp( _elem, root->l->elem ) ? LL( root ) : LR( root ) );
            }
        } else {
            // insert( root->r, _elem, cmp );  // after the first recursion, leftis  becomes lvalue. better to use forward
            root->r = insert( root->r, _elem, forward<_Cmp>( cmp ) );
            if ( getBlcIndex( root ) == -2 ) {
                root = ( !cmp( _elem, root->r->elem ) ? RR( root ) : RL( root ) );  // Both works
                // root = ( getBlcIndex( root->r ) < 0 ? RR( root ) : RL( root ) );
            }
        }
        updateHeight( root );
        return root;
    }
    friend void BFS( NodeType* root ) {
        using namespace std;
        queue<NodeType*> q( { root } );
        ostringstream os;
        while ( !q.empty() ) {
            queue<NodeType*> nextLevel;
            while ( !q.empty() ) {
                NodeType* curNode = q.front();
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
    friend void logger( NodeType* root ) {
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
        root = insert( root, val );
        // logger( root );
    }
    cout << ( root ? to_string( root->elem ) : "" );
}