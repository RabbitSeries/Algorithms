#include <bits/stdc++.h>
namespace AVL_Ietrative {
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
    friend inline void resolveInfo( std::stack<std::pair<NodeType*, int>>& NodeStk, NodeType* curNode, int ParentInfo ) {
        NodeStk.pop();
        if ( !NodeStk.empty() ) {
            auto [ParentNode, _] = NodeStk.top();
            if ( ParentInfo == -1 ) {
                ParentNode->l = curNode;
            } else if ( ParentInfo == 1 ) {
                ParentNode->r = curNode;
            }
        }
    }
    friend inline void blanceRoot( std::stack<std::pair<NodeType*, int>>& NodeStk, NodeType*& curNode, int ParentInfo ) {
        if ( getBlcIndex( curNode ) == 2 ) {
            curNode = ( getBlcIndex( curNode->l ) > 0 ? LL( curNode ) : LR( curNode ) );
            resolveInfo( NodeStk, curNode, ParentInfo );
        } else if ( getBlcIndex( curNode ) == -2 ) {
            curNode = ( getBlcIndex( curNode->r ) < 0 ? RR( curNode ) : RL( curNode ) );
            resolveInfo( NodeStk, curNode, ParentInfo );
        } else {
            NodeStk.pop();
        }
        updateHeight( curNode );
    }
    friend NodeType* insert( NodeType* root, ElemType elem, _Cmp&& cmp = _Cmp{} ) {
        if ( !root ) return new NodeType( elem );
        std::stack NodeStk{ std::deque{ std::pair<NodeType*, int>{ root, 0 } } };
        bool Added = false;
        NodeType* initRoot = root;
        while ( !NodeStk.empty() ) {
            auto [curNode, ParentInfo] = NodeStk.top();
            if ( !Added ) {
                if ( curNode ) {
                    if ( cmp( elem, curNode->elem ) ) {
                        NodeStk.emplace( curNode->l, -1 );
                    } else if ( cmp( curNode->elem, elem ) ) {
                        NodeStk.emplace( curNode->r, 1 );
                    } else {
                        return initRoot;  // Dulplicated elem.
                    }
                } else {
                    curNode = new NodeType{ elem };
                    resolveInfo( NodeStk, curNode, ParentInfo );
                    Added = true;
                }
            } else {
                blanceRoot( NodeStk, curNode, ParentInfo );
            }
            root = curNode;
        }
        updateHeight( root );
        return root;
    }
    friend NodeType* delNode( NodeType* root, ElemType elem, _Cmp&& cmp = _Cmp{} ) {
        if ( !root ) return nullptr;
        std::stack NodeStk{ std::deque{ std::pair<NodeType*, int>{ root, 0 } } };
        NodeType* initRoot = root;
        bool deleted = false;
        while ( !NodeStk.empty() ) {
            auto [curNode, ParentInfo] = NodeStk.top();
            if ( !deleted ) {
                if ( curNode ) {
                    if ( cmp( elem, curNode->elem ) ) {
                        NodeStk.emplace( curNode->l, -1 );
                    } else if ( cmp( curNode->elem, elem ) ) {
                        NodeStk.emplace( curNode->r, 1 );
                    } else {
                        if ( curNode->l ) {
                            NodeType* ptr = curNode->l;
                            while ( ptr && ptr->r ) {
                                ptr = ptr->r;
                            }
                            curNode->elem = ptr->elem;  // Change to std::move()?
                            elem = ptr->elem;
                            NodeStk.emplace( curNode->l, -1 );
                        } else if ( curNode->r ) {
                            NodeType* ptr = curNode->r;
                            while ( ptr && ptr->l ) {
                                ptr = ptr->l;
                            }
                            curNode->elem = ptr->elem;
                            elem = ptr->elem;
                            NodeStk.emplace( curNode->r, 1 );
                        } else {
                            delete curNode;
                            curNode = nullptr;
                            resolveInfo( NodeStk, curNode, ParentInfo );
                            deleted = true;
                        }
                    }
                } else {
                    return initRoot;  // Not found
                }
            } else {
                blanceRoot( NodeStk, curNode, ParentInfo );
            }
            root = curNode;
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
}  // namespace AVL_Ietrative
