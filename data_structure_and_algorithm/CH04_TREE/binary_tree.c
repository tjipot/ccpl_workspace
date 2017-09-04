/* @UNIVESRE.COM_20161218_HYe
 * Demonstrates the concepts of Binary Tree. */

/* Declare the node of a binary tree */
typedef struct TreeNode * PtrToNode;
typedef struct PtrToNode Tree;

/* A node of A Binary Tree */
struct TreeNode{
    ElementType Element;
    Tree Left;
    Tree Right;
};