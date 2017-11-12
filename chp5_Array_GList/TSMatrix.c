// 稀疏矩阵的三元组顺序存储表示
// 三元组顺序表的特点是：非零元在表中按行序有序存储，便于进行依行顺序处理的矩阵运算
#include "myheader.h"
#define MAXSIZE 10000	// 假设非零元素个数的最大值为10000
typedef struct 
{
	int i, j;		// 该非零元的行下标和列下标
	ElemType e;
}Triple;

typedef struct 
{
	Triple data[MAXSIZE+1];	// 非零元三元组表，data[0]未用
	int rn, cn, en;			// 矩阵的行数，列数，非零元个数
}TSMatrix;


Status TransposeSMatrix(TSMatrix M, TSMatrix *T){
	// 采用三元组表存储表示，，求稀疏矩阵M的转置矩阵T
	// 思想：按照T.data中三元组的顺序依次在M.data中找到相应的三元组进行转置
	(*T).rn = M.cn;
	(*T).cn = M.rn;
	(*T).en = M.en;
	if((*T).en){
		int q = 1;
		for(int col = 1; col <= M.cn; ++col)	// 时间复杂度为O(cn*en), 故适用于cn*rn >> en
			for(int p = 1; p <= M.en; ++p)
				if(M.data[p].j == col){
					(*T).data[q].i = M.data[p].j;
					(*T).data[q].j = M.data[p].i;
					(*T).data[q].e = M.data[p].e;
					++q;
				}
	}
	return OK;
}

Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T){
	// 快速转置：按照M.data中的三元组的次序进行转置
	// 预先求出M中每一列的第一个非零元在T.data中的位置, num[col]:col列非零元个数，cpot[col]:位置
	// cpot[1] = 1; cpot[col] = cpot[col-1] + num[col-1]
	(*T).rn = M.cn;
	(*T).cn = M.rn;
	(*T).en = M.en;
	if((*T).en){
		for(int col = 1; col <= M.cn; ++col)
			num[col] = 0;
		for(int p = 1; p <= M.en; ++p)
			++num[M.data[p].j];		// 求num[col]
		cpot[1] = 1;
		for(int col = 2; col <= M.cn; ++col)
			cpot[col] = cpot[col-1] + num[col-1];	// 求cpot[col]
		for(int p = 1, q; p <= M.en; ++p){
			q = cpot[M.data[p].j];
			(*T).data[q].i = M.data[p].j;
			(*T).data[q].j = M.data[p].i;
			(*T).data[q].e = M.data[p].e;
			++cpot[col];
		}
	}
	return OK;
}