#include "myheader.h"
#include "SqStack.h"

Status InitStack(SqStack *S){
	//
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!(*S).base) exit(OVERFLOW);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status GetTop(SqStack S, SElemType *e){
	//
	if(S.top == S.base) return ERROR;
	*e = *(S.top - 1);
	return OK;
}

Status Push(SqStack *S, SElemType e){
	//
	if ((*S).top - (*S).base >= (*S).stacksize){	// 栈满
		(*S).base = (SElemType*)realloc((*S).base, ((*S).stacksize + STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base) exit(OVERFLOW);	// 分配存储空间失败
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top) = e;
	(*S).top++;
	return OK;
}

Status Pop(SqStack *S, SElemType *e){
	// 若栈不空，则删除S的栈顶元素，用e返回其值
	if((*S).top == (*S).base) return ERROR;
	*e = *(--(*S).top);
	return OK;
}

Status StackEmpty(SqStack S){
	//
	if(S.top == S.base) return TRUE;
	else return FALSE;
}

