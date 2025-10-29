#include "AbstractBST.hpp"
/**
 * ================================================
 * @brief
 *           O           O
 *          /           /^\
 * !       O      =>   O | O
 *        /|             |
 * !     O ---------------
 * ================================================
 *           O            O
 *          /            /
 * !       O      =>    O
 *          \          /^
 * !         O        O |
 * !         |          |
 * !         ------------
 * ================================================
 *           O              O
 *            \            /^\
 * !           O      =>  O | O
 *             |\           |
 * !           | O          |
 *             --------------
 * ================================================
 *           O              O
 *            \              \
 * !           O      =>      O
 *            /               ^\
 * !         O                | O
 *           |                |
 *           ------------------
 * ================================================
 *           O
 * !        / \           O
 * !       O   O   =>    / \
 *        /             O   O
 * !     O             /
 *                    O
 * ================================================
 */
#include <map>
struct RBT : public AbstractBST<RBT> {
    RBT( int elem ) : AbstractBST( elem ) {}
    enum RBT_Color {
        red = false,
        black = true
    };
    RBT_Color color = red;
    std::weak_ptr<RBT> parent;  // Parent should use weak_ptr to avoid memory leak
    // int bHeight = 0; // Doesn't need this to maintain the property of RBT
    static void rRotate( Node root, Tree& tree );
    static void lRotate( Node root, Tree& tree );
    static Tree insert( Tree tree, int elem );
    static void insert_rebalance( Node elem, Tree& tree );
};
inline void RBT::rRotate( Node root, Tree& tree ) {
    Tree lRoot = root->l;
    root->l = lRoot->r;
    if ( root->l ) {
        root->l->parent = root;
    }
    lRoot->parent = root->parent;
    if ( root == tree ) {
        tree = lRoot;
    } else if ( root == root->parent.lock()->l ) {
        root->parent.lock()->l = lRoot;
    } else {
        root->parent.lock()->r = lRoot;
    }
    lRoot->r = root;
    root->parent = lRoot;
}
inline void RBT::lRotate( Node root, Tree& tree ) {
    Tree rRoot = root->r;
    root->r = rRoot->l;
    if ( root->r ) {
        root->r->parent = root;
    }
    rRoot->parent = root->parent;
    if ( root == tree ) {
        tree = rRoot;
    } else if ( root == root->parent.lock()->l ) {
        root->parent.lock()->l = rRoot;
    } else {
        root->parent.lock()->r = rRoot;
    }
    rRoot->l = root;
    root->parent = rRoot;
}
inline RBT::Tree RBT::insert( Tree tree, int elem ) {
    if ( !tree ) {
        tree = std::make_shared<RBT>( elem );
        tree->color = black;
    }
    bool left = false;
    // Parent is nullptr actually if root is really a root.
    Node parent = tree->parent.lock(), p = tree;
    while ( p ) {
        if ( elem == p->data ) {
            return tree;
        }
        left = elem < p->data;
        parent = p;
        if ( left ) {
            p = p->l;
        } else {
            p = p->r;
        }
    }
    Node node = std::make_shared<RBT>( elem );
    if ( left ) {
        parent->l = node;
        node->parent = parent;
    } else {
        parent->r = node;
        node->parent = parent;
    }
    insert_rebalance( node, tree );
    return tree;
}
inline void RBT::insert_rebalance( Node elem, Tree& tree ) {
    while ( elem != tree && elem->parent.lock()->color == red ) {
        Node xpp = elem->parent.lock()->parent.lock();
        if ( elem->parent.lock() == xpp->l ) {
            Node y = xpp->r;
            if ( y && y->color == red ) {
                xpp->color = red;
                xpp->l->color = black;
                xpp->r->color = black;
                elem = xpp;
            } else {
                if ( elem == elem->parent.lock()->r ) {
                    elem = elem->parent.lock();
                    lRotate( elem, tree );
                }
                elem->parent.lock()->color = black;
                xpp->color = red;
                rRotate( xpp, tree );
            }
        } else {
            Node y = xpp->l;
            if ( y && y->color == red ) {
                xpp->color = red;
                xpp->l->color = black;
                xpp->r->color = black;
                elem = xpp;
            } else {
                if ( elem == elem->parent.lock()->l ) {
                    elem = elem->parent.lock();
                    rRotate( elem, tree );
                }
                elem->parent.lock()->color = black;
                xpp->color = red;
                lRotate( xpp, tree );
            }
        }
    }
    tree->color = black;  // The root is always black, either rebalanced or already balanced.
                          // Set the root of the entire tree to black anyways.
}
