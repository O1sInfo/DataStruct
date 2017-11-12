// 稀疏矩阵的三元组行逻辑连接存储表示
// 为了方便随机存取任一行的非零元，则需要知道每一行的第一个非零元在三元组表中的位置
#include "myheader.h"
#define MAXSIZE 10000	// 假设非零元素个数的最大值为10000
#define MAXRC 100		// 行元素的个数的最大值
typedef struct 
{
	int i, j;		// 该非零元的行下标和列下标
	ElemType e;
}Triple;

typedef struct 
{
	Triple data[MAXSIZE+1];	// 非零元三元组表，data[0]未用
	int rpos[MAXRC+1];		// 各行第一个非零元的位置表
	int rn, cn, en;			// 矩阵的行数，列数，非零元个数
}RLSMatrix;

Status MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q){
	// 求矩阵乘积Q = M * N 采用行逻辑连接存储表示
	// 算法时间复杂度为O(M.rn*N.cn + M.en*N.en/N.rn)
	if(M.cn != N.rn)
		return ERROR;
	int an, bn, arow, brow, ccol, ctemp[MAXRC+1];
	(*Q).rn = M.rn;
	(*Q).cn = N.cn;
	(*Q).en = 0;
	if(M.en * N.en != 0){// Q是非零矩阵
		for(arow = 1; arow <= M.rn; arow++){
			for(ccol = 1; ccol <= (*Q).cn; ++ccol)
				ctemp[ccol] = 0;	// Q的当前行的各列元素累加器清零
			(*Q).rpos[arow] = (*Q).en + 1;	// Q的arow行的第一个元位于上一行最后一个元之后
			if(arow < M.rn)
				an = M.rpos[arow + 1] - 1;	// 当前arow最后一个元在data中的位置
			else
				an = M.en;					// 最后一行的最后一个元位置是M.en
			for(int a = M.rpos[arow]; a <= an; ++a){	// 对当前行中的每一个非零元
				brow = M.data[a].j;	// 找到对应元在N中的行号
				if(brow < N.rn)
					bn = N.rpos[brow + 1] - 1;
				else
					bn = N.en;
				for(int b = N.rpos[brow]; b <= bn; ++b){
					ccol = N.data[b].j;	//	乘积元素在N中的列号
					ctemp[ccol] += M.data[a].e * N.data[b].e;
				}
			}
			for(ccol = 1, ccol <= (*Q).cn; ccol++)	// 压缩存储该行的非零元
				if(ctemp[ccol]){
					if(++(*Q).en > MAXSIZE)
						return ERROR;
					(*Q).data[(*Q).en].i = arow;
					(*Q).data[(*Q).en].j = ccol;
					(*Q).data[(*Q).en].e = ctemp[ccol];
				}
		}
	}
	return OK;
}

