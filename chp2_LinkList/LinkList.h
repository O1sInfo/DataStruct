typedef struct LNode
{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

Status CreateList_L(LinkList *L, int n);
Status ListDelete_L(LinkList *L, int i, ElemType *e);
Status ListInsert_L(LinkList *L, int i, ElemType e);
Status GetElem_L(LinkList L, int i, ElemType *e);
Status MergerList_L(LinkList *La, LinkList *Lb, LinkList *Lc);