#include "../myheader.h"

// 串的定长顺序表示
#define MAXSTRLEN 255	// 用户可以在25以内定义最大串长
typedef unsigned char SString[MAXSTRLEN+1];	// 0号单元存放串的长度


Status Concat(SString *T, SString S1, SString S2){
	// 串连接
	bool uncut;
	if(S1[0]+S2[0] <= MAXSTRLEN){
		// 未截断
		for (int i = 1; i <= S1[0]; ++i)
			(*T)[i] = S1[i];
		for (int i = 1; i <= S2[0]; ++i)
			(*T)[S1[0]+i] = S2[i];
		(*T)[0] = S1[0] + S2[0];
		uncut = TRUE;
	}
	else if(S1[0] < MAXSTRLEN){
		// 截断S2
		for (int i = 1; i <= S1[0]; ++i)
			(*T)[i] = S1[i];
		for (int i = 1; i <= MAXSTRLEN-S1[0]; ++i)
			(*T)[S1[0]+i] = S2[i];
		(*T)[0] = MAXSTRLEN;
		uncut = FALSE;
	}
	else{
		// 截断S1
		for (int i = 0; i <= MAXSTRLEN; ++i)
			(*T)[i] = S1[i];	// *T[0] = S1[0] = MAXSTRLEN
		uncut = FALSE;
	}
	return uncut;
}

Status SubString(SString *Sub, SString S, int pos, int len){
	// 用Sub返回串S的第pos个字符起长度为len的字串
	if(pos < 1 || pos > S[0] || len < 0 || len > s[0] - pos +1)
		return ERROR;
	for (int i = 1; i <= len; ++i)
		(*Sub)[i] = S[pos+i-1];
	(*Sub)[0] = len;
	return OK;
}

int Index(SString S, SString T, int pos){
	// 返回子串T在主串S中第pos个字符之后的字符，若不存在则函数值为0
	int i = pos, j = 1;
	while(i<=S[0] && j<=T[0]){
		if(S[i] == T[j]){
			// 继续比较后续字符
			++i;
			++j;
		}
		else{
			// 指针后退从新开始匹配
			i = i+j-2;	// i = i - (j-1) + 1 (j-1为i移动的位数)
			j = 1;
		}
	}
	if(j > T[0])	// 匹配完成
		return i - T[0];
	else	// 未匹配到
		return 0 
}

int Index_KMP(SString S, SString T, int pos){
	// 利用模式串T的next函数求T在主串S中第pos个字符之后的位置
	int i = pos, j = 1;
	while(i<=S[0] && j<=T[0]){
		if(j == 0 || S[i] == T[j]){
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if(j > T[0])
		return i - T[0];
	else return 0;
}

void get_next(SString T, int next[]){
	// 求模式串T的next函数值并存入next数组
	int i = 1, j = 0;
	next[1] = 0;
	while(i<T[0]){
		if(j == 0 || T[i] == T[j]){
			++i;
			++j;
			if(T[i] != T[j])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}
}