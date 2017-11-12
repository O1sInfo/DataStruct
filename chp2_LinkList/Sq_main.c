#include "myheader.h"
#include "sqlist.h"

int main(int argc, char const *argv[])
{
	Status s;
	Sqlist La, Lb, Lc;
	int a[] = {1,2,4,8,10};
	int b[] = {2,4,5,7,9};
	s = InitList_Sq(&La);
	if(s==1){
		La.elem = a;
		La.length = 5;
	}
	s = InitList_Sq(&Lb);
	if(s==1){
		Lb.elem = b;
		Lb.length = 5;
	}
	s = ListInsert_Sq(&La, 3, 3);
	if (s==1)
		MergeList_Sq(La, Lb, &Lc);
	for (int i = 0; i < Lc.length; ++i)
	{
		printf("%3d", Lc.elem[i]);
	}
	return 0;
}
// gcc sqlist.c main.c -o sq_main