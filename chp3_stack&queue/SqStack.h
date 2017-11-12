// 栈的顺序存储结构
// #include "maze.h"		// maze.c
#define STACK_INIT_SIZE 100	// 存储空间初始分配量
#define STACKINCREMENT 10		// 存储空间分配增量
// typedef ElemType SElemType;	// conversion.c
typedef char SElemType;	// EvaluateExpression.c

typedef struct 
{
	SElemType *base;	// 栈底指针
	SElemType *top;		// 栈顶指针
	int stacksize;		// 指示栈的当前可使用的最大容量
}SqStack;				// 顺序栈

// base为NULL，则表明栈结构不存在；top=base可作为栈空的标记

Status InitStack(SqStack *S);
Status GetTop(SqStack S, SElemType *e);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
Status StackEmpty(SqStack S);