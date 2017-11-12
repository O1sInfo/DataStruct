#include "../myheader.h"
#include "hstring.h"

void StrInit(HString *T){
	// 初始化(产生空串)字符串T
	(*T).length = 0;
	(*T).ch = NULL;
}

Status StrAssign(HString *T, char *chars){
	// 生成一个其值等于串常量chars的串T
	int i;
	char *c;
	if((*T).ch)
		free((*T).ch);
	for(i = 0, c = chars; *c; ++i, ++c);	// 求串chars的长度 i = len(chars)
	if(!i){
		(*T).ch = NULL;
		(*T).length = 0;
	}
	else{
		if(!((*T).ch = (char*)malloc((i+1)*sizeof(char))))
			exit(OVERFLOW);
		for (int j = 0; j <= i; ++j)	// 值复制; 注意最后的'\0'也要复制
			(*T).ch[j] = chars[j];
		(*T).length = i;
	}
	return OK;
}

int StrLength(HString S){
	// 返回串S的长度
	return S.length;
}

int StrCompare(HString S, HString T){
	// 若S>T 则返回>0, 若S=T,则返回0, 若S<T, 则返回<0
	for (int i = 0; i < S.length && i < T.length; ++i){
		if(S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}

Status StrClear(HString *S){
	// 将S清为空串
	if((*S).ch){
		free((*S).ch);
		(*S).ch = NULL;
	}
	(*S).length = 0;
	return OK;
}

Status StrConcat(HString *T, HString S1, HString S2){
	// 用T返回由S1和S2连接而成的新串
	if((*T).ch)
		free((*T).ch);	// 释放旧空间
	if(!((*T).ch = (char*)malloc((S1.length+S2.length)*sizeof(char))))
		exit(OVERFLOW);
	for (int j = 0; j < S1.length; ++j)	// 值复制S1
			(*T).ch[j] = S1.ch[j];
	(*T).length = S1.length + S2.length;
	for (int i = S1.length; i < (*T).length; ++i)
		(*T).ch[i] = S2.ch[i-S1.length];		// 复制S2
	return OK;
}

Status StrSub(HString *Sub, HString S, int pos, int len){
	// 用Sub返回串S的第pos个位置起长度为len的字串
	// 1<=pos<=S.length && 0<=len<=S.length-pos+1
	if (pos<1 || pos>S.length || len<0 || len>S.length-pos+1)
		return ERROR;
	if((*Sub).ch)
		free((*Sub).ch);
	if(!len){	// 空字串
		(*Sub).ch = NULL;
		(*Sub).length = 0;
	}
	else{
		(*Sub).ch = (char*)malloc(len*sizeof(char));
		for (int i = 0; i < len; ++i)
			(*Sub).ch[i] = S.ch[pos-1+i];
		(*Sub).length = len;
	}
	return OK;
}

Status StrCopy(HString *T, HString S){
	//	由串S复制得串T
	int i;
	if((*T).ch)
		free((*T).ch);	// 释放原有空间
	(*T).ch = (char*)malloc(S.length*sizeof(char));	// 分配空间
	if(!(*T).ch)
		exit(OVERFLOW);
	for(i = 0; i < S.length; i++)	// 拷贝串
		(*T).ch[i] = S.ch[i];
	(*T).length = S.length;
	return OK;
}