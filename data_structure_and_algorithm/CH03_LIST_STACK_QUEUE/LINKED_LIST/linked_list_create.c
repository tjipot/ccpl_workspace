/* @UNIVESRE.COM_10252016_HYe
 */
#include <stdio.h>
#include <stdlib.h>

//定义Student结构体, 链表以此为结构体;
typedef struct student{
	int id;
	int score;
	char name[20];
	struct student *next;//保存一个地址, 指向另一个链表结点: 指针变量的大小都是固定的, 内容和其它变量一样, 数值大小上可不一样, 指针怎么了?!
}stu;

void link_create(stu **head, stu *node){
	stu *p_tmp = *head;
	if(*head == NULL){ //二级指针, *head表示保存head node所在地址的那个变量, 判断它的值是否为空(是否有head node的地址);
		*head = node;
		node->next = NULL;
	}else{
		while(p_tmp != NULL){
			p_tmp = p_tmp->next;
		}
		p_tmp->next = node;
		node->next = NULL;
	}
}

void link_print(STU *head){
	while(head != NULL){
		printf("Stu_Name: %s.\n", head->name);
		head = head->next;
	}
}

int main(void){

	int num;
	stu *link_head = NULL, *new_node = NULL;
	printf("Number Of Link Nodes You Want To Create? Typein:");
	scanf("%d", &num);
	for(int i = 0; i < num; i++){
		new_node = (stu*)malloc(sizeof(stu));
		printf("\nNeed Student Name, Id And Score:");
		scanf("%s %d %d", new_node->name, &new_node->id, &new_node->score); //&new_node->name: warning;
		link_create(&link_head, new_node);//把新节点加入到链表中去, 如果链表空, 则创建; 如果链表已有, 则加至末尾;
	}
	link_print(link_head);
	printf("link_create() finished\n");
	return 0;
}