//	1
typedef struct 
{
	int *elem;
	int length;
	int listsize;
}Sqlist;

int Compare(Sqlist A, Sqlist B){
	// 根据规则比较A, B的大小
	int n = A.length;
	int m = B.length;
	int i;
	if(n <= m){
		for(i = 0; i < n; ++i)
			if(A.elem[i] > B.elem[i])
				return 1;
			else{
				if(A.elem[i] < B.elem[i])
					return -1;
				else
					continue;
				}
		if(i == n)
			return 0;
	}
	else
		return 1;
}

//	2
typedef struct 
{
	ElemType *elem;
	int length;
	int listsize;
}Sqlist;

void Reverse(Sqlist *L){
	// 在原表的存储空间内将顺序线性表逆置
	int len;
	ElemType temp;
	for(int i = 0; i < len/2; ++i){
		temp = (*L).elem[i];
		(*L).elem[i] = (*L).elem[len-1 - i];
		(*L).elem[len-1 - 1] = temp;
	}
}

typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

void Reverse(LinkList *L){
	// 在原表的存储空间内将线性链性表逆置(就地插入)
	// 头插法:表中节点从原链表中依次“删除”，再逐个插入逆置链表的表头
	LinkList p, q;
	p = (*L)->next;		// 保存第一个结点
	(*L)->next = NULL;	// 头结点next域置空
	while(p){
		q = p;
		p = p->next
		q->next = (*L)->next;
		(*L)->next = q; 
	}
}

// 	5
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

void MergeDown(LinkList A, LinkList B, LinkList *C){
	// 已知A,B为递增有序的单链表, 将A,B归并为一个按递减排列的单链表C中
	// 取A,B中较小元素按头插法插入C中
	LinkList pa = A->next;
	LinkList pb = B->next;
	LinkList pc;
	if(!((*C) = (LinkList)malloc(sizeof(LNode))))
		exit(OVERFLOW);
	(*C)->next = NULL;		// 初始化C的头结点
	while(pa && pb)
	{
		if (pa->data <= pb->data)
		{
			pc = pa;
			pa = pa->next;
			pc->next = (*C)->next;	// pc指向最后一个结点
			(*C)->next = pc;
		}
		else
		{
			pc = pb;
			pb = pb->next;
			pc->next = (*C)->next;
			(*C)->next = pc;
		}
	}
	while(pa){
		pc = pa;
		pa = pa->next;
		pc->next = (*C)->next;
		(*C)->next = pc;
	}
	while(pb){
		pc = pb;
		pb = pb->next;
		pc->next = (*C)->next;
		(*C)->next = pc;
	}
}

//	8
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

void DeletePrior(LinkList *S){
	// 删除无头无尾指针的循环单链表(len>1)中S所指的元素的直接前驱
	LinkList p;
	for(p = *S; p->next->next == *S; p = p->next);
	p->next = *S;
}