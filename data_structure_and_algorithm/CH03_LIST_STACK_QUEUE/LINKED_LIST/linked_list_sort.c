/* @UNIVESRE.COM @11292016 @HYe
 * One Direction Loop Linked List:
 * Data Structure. */

 /* 开始排序前, 先准备准备 */
typedef int type_t;

struct node{						//一个结点就是一个结构体;
	type_t data;					//本node的数据;
	struct node * next;				//下一个node的地址;
};

struct list_head{
	struct node * head;				//list_head的数据域, 指向一个head node;
};

typedef struct node Node;
typedef struct list_head List_Header;

/* 排序思路: 每轮排序从待排序链表中选出数据最小的结点,
 * 插入另一个新的空链表的尾部, 同时从待排序链表中将该
 * 结点删除. */
void list_sort(List_Header *listheader){		//参数是一个待排序的list的head node;
	Node *oldHeader = listheader->head;		//node指针值 = head node指针值;
	Node *newHeader = NULL, *newTail = NULL;	//新链表的头指针, 尾指针;
	Node *cursor = NULL;				//遍历的cursor;
	Node *cursor_prev = NULL;			//保存遍历时的前一个结点;
	Node *min = NULL;				//保存最小值结点的地址;
	Node *min_prev = NULL;				//最小值结点的前一个结点地址;

	while(oldHeader != NULL){			//第一重循环: 从head开始遍历, 最后一轮oldHeader指向了list中剩下的最大一个元素了, 而这个元素的next就是为NULL的, 故循环可控;
		min = oldHeader;			//先保存每轮循环第一个结点为最小值;

		/* 1.当前p的一轮循环 */
		for(cursor_prev = oldHeader, cursor = oldHeader->next; cursor != NULL; cursor_prev = cursor, cursor = cursor->next){	//从"剩余"list的第一个结点开始遍历, 同时保存当前结点与前一个结点, 找出更小的值;
			if(cursor->data < min->data){
				min = cursor;		//保存最小结点的地址;
				min_prev = cursor_prev;	//保存最小结点的前一结点的地址;
			}
		}					//一遍for循环下来: 发现这一轮中的最小值node, 为min;

		/* 2.将找到的最小结点min链接到新链表之后 */
		if(newHeader == NULL){			//如果新链表为空: 则min为header;
			newHeader = min;		//newHeader是一个node;
			newTail = min;			//newTail也是一个node;
		}else{
			newTail->next = min;		//tail和min链接起来;
			newTail = min;			//min是新的tail;
		}

		/* 3.新链表添加min后, 移除min在原链表的
		 * 链接关系, 但结构体(内存资源)不删除 */
		if(min == oldHeader){
			oldHeader = oldHeader->next;	//如果min是一开始的头结点, 则新的oldHeader为原oldHeader的next;
		}else{
			min_prev->next = min->next;	//否则, 设置min_prev的next为min的next, 跳过min, 而min已经在第二步加入newHeader的链表中;
		}
	}						//全部node排序结束;

	if(newHeader != NULL){				//如果新链表头存在: 好像是多余的;
		newTail->next = NULL;			//扫尾工作: 全部排序完成, tail的next应设置为NULL;
	}

	listheader->head = newHeader;			//更新原链表head node的地址值为newHeader;
}


/* Linked_List_Merge_1: Normal Merge;
 * Method: 将两个相同类型的链表中的第一个链表的最后
 * 一个node的next值设置为第二个链表的head node的地址. */
void list_merge(List_Header *listheader1, List_Header *listheader2){
	
	Node * cursor = NULL;
	Node * cursor_prev = NULL;

	cursor = listheader1->head;			//获取到了listheader1
	while(cursor != NULL){
		cursor_prev = cursor;
		cursor = cursor->next;
	}
	cursor_prev->next = listheader2->head;		//list1的最后一个node的next赋为list2的head;
}

/* Linked_List_Merge_2: Sequential Merge; 
 * Method: 合并思路与数组中的思路类似. */
void list_merge_by_order(List_Header * dst, List_Header * list1, List_Header * list2){
	Node * newHeader = NULL, *newTail = NULL;	//Helper variable;
	Node * cursor1 = list1->head;
	Node * cursor2 = list2->head;

	/* 1.主体排序部分. */
	while(cursor1 != NULL && cursor2 != NULL){
		if(cursor1->data < cursor2->data){
			if(newHeader == NULL){
				newHeader = cursor1;
				newTail   = cursor1;
				cursor1   = cursor1->next;
			}else{
				newTail->next = cursor1;
				newTail       = cursor1;
				cursor1       = cursor1->next;
			}
		}else{
			if(newHeader == NULL){
				newHeader = cursor2;
				newTail   = cursor2;
				cursor2   = cursor2->next;
			}else{
				newTail->next = cursor2;
				newTail       = cursor2;
				cursor2       = cursor2->next;
			}
		}
	}						//list1和list2中至少有一个已经全部排入了新链表序列中了;

	/* 2.扫尾工作: 主体排序已经完成. */
	if(cursor1 != NULL){				//list1中还有剩余;
		newTail->next = cursor1;
	}

	if(cursor2 != NULL){				//list2中还有剩余;
		newTail->next = cursor2;
	}

	// 要注释掉, 否则会有逻辑错误: 此时的newTail是主体排序部分的tail, 而非扫尾部分更新了的链表的tail;
	// if(newHeader != NULL){
	// 	newTail->next = NULL;
	// }

	dst->head = newHeader;				//没有free掉newHearder(指针)变量, 函数退出后还能访问该地址, 这里没错: 设计精巧.
}
