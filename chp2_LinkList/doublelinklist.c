#include "doublelinklist.h"
#include "myheader.h"

Status ListInsert_DuL(DuLinkList *L, int i, ElemType e){
	// 在带头结点的双链循环线性表L中第i个位置之前插入元素e
	DuLinkList p, s;
	if(!(p=GetElemP_DuL(L, i))) // 在L中确定插入位置, p指向第i个元素
		return ERROR;
	if(!(s=(DuLinkList)malloc(sizeof(DuLNode))))
		return ERROR;
	s->data = e;
	s->prior = p->prior;
	p->prior->next = s;
	s->next = p;
	p->prior = s;
	return OK;
}

DuLinkList GetElemP_DuL(DuLinkList *L, int i){
	//
	DuLinkList p = (*L)->next; // 初始化p指向第一个结点
	int j = 1;
	while(p && j<i){
	// 顺指针向后查找，直到p指向第i个元素或p为空
		p = p->next;
		++j;
	}
	if(!p || j>i) return NULL;	//第i个元素不存在
	else return p;	// 存在返回指向第i个元素的指针p
}

Status ListDelete_DuL(DuLinkList *L, int i, ElemType e){
	// 删除带头结点的双链循环表L的第i个元素
	DuLinkList p;
	if(!(p=GetElemP_DuL(L, i))) return ERROR;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}