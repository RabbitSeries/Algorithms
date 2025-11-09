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
    static Tree del( Tree tree, int elem );  // Return the new root
    static void insert_rebalance( Node elem, Tree& tree );
    static void del_rebalance( Node x, Node x_parent, Node y, Tree& tree );
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
inline RBT::Tree RBT::del( Tree tree, int elem ) {
    Node p = tree, parent = nullptr;
    while ( p ) {
        if ( elem == p->data ) {
            break;
        } else if ( elem < p->data ) {
            parent = p;
            p = p->l;
        } else {
            parent = p;
            p = p->r;
        }
    }
    if ( !p ) {
        return tree;
    }
    // ==========================================================================BEGIN TRANSPLANT
    Node y = p;        // will be adjusted to the real deleted node
    Node x{};          // Possible child of deleted node y
    Node x_parent{};   // The parent of x after swap
    if ( !y->l )       // p has at most one non-null child. y == z.
        x = y->r;      // x might be null.
    else if ( !y->r )  // p has exactly one non-null child. y == z.
        x = y->l;      // x is not null.
    else {
        // p has two non-null children.  Set __y to
        y = y->r;    //   p's successor.  x might be null.
        while ( y->l )
            y = y->l;
        x = y->r;
    }
    if ( y != p ) {  // y: p's right successor, x: successor's right child
        // relink y in place of p.  y is p's successor
        p->l->parent = y;
        y->l = p->l;
        if ( y != p->r ) {
            x_parent = y->parent.lock();
            if ( x )
                x->parent = y->parent;
            y->parent.lock()->l = x;  // __y must be a child of l
            y->r = p->r;
            p->r->parent = y;
        } else
            x_parent = y;
        if ( tree == p )
            tree = y;
        else if ( p->parent.lock()->l == p )
            p->parent.lock()->l = y;
        else
            p->parent.lock()->r = y;
        y->parent = p->parent;
        std::swap( y->color, p->color );
        y = p;
        // __y now points to node to be actually deleted
    } else {  // __y == p, y is leave, x: y's left or right child
        x_parent = y->parent.lock();
        if ( x )
            x->parent = y->parent;
        if ( tree == p )
            tree = x;
        else if ( p->parent.lock()->l == p )
            p->parent.lock()->l = x;
        else
            p->parent.lock()->r = x;
    }
    del_rebalance( x, x_parent, y, tree );
    return tree;
}
/**
 * !(black)x means x is black or null
 * */
/*==============================================================================================================================================*/
/*             O <- x_parent(black)      O (black)                                                                                              */
/*            / \                  =>   /                                                                                                       */
/*(black)x-> O   O <- w (red)          O <- x_parent (red)                                                                                      */
/*              / \                   / \                                                                                                       */
/*(must two b) O   O    (black) x -> O   O <- w (must be black)                                                                                 */
/*                                      / \                                                                                                     */
/*                                     O   O    left is still b shorter than right                                                              */
/*==============================================================================================================================================*/
/*             O <- x_parent(red or black)                                                                                                      */
/*            / \                                                                                                                               */
/*(black)x-> O   O <- w (black)                                                                                                                 */
/*              / \                                                                                                                             */
/*             O   O (child: red, black, empty)                                                                                                 */
/*==============================================================================================================================================*/
/*             O <- x_parent(red or black)                            O <- x_parent(red or black)                                               */
/*            / \                                                    / \                                                                        */
/*(black)x-> O   O <- w (black, then non leave)    =>    (black)x-> O   O <- w (dye red, right minus black height, done, x go up,               */
/*              / \                                                    / \      if x_parent is black continue to balance dual black             */
/*             O   O (child: black, empty)                            O   O     or else dye parent to black and finish)                         */
/*==============================================================================================================================================*/
/*             O <- x_parent(red or black)                            O <- x_parent(red or black)                                               */
/*            / \                                                    / \                                                                        */
/*(black)x-> O   O <- w (black, then non leave)    =>    (black)x-> O   O <- w (roate to black)                                                 */
/*              / \                                                    / \                                                                      */
/*             O   O (child: at least one red)                        O   O (ensures w->r is red)                                               */
/*                                                             left is still b shorter than right                                               */
/*==============================================================================================================================================*/
/*             O <- x_parent(red or black) <- lRotate                      O <- w(red or black)                                                 */
/*            / \                                                         / \                                                                   */
/*(black)x-> O   O <- w (black, dye to parent),   =>   x_parent(black)-> O   O black(ensures r bHeight stays unchanged)                         */
/*              / \                         (Increase left bHeight)     / \                                                                     */
/*             O   O <- red(go black)                       (black)x-> O   O                                                                    */
/*==============================================================================================================================================*/
inline void RBT::del_rebalance( Node x, Node x_parent, Node y, Node& tree ) {
    if ( y->color == red ) {
        return;
    }
    while ( x != tree && ( !x || x->color == black ) ) {  // x is null(black) or black, deleted y is also black
        if ( x == x_parent->l ) {
            Node w = x_parent->r;                         // sibling of x
            if ( w->color == red ) {
                w->color = black;
                x_parent->color = red;
                lRotate( x_parent, tree );
                w = x_parent->r;
            }
            if ( ( !w->l || w->l->color == black ) &&
                 ( !w->r || w->r->color == black ) ) {
                w->color = red;
                x = x_parent;
                x_parent = x_parent->parent.lock();
            } else {
                if ( !w->r || w->r->color == black ) {
                    w->l->color = black;
                    w->color = red;
                    rRotate( w, tree );
                    w = x_parent->r;
                }
                w->color = x_parent->color;
                x_parent->color = black;
                w->r->color = black;
                lRotate( x_parent, tree );
                break;
            }
        } else {  // same as above, with r <-> l.
            Node w = x_parent->l;
            if ( w->color == red ) {
                x_parent->color = red;
                w->color = black;
                rRotate( x_parent, tree );
                w = x_parent->l;
            }
            if ( ( !w->l || w->l->color == black ) &&
                 ( !w->r || w->r->color == black ) ) {
                w->color = red;
                x = x_parent;
                x_parent = x_parent->parent.lock();
            } else {
                if ( !w->l || w->l->color == black ) {
                    w->color = red;
                    w->r->color = black;
                    lRotate( w, tree );
                    w = x_parent->l;
                }
                w->color = x_parent->color;
                w->l->color = x_parent->color = black;
                rRotate( x_parent, tree );
                break;
            }
        }
    }
    if ( x ) {
        x->color = black;  // re-dye to black}
    }
}
