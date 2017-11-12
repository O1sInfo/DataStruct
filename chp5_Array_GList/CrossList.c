// 稀疏矩阵的十字链表存储表示
// 当矩阵的非零元个数和位置在操作过程中变化较大时，宜采用链式存储结构表示三元组的线性表
typedef struct OLNode 
{
	int i, j;		// 该非零元的行和列下标
	ElemType e;
	struct OLNode *right, *down;	// 该元素所在行表和列表的后继链域
}OLNode, *OLink;

typedef struct 
{
	OLink *rhead, *chead;	// 行和列链表头指针向量
	int rn, cn, en;			// 稀疏矩阵的行数、列数、非零元素个数
}CrossList;


Status InitSMatrix(CrossList *M){
	// 初始化(CrossList类型的变量必须初始化, 否则创建，复制矩阵将出错)
	(*M).rhead = (*M).chead = NULL;
	(*M).rn = (*M).cn = (*M).en = 0;
	return OK;
}

Status CreatSMatrix_OL(CrossList *M){
	// 创建稀疏矩阵，采用十字链表存储表示
	// 时间复杂度为O(e*s) s = max{r,c}
	int rn, cn, en, r, c;
	ElemType e;
	OLink p, q;
	printf("输入稀疏矩阵的行数、列数和非零元个数\n");
	scanf("%d%d%d", &rn, &cn, &en);
	(*M).rn = rn;
	(*M).cn = cn;
	(*M).en = en;
	if(!((*M).rhead = (OLink)malloc(rn+1)*sizeof(OLNode)))
		exit(OVERFLOW);
	if(!((*M).chead = (OLink)malloc(cn+1)*sizeof(OLNode)))
		exit(OVERFLOW);
	for(int i = 1; i <= rn; i++)
		(*M).rhead[i] = NULL;		// 初始化各行头指针
	for(int i = 1; i <= cn; i++)
		(*M).chead[i] = NULL;		// 初始化各列头指针
	printf("请按任意顺序输入%d个非零元的行 列 元素值\n", (*M).en);
	for(int i = 0; i <= en; i++){
		scanf("%d%d%d", &r, &c, &e);
		p = (OLink)malloc(sizeof(OLNode));
		if(!p)
			exit(OVERFLOW);
		p->i = r;
		p->j = c;
		p->e = e;
		if((*M).rhead[r] == NULL || (*M).rhead[r]->j > c){// p插在该行的第一个结点处
			p->right = (*M).rhead[r];
			(*M).rhead[r] = p;
		}
		else{// 查询在行表中的插入位置
			for(q = (*M).rhead[r]; q->right && q->right->j < c; q = q->right);
			p->right = q->right;	// 完成行表的插入
			q->right = p;
		}
		if((*M).chead[c] == NULL || (*M).chead[c]->i > r){// p插在该列的第一个结点处
			p->down = (*M).chead[c];
			(*M).chead[c] = p;
		}
		else{// 查询在列表中的插入位置
			for(q = (*M).chead[c]; q->down && q->down->r < r; q = q->down);
			p->down = q->down;	// 完成列表的插入
			q->down = p;
		}
	}
	return OK;
}