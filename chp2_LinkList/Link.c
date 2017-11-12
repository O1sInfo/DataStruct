#include "myheader.h"
#include "Link.h"

Status MakeNode(Link *p, ElemType e){
	// 分配由p指向的值为e的结点，并返回OK;若失败返回ERROR
	(*p) = (Link)malloc(sizeof(LNode));
	if(!(*p))
		return ERROR;
	(*p)->data = e;
	return OK;
}

void FreeNode(Link *p){
	// 释放p所指的结点
	free(*p);
	*p = NULL;
}

Status InitList(LinkList *L){
	// 构造一个空的线性链表L
	Link p;
	p = (Link)malloc(sizeof(LNode));
	if(p)
	{
		p->next = NULL;
		(*L).head = (*L).tail = p;
		(*L).len = 0;
		return OK;
	}
	else
		return ERROR;
}

Status ClearList(LinkList *L){
	// 将L表重置为空表，并释放原链表的结点空间
	Link p, q;
	if ((*L).head != (*L).tail)	// 头结点不是尾结点，即表不为空
	{
		p = q = (*L).head->next;
		(*L).head->next = NULL;
		while(p!=(*L).tail){	// 依次释放结点
			p = q->next;		// 注意这里要用两个指针
			free(q);
			q = p;
		}
		free(q);	// 释放尾结点
		(*L).tail = (*L).head;	// 头结点是尾结点，表尾空
		(*L).len = 0;
	}
	return OK;
}

Status DestoryList(LinkList *L){
	// 销毁线性链表L, L不在存在
	ClearList(L);	// 将L清空
	FreeNode(&(*L).head);	// (*L).head = NULL
	(*L).tail = NULL;
	(*L).len = 0;
	return OK;
}

Status InsList(LinkList *L, Link h, Link s){	// 形参增加L,因为需要修改L
	// 已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
	s->next = h->next;
	h->next = s;
	if(h==(*L).tail)
		(*L).tail = h->next;
	(*L).len++;
	return OK;
}

Status DelFirst(LinkList *L, Link h, Link *q){	// 形参增加L,因为需修改L
	// h指向L的头结点，删除链表中的第一个结点并以q返回
	// 若链表为空(h指向尾结点)，q=NULL，返回FALSE
	*q = h->next;
	if(*q)	// 链表非空
	{
		h->next = (*q)->next;
		if(!h->next)		// 删除尾结点
			(*L).tail=h;	// 修改尾指针
		(*L).len--;
		return OK;
	}
	else
		return FALSE;	// 链表空
}

Status Append(LinkList *L, Link s){
	// 将指针s所指的一串结点连接在线性表L的尾结点之后，并将L的尾指针指向新的尾结点
	int i = 1;
	(*L).tail->next = s;	// 连接第一个结点，i=1
	while(s->next){			// 计算结点个数
		s = s->next;	
		i++;
	}
	(*L).tail = s;
	(*L).len += i;
	return OK;
}

Position PriorPos(LinkList L, Link p){
	// 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，若无则返回NULL
	Link q = L.head->next;	// q指向第一个结点
	if(q==p)	// 无前驱
		return NULL;
	else{
		while(q->next != p){
			q = q->next;
		return q;
		}
	}
}


Position NextPos(Link p){
	// 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置，若无则返回NULL
	return p->next;
}

Status Remove(LinkList *L, Link *q){
	// 删除线性链表L的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
	Link p = (*L).head;
	if ((*L).len = 0){	// L为空表	
		*q = NULL;
		return FALSE;
	}
	while(p->next != (*L).tail)	// p指向尾结点的前一个结点
		p = p->next;
	*q = (*L).tail;
	p->next = NULL;
	(*L).tail = p;
	(*L).len--;
	return OK;
}

Status InsBefore(LinkList *L, Link *p, Link s){
	// 已知p指向线性表中的一个结点，将s所指结点插入在p所指结点之前，并修改p指向新的结点
	Link q=PriorPos(*L, *p);	// q是p的前驱
	if(!q)	q = (*L).head;	// p无前驱
	s->next = *p;
	q->next = s;
	*p = s;
	(*L).len++;
	return OK;
}

Status InsAfter(LinkList *L, Link *p, Link s){
	// 已知p指向线性表中的一个结点，将s所指结点插入在p所指结点之后，并修改p指向新的结点 
	if(*p==(*L).tail)	// p指向尾结点，修改尾结点
		(*L).tail = s;
	s->next = (*p)->next;
	(*p)->next = s;
	*p = s;
	(*L).len++;
	return OK;
}

Status SetCurElem(LinkList *L, Link p, ElemType e){
	// 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
	p->data = e;
	return OK;
}

Status GetCurElem(Link p){
	// 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
	return p->data;
}

Status ListEmpty(LinkList L){
	// 若链表为空，返回True, 否则False
	return L.len? FALSE:TRUE;
}

int ListLength(LinkList L){
	// 返回线性表L中的元素个数
	return L.len;
}

Position GetHead(LinkList L){
	// 返回线性表L的头结点的位置
	return L.head;
}

Position GetTail(LinkList L){
	// 返回线性链表L的尾结点的位置
	return L.tail;
}

Status LocatePos(LinkList L, int i, Link *p){
	// 返回p指示L中的第i个结点，i值不合法时返回ERROR
	int j;
	if(i<0 || i>L.len) return ERROR;
	else{
		*p = L.head;	// (*p)从头开始偏移到第i个元素
		for(j=1; j<=i; j++)
			*p = (*p)->next;
		return OK;
	}
}

Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType)){
	// 返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置，若不存在这样的元素，则返回NULL
	Link p = L.head;
	do
		p = p->next;
	while(p&&!(compare)(p->data, e));	// 没到表尾并且没找到满足关系到额元素
	return p;
}

Status LocateTraverse(LinkList L, void(*visit)(ElemType)){
	// 依次对L的每个数据元素调用visit()函数。一旦visit()失败，则操作失败
	Link p = L.head->next;
	for (int j=1; j<=L.len; j++)
	{
		visit(p->data);
		p = p->next;
	}
	return OK;
}

Status OrderInsert(LinkList *L, ElemType e, int (*comp)(ElemType, ElemType)){
	// 已知L为有序线性链表，将元素e按非降序(或有序函数comp的约定)插入在L中(用于一元多项式)
	Link o,p,q;
	q = (*L).head;
	p = q->next;
	while(p!=NULL && (comp)(p->data, e)<0){	// p不是表尾且元素值小于e
		q = p;		// q为p的前驱，即指向最后一个满足关系的元素
		p = p->next;
	}
	o = (Link)malloc(sizeof(LNode));
	o->data = e;
	q->next = o;
	o->next = p;
	(*L).len++;
	if(!p)	(*L).tail = o;	// 插在表尾
	return OK;	
}

Status LocateElemP(LinkList L,ElemType e,Position *q,int(*compare)(ElemType,ElemType)){
	// 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中
	// 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数
	// compare()取值>0的元素的前驱的位置。并返回FALSE。用于一元多项式
	Link p = L.head,pp;
	do{
		pp = p;		// pp为p的前驱
		p = p->next;
	}while(p && (compare(p->data,e)<0));	// 没到表尾且p->data.expn<e.expn
	if(!p || compare(p->data,e)>0){	// 到表尾或compare(p->data,e)>0
		*q = pp;
		return FALSE;
	}
	else{
		*q = p;
		return TRUE;
	}
}