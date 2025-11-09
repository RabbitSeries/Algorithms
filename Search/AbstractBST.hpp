#pragma once
#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <ranges>
template <typename derived>
struct AbstractBST {
    using Tree = std::shared_ptr<derived>;
    using Node = std::shared_ptr<derived>;
    int data = -1;
    // l->data < this->data < r.data
    AbstractBST( int elem ) : data{ elem } {}
    virtual ~AbstractBST() {}
    Node l = nullptr, r = nullptr;
    static const Node find( const Tree root, int elem );
    static void pre( Tree root );
    static void mid( Tree root );
    static void after( Tree root );
    template <bool testDelete = true>
    static void test();
};
/**
 * @return Node or nullptr
 */
template <typename derived>
inline const AbstractBST<derived>::Node AbstractBST<derived>::find( const Tree root, int elem ) {
    if ( !root ) {
        return nullptr;
    }
    if ( elem == root->data ) {
        return root;
    } else if ( elem < root->data ) {
        return find( root->l, elem );
    } else {
        return find( root->r, elem );
    }
}
template <typename derived>
inline void AbstractBST<derived>::pre( Tree root ) {
    if ( !root ) {
        return;
    }
    std::cout << root->data << " ";
    pre( root->l );
    pre( root->r );
}
template <typename derived>
inline void AbstractBST<derived>::mid( Tree root ) {
    if ( !root ) {
        return;
    }
    pre( root->l );
    std::cout << root->data << " ";
    pre( root->r );
}
template <typename derived>
inline void AbstractBST<derived>::after( Tree root ) {
    if ( !root ) {
        return;
    }
    pre( root->l );
    pre( root->r );
    std::cout << root->data << " ";
}
template <typename derived>
template <bool testDelete>
inline void AbstractBST<derived>::test() {
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> u_distri( 0, 100 );
    Tree tree;
    for ( int _ : std::views::iota( 0, 50 ) ) {
        int elem = u_distri( gen );
        tree = derived::insert( tree, elem );
    }
    void ( *traversal[] )( Tree root ) = { &pre, &mid, &after };
    std::cout << "DFS: pre, mid, after\n";
    for ( auto method : traversal ) {
        method( tree );
        std::cout << "\n";
    }
    std::queue<Node> q{ { tree } };
    int level = 1;
    while ( !q.empty() ) {
        std::cout << "Level " << ( level++ ) << ": ";
        std::queue<Node> nextLevel;
        while ( !q.empty() ) {
            auto node = q.front();
            q.pop();
            std::cout << node->data << " ";
            if ( node->l ) {
                nextLevel.push( node->l );
            }
            if ( node->r ) {
                nextLevel.push( node->r );
            }
        }
        q = std::move( nextLevel );
        std::cout << "\n";
    }
    for ( int _ : std::views::iota( 0, 50 ) ) {
        int elem = u_distri( gen );
        auto result = derived::find( tree, elem );
        if ( result ) {
            std::cout << elem << " is found\n";
        } else {
            std::cout << elem << " not found\n";
        }
    }
    if constexpr ( testDelete ) {
        for ( int _ : std::views::iota( 0, 100 ) ) {
            int elem = u_distri( gen );
            tree = derived::del( tree, elem );
            std::cout << "Elem " << elem << " deleted\n";
            pre( tree );
            std::cout << "\n";
        }
    }
}
