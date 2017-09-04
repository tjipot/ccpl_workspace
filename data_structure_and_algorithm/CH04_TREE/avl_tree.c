/* @UNIVESRE.COM_20161218_HYe
 * Demonstrates the concepts of AVL Tree. */

#include "avl_tree.h"

/* Declare the node of an avl tree */
struct AvlNode{
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};