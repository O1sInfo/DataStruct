#include "myheader.h"

typedef struct MPNode
{
	ElemTag tag;
	int exp;		// 指数域
	union {
		float coef;	// 系数域
		struct MPNode *hp;	// 表结点的表头指针
	}u;
	struct MPNode *np;	// 相当于线性表的next, 指向下一个元素结点
}*MPList;				// m元多项式广义表的类型
