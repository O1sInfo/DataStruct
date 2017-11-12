// 数组的顺序存储表示
#include "../myheader.h"
#include <stdarg.h>			// 提供宏va_start, va_arg, va_end用于存取变长参数表
#define MAX_ARRAY_DIM 8	// 数组维数最大值

typedef struct
{
	ElemType *base;	// 数组元素基址
	int dim;		// 数组维数
	int *bounds;	// 数组维界基址
	int *constants;	// 数组映像函数常数基址
}Array;

Status InitArray(Array *A, int dim, ...){
	// 若维数和各维的长度合法，则构造相应的数组
	int elemtotal = 1;
	if(dim<1 || dim>MAX_ARRAY_DIM)
		return ERROR;
	A.dim = dim;
	A.bounds = (int*)malloc(dim*sizeof(int));
	if(!A.bounds)
		exit(OVERFLOW);
	// 若各维的长度合法，则存入A.bounds, 并求出A的元素总数elemtotal
	va_list ap;			// ap为va_list类型，是存放变长参数表信息的数组
	va_start(ap, dim);	// 指出参数列表中可变长部分开始的位置(dim)，
						// 带有可变数量参数的函数必须至少有一个'正常的'形式参数
	for(i = 0; i < dim; ++i){
		A.bounds[i] = va_arg(ap, int);	// 获取ap中的第一个参数，然后自动前进到下一个参数处
		if(A.bounds[i]<0)
			return UNDERFLOW;
		elemtotal *= A.bounds[i];
	}
	va_end(ap);
	A.base = (ElemType*)malloc(elemtotal*sizeof(ElemType));
	if(!A.base)
		exit(OVERFLOW);
	// 求映像函数的常数Ci, 并存入A.constants[i-1], i=1,...,dim
	A.constants[dim-1] = 1;	// L = 1指针的增减以元素的大小为单位, (第dim维的映像常数为1)
	for(i = dim-2; i>=0; --i)
		A.constants[i] = A.bounds[i+1] * A.constants[i+1];	// C(i-1) = B(i) * C(i)
	return OK;
}

Status DestoryArray(Array *A){
	// 销毁数组A
	if(!A.base || !!A.bounds || !A.constants)
		return ERROR;
	free(A.base);
	A.base = NULL;
	free(A.bounds);
	A.bounds = NULL;
	free(A.constants);
	A.constants = NULL;
	return OK;
}

Status Locate(Array A, va_list ap, int *offset){
	// 若ap指示的下标值合法，则求出该元素在A中的相对地址offset
	*offset = 0;
	for(int i = 0, i < dim; ++i){
		ind = va_arg(ap, int);
		if(ind<0 || ind>=A.bounds[i])
			return OVERFLOW;
		*offset += A.constants[i]*ind;
	}
	return OK;
}

Status Value(Array A, ElemType *e, ...){
	// 若下标值合法，则用e返回A中的下标所指的元素
	va_list ap;
	int offset;
	va_start(ap, e);
	if(Locate(A, ap, &offset)<=0)
		return ERROR;
	*e = *(A.base + offset);
	return OK;
}

Status Assign(Array *A, ElemType e, ...){
	// 若下标值合法，将e赋值给A中下标所指的元素
	va_list ap;
	int offset;
	va_start(ap, e);
	if(Locate(A, ap, &offset)<=0)
		return ERROR;
	*(A.base + offset) = e;
	return OK;
}
