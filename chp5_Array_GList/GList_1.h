// 广义表的扩展线性链表存储表示
#include "../myheader.h"

typedef enum {ATOM, LIST}ElemTag;	// ATOM=0:原子; LIST=1:子表
typedef struct GLNode
{
	ElemTag tag;					// 标志域区分元素类型
	union {							// 原子结点和表结点的联合部分
		AtomType atom;				// atom是原子结点的值域, AtomType由用户定义
		struct GLNode *hp; 			// 表结点的表头指针
	}u;	// -----------联合体变量名
	struct GLNode *np;				// 相当于线性链表的next, 指向下一个元素
}*GList;							// 广义表类型