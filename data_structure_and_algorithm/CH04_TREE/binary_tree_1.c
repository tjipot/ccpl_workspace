/* @UNIVESRE.COM_12012016_HYe
 * Description: Basic Concepts Of Binary Tree.
 * Include: Node Structure, Node Creation, 
 * 1202_CHANGE_TABS_4. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Basic Structure: Tree Node */
typedef int type_t;
typedef struct node{
	type_t data;
	struct node * left;
	struct node * right;
}Node;

/* Node Creation: 创建一个结点;
 * Input: an int;
 * Output: node's address; */
Node * node_create(type_t data){
	Node * p = (Node *)malloc(sizeof(Node));
	assert(p);						//断言, p是否成功, 不成功就退出(因为是断言)?!
	p->data  = data;					//基本数据1: data;
	p->left  = NULL;					//基本数据2: left;
	p->right = NULL;					//基本数据3: right;
	return p;
}

/* Node Insertion(Normal Method): left <= right;
 * Input: a tree root, an insertion node;
 * Output: none; */
void node_insert(Node ** tree_trace, Node * insertion){
	if(*tree_trace == NULL){				//If there is no node right now: the case of insertion node is the first node;
		*tree_trace = insertion;
	}else{
		Node* tmp = *tree_trace;			//一开始tmp为传进来的root值;
		Node* parent = NULL;				//需记录操作的node的上一个node;
		while(tmp != NULL){				//判断上一次传递时的node是否为叶子;
			parent = tmp;				//临时记录下操作node的parent node;
			if(insertion->data <= tmp->data){	//传入的insertion值与tmp值比较;
				tmp = tmp->left;		//操作node被传左边去了;
			}else{
				tmp = tmp->right;		//操作node被传右边去了;
			}
		}

		if(insertion->data <= parent->data){		//while已经结束, 该插入node了;
			parent->left = insertion;		//insertion小, 放左边;
		}else{
			parent->right = insertion;		//insertion大, 放右边;
		}						//insertion地址已被正确链接, 完成任务;
	}


/* Node Insertion(Recursion): Incisive! 
 * 每一个结点的操作都是相同的判断, 这就为递归
 * 提供了可能. */
void node_insert_recursion(Node ** root, Node * insertion){
	if(*root == NULL){					//终止条件: 传进来的"root"(是它以下结点的root)为叶子的一个分支(左/右), 就放置insertion结点, 精辟;
		*root = insertion;				//If finally find the leaf, insert the node(insertion) here;
	}else{
		if(insertion->data <= (*root)->data){		//insertion不会在递归中改变状态, 可以一直比较;
			node_insert_recursion(&((*root)->left), insertion);//The root's left sub-root becomes a new root;
		}else{
			node_insert_recursion(&((*root)->right), insertion);//The root's right sub-root becomes a new root;
		}
	}
}

/* Tree Traverse: about the root order,
 * preorder: root, left, right,
 * midorder: left, root, right,
 * postorder: left, right, root, 
 * Input: address of tree root,
 * Output: void. */
void traverse_preorder(Node *tree){
	if(tree == NULL){
		//printf("Leaf.\n");
		return;
	}else{
		printf("%d ", tree->data);			//Preorder: before left and right;
		traverse_preorder(tree->left);			//Left after root;
		traverse_preorder(tree->right);			//Right after left;
	}
}
void traverse_midorder(Node *tree){
	if(tree == NULL){
		//printf("Leaf.\n");
		return;
	}else{
		traverse_preorder(tree->left);			//Midorder: root in the middle;
		printf("%d ", tree->data);			//Root after left;
		traverse_preorder(tree->right);			//Right after root;
	}
}
void traverse_postorder(Node *tree){
	if(tree == NULL){
		//printf("Leaf.\n");
		return;
	}else{
		traverse_postorder(tree->left);			//Postorder: root in the last;
		traverse_postorder(tree->right);		//Right after left;
		printf("%d ", tree->data);			//Root after right;
	}
}

/* Node Searching: normal search,
 * Input: address of root, the data value,
 * Output: the node's address. */
Node * node_search(Node * tree, int data){
	Node * p = tree;
	while(p != NULL){					//Normal search: 循环传递查找;
		if(p->data == data){
			return p;
		}else if(data < p->data){
			p = p->left;
		}else{
			p = p->right;
		}
	}
	return p;						//如果在这里函数返回了, 说明没有找到相匹配的值: p=NULL;
}

/* Node Searching: recursion,
 * Input: address of root, the data value,
 * Output: the node's address. */
Node * node_search_recursion(Node * tree, int data){
	if(tree == NULL){
		return NULL;
	}else if(tree->data == data){
		return tree;
	}else if(tree->data >  data){
		return node_search_recursion(tree->left,  data);	//Left作为新值传进去, data不变;
	}else{
		return node_search_recursion(tree->right, data);	//Right作为新值传进去, data不变;
	}
}

/* Tree Height:
 * Input: address of root,
 * Output: tree height. */
int tree_height(Node * tree){					//此函数理解的关键是旧的return值到新的嵌套环境中又加1然后又返回, 而不是表面上的right/left只加1;
	if(tree == NULL){
		return 0;
	}
	int left  = tree_height(tree->left);			//先获得一个树高的返回值(都是上一次的返回), 再进行下一步树高累加;
	int right = tree_height(tree->right);

	if(left < right){					//当在一个叶子结点时, 肯定是left+1的;
		return right + 1;
	}else{
		return left  + 1;
	}
}

/* Delete Node:
 * Input:  address of root's address, the deletion value,
 * Output: void. */
void node_deletion(Node ** root, int data){
	Node * find = *root;					//The target node;
	Node * parent = NULL;					//find's parent node;
	Node * delete = NULL;					//The node to delete;

	/* Find the node to be deleted and its parent */
	while(find != NULL){					//find一开始是指向root的;
		if(find->data == data){				//找到data了;
			break;
		}else if(data < find->data){
			parent = find;				//记录下parent;
			find = find->left;			//向左边寻找;
		}else{
			parent = find;				//记录下parent;
			find = find->right;			//向右边寻找;
		}
	}							//while结束;

	if(find == NULL){					//find==NULL, 及时没发现值对应的node;
		return;
	}else if(find->left == NULL){				//1.find没有左子树, 直接移植右边的数据;
		if(parent == NULL){				//parent==NULL, 说明没有parent, 说明是root;
			*root = find->right;			//无左无父, 直接设置right为root;
		}else{
			if(parent->left == find){		//find在parent左边:
				parent->left = find->right;	//设置find的right为parent的left, 即, 取代find;
			}else{
				parent->right = find->right;	//find在parent右边: 设置find的right为parent的right;
			}
		}
		free(find);					//新的链接关系形成, 删除find, 并return;
		return;
	}else if(find->left->right == NULL){			//2.find的左子树没有右结点: 删除find的left;
		delete = find->left;				//临时保存;
		find->data = delete->data;			//把find的data设置成find的left的data: 覆盖;
		find->left = delete->left;			//把find的left设置成left的left;
		free(delete);					//删除delete
		return;						//这个if的操作相当于: 把find的值覆盖成find的left的, 然后find的left链接成find的left的left, 然后删除find的left内存空间;
	}else{
		parent = find->left;				//3.find的左子树有右结点: 先保存find的left为parent;
		delete = parent->right;				//保存find的left的right为delete;
		while(delete->right != NULL){			//一直遍历到find的left的最大值node: 即find->left->right->...->right;
			parent = delete;			//循环查找: 直到delete的right为NULL, 即叶子;
			delete = delete->right;
		}
		parent->right = delete->left;			//此时delete已经是叶子, 将delete的left设置为delete的parent的right(不论delete的是否为NULL, 都无紧要关系);
		find->data = delete->data;			//快要功到渠成: 将叶子delete的data覆盖过去;
		free(delete);					//删除delete: 原find结点(的对象: 结构体)不必去删除, 而是要删除叶子结点的结构体;
		return;						//终于返回了;
	}
}

/* Delete Tree:
 * Input: address of root's address,
 * Output: void. */
void tree_deletion(Node** root){
	if(*root == NULL){					//当遇到了叶子结点的left和right, 就返回;
		return;
	}

	Node *tree = *root;
	tree_deletion(&(tree->left));				//先左后右, 不断递归;
	tree_deletion(&(tree->right));				//左边返回了, 轮到右边了;
	printf("Deleted %d\n", tree->data);			//同一个结点的左右两边也返回了: 那么可以进行删除了;
	free(tree);						//数据删除之后, 可以删除内存空间了;
	*root = NULL;						//避免野指针: 设置指针为空咯;
}


/* Test The Tree */
int main(void){

	return 0;
}
