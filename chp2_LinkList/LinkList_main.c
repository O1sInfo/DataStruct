#include "myheader.h"
#include "LinkList_L.h"

int main(int argc, char const *argv[])
{
	LinkList La;
	ElemType e;
	CreateList_L(&La, 5);
	ListInsert_L(&La, 3, 10);
	ListDelete_L(&La, 5, &e);
	for (int i = 1; i <= 5; ++i)
	{
		GetElem_L(La, i, &e);
		printf("%2d", e);
	}
	return 0;
}