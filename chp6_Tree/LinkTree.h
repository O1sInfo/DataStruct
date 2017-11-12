// 二叉树的链式存储
typedef struct BiTNode
{
	TElemType	data;
	struct BiTNode *lchild, *rchild;	// 左右孩子指针
}BiTNode, *BiTree;
