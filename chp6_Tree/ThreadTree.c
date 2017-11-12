#include ".\myheader.h"
#include "ThreadTree.h"

Status CreatBiThrTree(BiThrTree *T){
	// 按先序输入二叉线索树中的结点的值，构造二叉线索树T
	// 0(整型)/空格(字符型)表示空结点
	TElemType h;
	#if CHAR
		scanf("%c", &h);
	#else
		scanf("%d", &h);
	#endif
	if (h == NULL)
		*T = NULL;
	else{
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if(!(*T))
			exit(OVERFLOW);
		(*T)->data = h;
		CreatBiThrTree(&(*T)->lchild);		// 递归创建左子树
		if ((*T)->lchild)	// 有左孩子
			(*T)->LTag = Link;
		CreatBiThrTree(&(*T)->rchild);		// 递归创建右子树
		if ((*T)->rchild)	// 有右孩子
			(*T)->RTag = Link;
	}
	return OK;
}

BiThrTree pre;	// 全局变量， 始终指向刚刚访问过的结点
void InThreading(BiThrTree p){
	// 中序遍历进行中序线索化
	if (p){
		InThreading(p->lchild);	// 递归左子树线索化
		if(!p->lchild){			// 没有左孩子
			p->LTag = Thread;	// 前驱线索化
			p->lchild = pre;	// 左孩子指针指向前驱
		}
		if(!pre->rchild){		// 前驱没有右孩子
			pre->RTag = Thread;	// 后继线索
			pre->rchild = p;	// 前驱右孩子指针指向后继(当前结点p)
		}
		pre = p;				// 保持pre指向p的前驱
		InThreading(p->rchild);	// 递归右子树线索化
	}
}

Status InOrderThreading(BiThrTree *Thrt, BiThrTree T){
	// 中序遍历二叉树T, 并将其中序线索化， Thrt指向头结点
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!*Thrt)
		exit(OVERFLOW);
	(*Thrt)->LTag = Link;		// 建立表头结点
	(*Thrt)->RTag = Thread;
	(*Thrt)->rchild = *Thrt;	// 右指针回指
	if (!T)
		(*Thrt)->lchild = *Thrt;	// 若二叉树为空，左指针也回指
	else{
		(*Thrt)->lchild = T;
		pre = *Thrt;
		InThreading(T);			// 中序遍历进行中序线索化
		pre->rchild = *Thrt;
		pre->RTag = Thread;		// 最后一个结点线索化
		(*Thrt)->rchild = pre;
	}
	return OK;
}

Status InOrderTraverse_Thr(BiThrTree T, Status (*Visit)(TElemType)){
	// 中序遍历二叉线索树T(头结点)的非递归算法
	BiThrTree p;
	p = T->lchild;				// p指向根结点
	while (p != T ){	// 空树或遍历结束时p == T
		while (p->LTag == Link)
			p = p->lchild;
		if (!Visit(p->data))
			return ERROR;	// 访问其左子树为空的结点
		while(p->RTag == Thread && p->rchild != T){
			p = p->rchild;
			Visit(p->data);		// 访问后继结点
		}
		p = p->rchild;
	}
	return OK;
}