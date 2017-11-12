#include "myheader.h"
#include "ListLink_L.h"

Status GetElem_L(LinkList L, int i, ElemType *e){
	//
	LNode *p = L->next; // 初始化p指向第一个结点
	int j = 1;
	while(p && j<i){
	// 顺指针向后查找，直到p指向第i个元素或p为空
		p = p->next;
		++j;
	}
	if(!p || j>i) return ERROR;	//第i个元素不存在
	*e = p->data;			// 取第i个元素
	return OK;
}

Status ListInsert_L(LinkList *L, int i, ElemType e){
	//
	LNode *p = *L, *s;
	int j = 0;
	while(p && j<i-1){
	// 寻找第i个结点, 并让p指向其前驱
		p = p->next;
		++j;
	}
	if(!p || j>i-1) return ERROR;
	s = (LinkList)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

Status ListDelete_L(LinkList *L, int i, ElemType *e){
	//
	LNode *p = *L, *q;
	int j = 0;
	while(p->next && j<i-1){
		// 寻找第i个结点, 并让p指向其前驱
		p = p->next;
		++j;
	}
	if(!p || j>i-1) return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

Status CreateList_L(LinkList *L, int n){
	// 表头插入法
	// 逆位序输入n个元素的值, 建立带表头结点的单链线性表L
	LinkList p;
	(*L) = (LinkList)malloc(sizeof(LNode));
	(*L)->next = NULL;
	for (int i = n; i > 0; --i)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &(p->data));
		p->next = (*L)->next;
		(*L)->next = p;
	}
}
/*
Status CreateList_L(LinkList *L, int n){
	// 表尾插入法
	// 顺位序输入n个元素的值, 建立带表头结点的单链线性表L
	LinkList p, tail;
	(*L) = (LinkList)malloc(sizeof(LNode));
	tail = (*L);	// 设置表尾
	for (int i = n; i > 0; --i)
	{
		p = (LinkList)malloc(sizeof(LNode));
		scanf("%d", &(p->data));
		tail->next = p;
		tail = p;
	}
	tail->next = NULL;
	return OK;
}
*/
Status MergerList_L(LinkList *La, LinkList *Lb, LinkList *Lc){
	// 已知单链线性表La和Lb的元素按值非递减排列
	LinkList pa = La->next;
	LinkList pb = Lb->next;
	LinkList pc = Lc = La;		// 用La的头结点作为Lc的头结点
	while(pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;	// pc指向最后一个结点
			pa = pa->next;
		}
		else
		{
			pc-next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc-next = pa?pa:pb;
	free(Lb);
}