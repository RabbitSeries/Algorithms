#pragma once
#include <memory>
#include <vector>
#include "AbstractBST.hpp"
// Tag: unique element.
struct BST : public AbstractBST<BST> {
    BST( int elem ) : AbstractBST( elem ) {}
    static Tree insert( Tree root, int elem );
    static Tree del( Tree root, int elem );
};
/**
 * @brief Create a node if tree is empty. Won't do anything if the tree already have this element.
 */
inline BST::Tree BST::insert( Tree root, int elem ) {
    if ( !root ) {
        return std::make_shared<BST>( elem );
    }
    if ( elem == root->data ) {
        return root;
    }
    if ( elem > root->data ) {
        root->r = insert( root->r, elem );
    } else {
        root->l = insert( root->l, elem );
    }
    return root;
}
/**
 * @brief Won't do anything if the tree doesn't have this element.
 */
inline BST::Tree BST::del( Tree root, int elem ) {
    if ( !root ) {
        return nullptr;
    }
    if ( elem == root->data ) {
        if ( root->l ) {
            Node p = root->l;
            while ( p && p->r ) {
                p = p->r;
            }
            root->data = p->data;
            root->l = del( root->l, root->data );
        } else if ( root->r ) {
            Node p = root->r;
            while ( p && p->l ) {
                p = p->l;
            }
            root->data = p->data;
            root->r = del( root->r, root->data );
        } else {
            return nullptr;
        }
    } else if ( elem < root->data ) {
        root->l = del( root->l, elem );
    } else {
        root->r = del( root->r, elem );
    }
    return root;
}
