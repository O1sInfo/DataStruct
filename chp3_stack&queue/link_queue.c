#include "myheader.h"
#include "link_queue.h"

Status InitQueue(LinkQueue *Q){
	//
	(*Q).front = (*Q).rear = (QNode*)malloc(sizeof(QNode));
	if(!(*Q).front) exit(OVERFLOW);
	(*Q).front->next = NULL;
	return Ok;
}

Status DestoryQueue(LinkQueue *Q){
	//
	while((*Q).front){	// 从队头依次释放结点
		(*Q).rear = (*Q).front->next;
		free((*Q).front);
		(*Q).front = (*Q).rear;
	}
	return OK;
}

Status EnQueue(LinkQueue *Q, QElemType e){
	// 插入元素e为Q的新的队尾元素
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = NULL;		// ?
	(*Q).rear = p;
	return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e){
	//	若队列不空，则删除Q的队头元素，用e返回其值
	if((*Q).front == (*Q).rear)
		return ERROR;
	p = (*Q).front->next;	// p指向第一个结点
	e = p->data;
	(*Q).front->next = p->next;
	if((*Q).rear == p)		// 防止删除队尾指针
		(*Q).rear = (*Q).rear;
	free(p);
	return OK;
}

