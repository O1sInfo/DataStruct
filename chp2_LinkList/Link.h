typedef struct LNode
{
	// 结点类型
	ElemType data;
	struct LNode *next;
}LNode, *Link, *Position;

typedef struct 
{
	// 链表类型
	Link head, tail;	// 分别指向线性链表中的头结点和最后一个结点
	int len;			// 指示线性链表中数据的元素的个数
}LinkList;



Status LocateTraverse(LinkList L, void(*visit)(ElemType));
// 依次对L的每个数据元素调用visit()函数。一旦visit()失败，则操作失败
Status MakeNode(Link *p, ElemType e);
// 分配由p指向的值为e的结点，并返回OK;若失败返回ERROR
void FreeNode(Link *p);
// 释放p所指的结点
Status InitList(LinkList *L);
// 构造一个空的线性链表L
Status ClearList(LinkList *L);
// 将L表重置为空表，并释放原链表的结点空间
Status DestoryList(LinkList *L);
// 销毁线性链表L, L不在存在
Status InsList(LinkList *L, Link h, Link s);
// 已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
Status DelFirst(LinkList *L, Link h, Link *q);
// h指向L的头结点，删除链表中的第一个结点并以q返回
// 若链表为空(h指向尾结点)，q=NULL，返回FALSE
Status Append(LinkList *L, Link s);
// 将指针s所指的一串结点连接在线性表L的尾结点之后，并将L的尾指针指向新的尾结点
Position PriorPos(LinkList L, Link p);
// 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，若无则返回NULL
Position NextPos(Link p);
// 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置，若无则返回NULL
Status Remove(LinkList *L, Link *q);
// 删除线性链表L的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Status InsBefore(LinkList *L, Link *p, Link s);
// 已知p指向线性表中的一个结点，将s所指结点插入在p所指结点之前，并修改p指向新的结点
Status InsAfter(LinkList *L, Link *p, Link s);
// 已知p指向线性表中的一个结点，将s所指结点插入在p所指结点之后，并修改p指向新的结点
Status SetCurElem(LinkList *L, Link p, ElemType e);
// 已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
Status GetCurElem(Link p);
// 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
Status ListEmpty(LinkList L);
// 若链表为空，返回True, 否则False
int ListLength(LinkList L);
// 返回线性表L中的元素个数
Position GetHead(LinkList L);
// 返回线性表L的头结点的位置
Position GetTail(LinkList L);
// 返回线性表L的尾结点的位置
Status LocatePos(LinkList L, int i, Link *p);
// 返回p指示L中的第i个结点，i值不合法时返回ERROR
Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType));
// 返回线性链表L中第1个与e满足函数compare()判定关系的元素的位置，若不存在这样的元素，则返回NULL
Status LocateTraverse(LinkList L, void(*visit)(ElemType));
// 依次对L的每个数据元素调用visit()函数。一旦visit()失败，则操作失败
Status OrderInsert(LinkList *L, ElemType e, int (*comp)(ElemType, ElemType));
// 已知L为有序线性链表，将元素e按非降序(或有序函数comp的约定)插入在L中(用于一元多项式)
Status LocateElemP(LinkList L,ElemType e,Position *q,int(*compare)(ElemType,ElemType));
// 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中
// 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数
// compare()取值>0的元素的前驱的位置。并返回FALSE。用于一元多项式