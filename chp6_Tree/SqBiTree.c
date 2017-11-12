#include <math.h>
#include "SqBiTree.h"
#include "./myheader.h"

Status InitBiTree(SqBiTree T){
	// 构造空二叉树
	int i;
	for (i = 0; i < MAX_TREE_SIZE; ++i)
		T[i] = NULL;
	return OK; 
}

void DestoryBiTree(){
	// 由于SqBiTree是定长类型，无法销毁
}

Status CreateBiTree(SqBiTree T){
	// 按层序次序输入结点的值，空格表示空结点
	int i = 0;
	int len;
	char s[MAX_TREE_SIZE];
	printf("Please enter the value (character) of the node in the sequence,\
	 and the space represents the empty node\n");
	gets(s);
	len = strlen(s);
	for (; i < len; i++){
		T[i] = s[i];
		if (i != 0 && T[(i+1)/2 - 1] == NULL && T[i] != NULL){
			// 此结点(不空)无双亲且不是根
			printf("Error Node%c\n", T[i]);
			exit(ERROR);
		}
	}
	for (; i < MAX_TREE_SIZE; i++)
		T[i] = NULL;			// 赋值空给剩余的T
}

Status BiTreeEmpty(SqBiTree T){
	// 判断已存在的顺序二叉树是否为空
	if (T[0] == NULL)
		return TRUE;
	else
		return FALSE;
}

int BiTreeDepth(SqBiTree T){
	// 返回顺序二叉树的深度
	int i, j = -1;
	for (i = MAX_TREE_SIZE; i >= 0; i--)
		// 找到最后一个结点
		if (T[i] != NULL)
			break;
	i++;	// 0号单元存储根结点
	do
		j++;
	while(i >= pow(2, j));		// 完全二叉树有 2^(k-1) <= n < 2^k
	return j;
}

Status Root(SqBiTree T, TElemType *e){
	// 当T不为空，用e返回T的根，返回OK;否则返回ERROR, e无定义
	if (BiTreeEmpty(T))
		return ERROR;
	else{
		*e = T[0];
		return OK;
	}
}

TElemType Value(SqBiTree T, position e){
	// 返回处于位置e的结点的值
	return T[(int)pow(2, e.level-1) + e.order - 2];
}

Status Assign(SqBiTree T, position e, TElemType value){
	// 给处于位置e的结点赋值value
	int i = (int)pow(2, e.level-1) + e.order - 2;	// 找到e在数组中的下标
	if (value != NULL && T[(i+1)/2 - 1] == NULL)
		// 给双亲为空的叶子赋非空值
		return ERROR;
	else if (value == NULL && T[i*2 + 1] != NULL || T[i*2 + 2] != NULL)
		// 给双亲赋空值但有叶子
		return ERROR;
	T[i] = value;
	return OK;
}

TElemType LeftChild(SqBiTree T, TElemType e){
	// 返回e的左孩子，若e无左孩子返回空
	int i;
	if (T[0] == NULL)
		return NULL;
	for (i = 0; i <= MAX_TREE_SIZE; ++i)
		if (T[i] == e)	// 找到e
			return T[i*2 + 1];
	return NULL;
}

TElemType RightChild(SqBiTree T, TElemType e){
	// 返回e的右孩子
	int i;
	if (T[0] == NULL)
		return NULL;
	for (i = 0; i <= MAX_TREE_SIZE; ++i)
		if (T[i] == e)	// 找到e
			return T[i*2 + 2];
	return NULL;
}

TElemType LeftSibling(SqBiTree T, TElemType e){
	// 返回e的左兄弟
	int i;
	if (T[0] == NULL)
		return NULL;
	for (i = 0; i <= MAX_TREE_SIZE; ++i)
		if (T[i] == e && i%2 == 0)	// 找到e且其序号为偶数(是右孩子)
			return T[i - 1];
	return NULL;
}

TElemType RightSibling(SqBiTree T, TElemType e){
	// 返回e的右兄弟
	int i;
	if (T[0] == NULL)
		return NULL;
	for (i = 0; i <= MAX_TREE_SIZE; ++i)
		if (T[i] == e && i%2)	// 找到e且其序号为奇数(为左孩子)
			return T[i + 1];
	return NULL;
}

void Move(SqBiTree q, int j, SqBiTree T, int i){
	// 把从q的j结点开始的子树移为从T的i结点开始的子树
	if (q[j*2 + 1] != NULL)	// q的左子树不为空
		Move(q, (j*2 + 1), T, (i*2 + 1));	// 把q的j结点的左子树移到T的i结点的左子树
	if (q[j*2 + 2] != NULL)	// q的右子树不为空
		Move(q, (j*2 + 2), T, (i*2 + 2));
	T[i] = q[j];			// 把q的j结点的右子树移为T的i结点
	q[j] = NULL;			// q的j结点置空
}

Status InsertChild(SqBiTree T, TElemType p, Status LR, SqBiTree c){
	// p为非空二叉树T中某个结点的值，LR为0或1 非空二叉树c与T不相交且右子树为空
	// 根据LR为0或1，插入c为T中p结点的左或右子树，p结点的原有左或右子树
	// 则成为c的右子树
	int j, k, i = 0;
	for (j = 0; j < (int)pow(2, BiTreeDepth(T)) - 1; j++)
		// 查找p的序号
		if (T[j] == p)
			break;
	k = 2*j + 1 + LR;	// k为p的左或右孩子的序号
	if (T[k] != NULL)
/*?*/		Move(T, k, T, k*2+2);	// 把从T的k结点开始的子树移为从k结点的右子树开始的子树
	Move(c, i, T, K);	// 把从c的i结点开始的子树移为从T的k结点开始的子树
	return OK;
}