// 广义表的头尾链表存储表示
#include "../myheader.h"

typedef enum {ATOM, LIST}ElemTag;	// ATOM=0:原子; LIST=1:子表
typedef struct GLNode
{
	ElemTag tag;					// 标志域区分元素类型
	union {							// 原子结点和表结点的联合部分
		AtomType atom;				// atom是原子结点的值域, AtomType由用户定义
		struct {
			struct GLNode *hp, *tp; 
		}ptr;						// ptr是表结点的指针域, ptr.hp, ptr.tp分别指向表头和表尾
	}u;
}*GList;							// 广义表类型