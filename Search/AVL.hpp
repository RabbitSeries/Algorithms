#pragma once
/**
 * @brief
 * ==============================================================================
 * AVL ensures these cases won't appear:
 * Abnormal 1:
 *     O
 *    /
 *   O
 *  /
 * O
 * =======================================
 * Abnormal 2:
 * O
 *  \
 *   O
 *    \
 *     O
 * ==============================================================================
 * So, if add a parent node, there will be four cases in insertion:
 * 1. Insert at root's left : lChild becomes Abnormal 1, rChild is normal
 * 2. Insert at root's left : lChild becomes Abnormal 2, rChild is normal
 * 3. Insert at root's right: rChild becomes Abnormal 2, lChild is normal
 * 4. Insert at root's right: rChild becomes Abnormal 1, lChild is normal
 * And the corresponsding cases in deletion:
 * 1. Delete at root's left : rChild becomes Abnormal 2, lChild is normal
 * 2. Delete at root's left : rChild becomes Abnormal 1, lChild is normal
 * 3. Delete at root's right: lChild becomes Abnormal 1, rChild is normal
 * 4. Delete at root's right: lChild becomes Abnormal 2, rChild is normal
 * ==============================================================================
 * For case 1 and 3:
 *       O (2)          *       O (2)
 *      / \             * r -> /|\
 *     O   O rRotate => *     O | O
 *    /                 *    / \v
 *   O                  *   O   O
 *  /                   *  /
 * O                    * O
 * =======================================
 *       O (-2)         *       O (-2)
 *      / \             *      /|\  <- l
 *     O   O lRotate => *     O | O
 *          \           *       v/ \
 *           O          *       O   O
 *            \         *            \
 *             O        *             O
 * ==============================================================================
 * For case 2 and 4:
 *       O (2)          *       O (2)          *        O (2)
 *      / \             *      / \             *       / \
 *     O   O lRotate => *     O   O        =>  *      O   O   rRotate  => ...
 *      \               *    /|\ <- l          * r-> /
 *       O              *   O | O              *    O
 *        \             *     v/ \             *   /
 *         O            *     O   O            *  O
 * =====================================================================
 *       O (-2)         *       O (-2)         *       O (2)
 *      / \             *      / \             *      / \
 *     O   O rRotate => *     O   O        =>  *     O   O   lRotate  => ...
 *        /             *    r-> /|\           *          \ <- l
 *       O              *       O | O          *           O
 *      /               *      / \v            *            \
 *     O                *     O   O            *             O
 * ==============================================================================
 */
#include "AbstractBST.hpp"
struct AVL : public AbstractBST<AVL> {
    using Tree = std::shared_ptr<AVL>;
    using Node = std::shared_ptr<AVL>;
    AVL( int elem ) : AbstractBST( elem ) {}
    int height = 1;
    int bIndex();
    void updateHeight();
    static Tree balance( Tree root );
    static Tree rRotate( Tree root );  // Rotate clock wise
    static Tree lRotate( Tree root );  // Rotate counter-clock wise
    static Tree insert( Tree root, int elem );
    static Tree del( Tree root, int elem );
};
inline int AVL::bIndex() {
    int lHeight = l ? l->height : 0;
    int rHeight = r ? r->height : 0;
    return lHeight - rHeight;
}
inline void AVL::updateHeight() {
    int lHeight = l ? l->height : 0;
    int rHeight = r ? r->height : 0;
    height = std::max( lHeight, rHeight ) + 1;
}
inline AVL::Tree AVL::rRotate( Tree root ) {
    Tree lRoot = root->l;
    root->l = lRoot->r;
    lRoot->r = root;
    root->updateHeight();   // Root becomes rChild
    lRoot->updateHeight();  // lRoot becomes new Root
    return lRoot;
}
inline AVL::Tree AVL::lRotate( Tree root ) {
    Tree rRoot = root->r;
    root->r = rRoot->l;
    rRoot->l = root;
    root->updateHeight();   // Root becomes lChild
    rRoot->updateHeight();  // rRoot becomes new Root
    return rRoot;
}
inline AVL::Tree AVL::balance( Tree root ) {
    // rChild becomes abnormal
    if ( root->bIndex() == -2 ) {
        if ( root->r->bIndex() == 1 ) {
            root->r = AVL::rRotate( root->r );
        }
        root = AVL::lRotate( root );
    } else if ( root->bIndex() == 2 ) {
        if ( root->l->bIndex() == -1 ) {
            root->l = AVL::lRotate( root->l );
        }
        root = AVL::rRotate( root );
    }
    root->updateHeight();  // Recusive height update for parent, parent may become abnormal
    return root;
}
inline AVL::Tree AVL::insert( Tree root, int elem ) {
    if ( !root ) {
        return std::make_shared<AVL>( elem );
    }
    if ( elem == root->data ) {
        return root;
    }
    if ( elem > root->data ) {
        root->r = insert( root->r, elem );
    } else {
        root->l = insert( root->l, elem );
    }
    return balance( root );
}
inline AVL::Tree AVL::del( Tree root, int elem ) {
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
    return balance( root );
}
