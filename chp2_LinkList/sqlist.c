#include "myheader.h"
#include "sqlist.h"

Status InitList_Sq(Sqlist *L){
	// 初始化顺序链表 类似数组
	L->elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L->elem) exit(OVERFLOW);
	L->length = 0;
	L->listsize = LIST_INIT_SIZE;
	return OK;
}

Status ListInsert_Sq(Sqlist *L, int i, ElemType e){
	// T = O(f(n)) = O(n)
	ElemType *newbase, *q, *p;
	if (i<1 || i>L->length+1) return ERROR;
	if (L->length >= L->listsize)	// 分配空间已满，重新分配新的空间
	{
		newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT)*sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		L->elem = newbase;
		L->listsize += LISTINCREMENT;
	}
	q = &(L->elem[i-1]);	// q指向第i个元素
	for (p = &(L->elem[L->length-1]); p >= q; --p)	// 移动第i个元素之后的元素
		*(p+1) = *p;	// 后移一位
	*q = e;	// 插入e
	++L->length;
	return OK;
}

Status ListDelete_Sq(Sqlist *L, int i, ElemType *e){
	// T = O(f(n)) = O(n)
	// 删除第i个元素，用e返回其值
	ElemType *p, *q;
	if (i<1 || i>L->length) return ERROR;
	p = &(L->elem[i-1]);
	*e = *p;
	q = L->elem + L->length - 1;	// q指向尾结点
	for (++p; p<=q; ++p) *(p-1) = *p;	// 把第i个元素之前的元素向前移动一位
	--L->length;
	return OK;
}

int LocateElem_Sq(Sqlist L, ElemType e, Status (*compare)(ElemType, ElemType)){
	//
	int i = 1;
	ElemType *p = L.elem;
	while(i<=L.length && !(*compare)(*p++, e)) ++i;
	if(i<=L.length) return i;
	else return 0;
}

void MergeList_Sq(Sqlist La, Sqlist Lb, Sqlist *Lc){
	//
	ElemType *pa, *pb, *pc, *pa_last, *pb_last;
	pa = La.elem;
	pb = Lb.elem;
	Lc->listsize = Lc->length = La.length + Lb.length;
	pc = Lc->elem = (ElemType*)malloc(Lc->length*sizeof(ElemType));
	if(!Lc->elem) exit(OVERFLOW);
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while(pa<=pa_last && pb<=pb_last){
		if(*pa <= *pb) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while(pa<=pa_last) *pc++ = *pa++;
	while(pb<=pb_last) *pc++ = *pb++;
}
