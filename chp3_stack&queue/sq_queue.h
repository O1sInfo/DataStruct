// 循环队列--队列的顺序存储结构
#define MAXQSIZE 100	// 最大队列元素
typedef struct 
{
	QElemType *base;	// 初始化的动态存储空间
	int front;			// 头指针。若队列不为空，指向队列头元素
	int rear;			// 尾指针，若队列不为空，指向队列尾元素的下一个位置
}SqQueue;
