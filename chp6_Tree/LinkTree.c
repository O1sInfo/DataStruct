#include "./myheader.h"
#include "LinkTree.h"

Status InitBiTree(BiTree *T){
	// 构造空二叉树
	*T = NULL;
	return OK;
}

void DestoryBiTree(BiTree *T){
	// 递归销毁二叉树
	if (*T){
		if ((*T)->lchild)
			// 销毁左子树
			DestoryBiTree(&(*T)->lchild);
		if ((*T)->rchild)
			// 销毁右子树
			DestoryBiTree(&(*T)->rchild);
		free(*T);	// 释放根结点
		*T = NULL;
	}
}

void CreateBiTree(BiTree *T){
	// 按先序次序构造二叉链表表示的二叉树
	TElemType e;
	#ifdef CHAR
	scanf("%c", &e);
	#endif
	#ifdef INT
	scanf("%d", &e);
	#endif
	if (e == NULL)
		*T = NULL;
	else{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!(*T))
			exit(OVERFLOW);
		(*T)->data = e;	// 生成根结点
		CreateBiTree(&(*T)->lchild);	// 构造左子树
		CreateBiTree(&(*T)->rchild);	// 构造右子树
	}
}

Status BiTreeEmpty(BiTree T){
	// 二叉树为空返回TRUE, 否则返回FALSE
	if (T)
		return FALSE;
	else
		return TRUE;
}

int BiTreeDepth(BiTree T){
	// 返回二叉树的深度
	// 递归求左右子树的深度，返回结果为最大值加1
	int i, j;
	if (!T)
		return 0;
	if (T->lchild)
		i = BiTreeDepth(T->lchild);
	else
		i = 0;
	if (T->rchild)
		j = BiTreeDepth(T->rchild);
	else
		j = 0;
	return i > j? i+1: j+1;
}

TElemType Root(BiTree T){
	// 返回已存在二叉树的根
	if (BiTreeEmpty(T))
		return NULL;
	else
		return T->datal;
}

TElemType Value(BiTree p){
	// 返回p所指结点的值
	return p->data;
}

void Assign(BiTree p, TElemType value){
	// 给p所指结点赋值value
	p->data = value;
}

