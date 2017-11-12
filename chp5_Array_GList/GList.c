#include "GList.h"
#include "../chp4_String/sstring.c"
int GListDepth(GList L){
	// 采用头尾链式存储结构，求广义表的深度
	int max = 0;
	if(!L)
		return 1;	// 空表深度为1
	if(L->tag == ATOM)
		return 0;	// 原子深度为0
	for(GList pp = L; pp; pp = pp->u.ptr.np){
		int dep = GListDepth(pp->u.ptr.hp);	// 求字表深度
		if(dep > max)
			max = dep;
	}
	return max + 1;
}

Status CopyList(GList *T, GList L){
	// 采用头尾链式存储结构，由广义表L复制得到广义表T
	if(!L){
		(*T)->tag = LIST;	// 复制空表
		(*T)->u.ptr.hp = NULL;
		(*T)->u.ptr.np = NULL;
	}
	else{
		if(!((*T) = (GList)malloc(sizeof(GLNode))))	// 建立表结点
			exit(OVERFLOW);
		(*T)->tag = L->tag;
		if(L->tag == ATOM)
			(*T)->atom = L->atom;	// 复制单原子结点
		else{
			CopyList((*T)->u.ptr.hp, L->u.ptr.hp);
			CopyList((*T)->u.ptr.np, L->u.ptr.np);
		}
	}
	return OK;
}


Status CreateGList(GList *L, SString S){
	// 采用头尾链表存储结构，由广义表的书写形式串S创建广义表L,设emp="()"
	SString emp, sub, hsub;
	GList p, q;
	StrAssign(&emp, "()");	// 设emp="()"
	if(!((*L) = (GList)malloc(sizeof(GLNode))))
		exit(OVERFLOW);
	if(StrCompare(S, emp)){
		(*L)->tag = LIST;	// 创建空表
		(*L)->u.ptr.hp = NULL;
		(*L)->u.ptr.np = NULL;
	}
	else{
		if(!((*L) = (GList)malloc(sizeof(GLNode))))
			exit(OVERFLOW);
		else{
			(*L)->tag = LIST;
			p = L;
			SubString(sub, S, 2, StrLength(S)-2);
		}
	}
}