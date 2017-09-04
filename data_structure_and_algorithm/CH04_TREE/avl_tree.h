/* @UNIVESRE.COM_20161218_HYe
 * Demonstrates the concepts of AVL Tree. */

#ifndef _AvlTree_H

struct AvlNode;
typedef struct AvlNode * Position;
typedef struct AvlNode * AvlTree;

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(ElementType X, AvlTree T);
AvlTree Delete(ElementType X, AvlTree T);
ElementType Retrieve(Position P);

#endif /* _AvlTree_H */