/* @UNIVESRE.COM_20161212_HYe
 * Demonstrates the concepts of TREE ADT.
 */

/* Declare the node of a tree */
typedef struct TreeNode * PtrToNode;
struct TreeNode{
    ElementType Element;
    PtrToNode FirstChild;
    PtrToNode NextSibling;
};