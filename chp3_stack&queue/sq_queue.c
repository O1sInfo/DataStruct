#include "myheader.h"
#include "sq_queue.h"

Status InitQueue(SqQueue *Q){
	// 初始化循环(顺序存储)队列
	(*Q).base = (QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
	if(!(*Q).base)
		exit(OVERFLOW);
	(*Q).front = (*Q).rear = 0;	// 不一定要=0 只需在MAXQSIZE之内
	return OK;
}

int QueueLength(SqQueue Q){
	//
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue *Q, QElemType e){
	//
	if(((*Q).rear+1) % MAXQSIZE == (*Q).front)
		return ERROR;	// 队列满
	(*Q).base[(*Q).rear] = e;
	(*Q).rear++;		// 尾指针后移一位
	(*Q).rear %= MAXQSIZE;	// 循环队列
	return OK;
}

Status DeQueue(SqQueue *Q, QElemType *e){
	//
	if((*Q).front == (*Q).rear)
		return ERROR;	// 空队列
	*e = (*Q).base[(*Q).front];	// 队头元素赋值给e
	(*Q).front = ((*Q).front+1)%MAXQSIZE;	// 循环后移到下一位置
	return OK;
}