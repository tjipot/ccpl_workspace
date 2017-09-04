/* @UNIVESRE.COM_1203_HYe
 * Dual_Linked_List */
#include <stdlib.h>

/* 基本结点结构定义 */
typedef int type_t;

/* 双向链表的一个结点 */
struct node{
	type_t data;
	struct node * next;
	struct node * prev;
};

struct list_header{
	struct node * header;
};

typedef struct node NODE;
typedef struct list_header LIST_HEADER;
/* 结束: 双向链表基本结构定义完成 */

/* Node Deletion In Dual_Linked_List
 * Attention: unsafe. */
void node_delete(LIST_HEADER * list, NODE * cursor){
	if(cursor->prev == NULL){			//如果cursor是head node;
		list->header = cursor->next;
		cursor->next->prev = NULL;	
	}else if(cursor->next == NULL){			//如果cursor是tail node;
		cursor->prev->next = NULL;
	}else{						//如果是中间的node: 直接更新该结点的前向结点的next值和后向结点的prev值;
		cursor->prev->next = cursor->next;
		cursor->next->prev = cursor->prev;	//cursor->prev->next?!;
	}

	free(cursor);					//直接清除指针指向的内存实体;
}


/* 如果没有定义main函数, 则编译器无法生成符号"_main", 而"_main"是linker需要link的程序运行入口;
 * Undefined symbols for architecture x86_64:
 *   "_main", referenced from:
 *     implicit entry/start for main executable
 * ld: symbol(s) not found for architecture x86_64
 * clang: error: linker command failed with exit code 1 (use -v to see invocation) */
int main(void){


	return 0;
}
