#define MAXSIZE 100

typedef struct 
{
	ElemType data;
	int cur;
}component, SLinkList[MAXSIZE];
 
int LocateElem_SL(SLinkList S, ElemType e);
void InitSpace_SL(SLinkList *space);
int Malloc_SL(SLinkList *space);
void Free_SL(SLinkList *space, int k);
void difference(SLinkList *space, int *S);