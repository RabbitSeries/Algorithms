#include <bits/stdc++.h>
// WTF is this?
namespace AVL {
template <typename _ElemType, typename _Cmp = std::less<>>
    requires std::default_initializable<_Cmp> && requires( const _Cmp& cmp, const _ElemType& a, const _ElemType& b ) {
        { cmp( a, b ) } -> std::convertible_to<bool>;
        { cmp( b, a ) } -> std::convertible_to<bool>;
    }
struct node {
    using ElemType = _ElemType;
    using NodeType = node<_ElemType, _Cmp>;
    ElemType elem;
    int height;
    NodeType *l, *r;
    node( ElemType _elem ) : elem{ _elem }, height{ 1 }, l( nullptr ), r{ nullptr } {}
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
    friend NodeType* insert( NodeType* root, ElemType elem, _Cmp&& cmp = _Cmp{} ) {
        if ( root == nullptr ) {
            return new NodeType{ elem };
        } else if ( cmp( elem, root->elem ) ) {
            root->l = insert( root->l, elem, forward<_Cmp>( cmp ) );
            if ( getBlcIndex( root ) == 2 ) {
                root = ( getBlcIndex( root->l ) > 0 ? LL( root ) : LR( root ) );  // Both works
                // root = ( cmp( elem, root->l->elem ) ? LL( root ) : LR( root ) );
            }
        } else {
            // insert( root->r, _elem, cmp );  // after the first recursion, leftis  becomes lvalue. better to use forward
            root->r = insert( root->r, elem, forward<_Cmp>( cmp ) );
            if ( getBlcIndex( root ) == -2 ) {
                // root = ( !cmp( elem, root->r->elem ) ? RR( root ) : RL( root ) );  // Both works
                root = ( getBlcIndex( root->r ) < 0 ? RR( root ) : RL( root ) );
            }
        }
        updateHeight( root );
        return root;
    }
    friend NodeType* delNode( NodeType* root, ElemType elem, _Cmp&& cmp = _Cmp{} ) {
        if ( !root ) {
            return root;
        } else if ( cmp( elem, root->elem ) ) {
            root->l = delNode( root->l, elem, forward<_Cmp>( cmp ) );
            if ( getBlcIndex( root ) == -2 ) {
                root = ( getBlcIndex( root->r ) < 0 ? RR( root ) : RL( root ) );
            }
        } else if ( cmp( root->elem, elem ) ) {
            root->r = delNode( root->r, elem, forward<_Cmp>( cmp ) );
            if ( getBlcIndex( root ) == 2 ) {
                root = ( getBlcIndex( root->l ) > 0 ? LL( root ) : LR( root ) );
            }
        } else {
            if ( root->r ) {
                NodeType* ptr = root->r;
                while ( ptr && ptr->l ) {
                    ptr = ptr->l;
                }
                root->elem = ptr->elem;
                root->r = delNode( root->r, ptr->elem, forward<_Cmp>( cmp ) );
            } else if ( root->l ) {
                NodeType* ptr = root->l;
                while ( ptr && ptr->r ) {
                    ptr = ptr->r;
                }
                root->elem = ptr->elem;
                root->l = delNode( root->l, ptr->elem, forward<_Cmp>( cmp ) );
            } else {
                delete root;
                root = nullptr;
            }
        }
        if ( root ) updateHeight( root );
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
};
}  // namespace AVL
