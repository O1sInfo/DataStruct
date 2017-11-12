#include "myheader.h"
#include "StaticLinkList.h"

int LocateElem_SL(SLinkList S, ElemType e){
	//
	int i = S[0].cur;	// i指示表中第i个结点
	while (i && S[i].data != e){
		i = S[i].cur;
	}
	return i;
}

void InitSpace_SL(SLinkList *space){
	// 将一位数组各分量链成一个备用链表，space[0].cur为头指针
	for (int i = 0; i < MAXSIZE-1; ++i)
		(*space)[i].cur = i + 1;
	(*space)[MAXSIZE-1].cur = 0;	// 赋值空指针
}

int Malloc_SL(SLinkList *space){
	// 若备用链表为非空，则返回分配的结点下标，否则返回0
	int i = (*space)[0].cur;
	if (i) (*space)[0].cur = (*space)[i].cur;
	return i;
}

void Free_SL(SLinkList *space, int k){
	// 将下标为k的空闲结点回收到备用链表
	(*space)[k].cur = (*space)[0].cur;
	(*space)[0].cur = k;
}

void difference(SLinkList *space, int *S){
	// 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)并(B-A)的静态链表
	// S为其头指针，假设备用空间足够大，space[0].cur为其头指针
	int r, m, n, b, p, i, k;
	InitSpace_SL(space);	// 初始化备用空间
	*S = Malloc_SL(space);	// 生成S的头结点
	r = *S;					// r指向S的当前最后结点
	scanf("%d,%d", &m,&n);	// 输入A和B的元素个数
	for (int j = 1; j <= m; ++j)
	{
		i = Malloc_SL(space);	// 分配结点
		scanf("%d", (*space)[i].data);	// 输入A的元素值
		(*space)[r].cur = i;		// 插入到表尾
		r = i;
	}
	(*space)[r].cur = 0;	// 尾结点指针为空
	for (int j = 1; j <= n; ++j)
	{
		scanf("%d", &b);
		p = *S;
		k = (*space)[*S].cur; // k指向集合A中第一个结点
		while(k!=(*space)[r].cur && (*space)[k].data!=b){	// 在当前表中查找,k指向与b相等的元素位置
			p = k;					// p为其前一个位置
			k = (*space)[k].cur;
		}
		if (k==(*space)[r].cur){	// 当前表中不存在该元素，插入在r所指结点之后，且r的位置不变
			i = Malloc_SL(space);
			(*space)[i].data = b;
			(*space)[i].cur = (*space)[r].cur;
			(*space)[r].cur = i;
		}
		else{	// 该元素已在表中，删除之
			(*space)[p].cur = (*space)[k].cur;	// 删除第k个元素
			Free_SL(space, k);
			if(r == k) r = p;	// 若删除的是r所指的结点，则需要修改尾指针
		}
	}
}