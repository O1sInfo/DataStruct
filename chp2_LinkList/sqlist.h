#define LIST_INIT_SIZE 100	// 顺序链表初始分配大小
#define LISTINCREMENT 10	// 增量空间
typedef struct 
{
	ElemType *elem;
	int length;
	int listsize;
}Sqlist;

Status InitList_Sq(Sqlist *L);
Status ListInsert_Sq(Sqlist *L, int i, ElemType e);
Status ListDelete_Sq(Sqlist *L, int i, ElemType *e);
int LocateElem_Sq(Sqlist L, ElemType e, Status (*compare)(ElemType, ElemType));
void MergeList_Sq(Sqlist La, Sqlist Lb, Sqlist *Lc);