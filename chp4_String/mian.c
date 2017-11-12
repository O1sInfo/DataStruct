#include <string.h>
#include "../myheader.h"
#include "hstring.c"
#include "../chp2_LinkList/Link.c"
#define MaxBookNum 1000	// 假设只对1000本书建立索引表
#define MaxKeyNum 2500	// 索引表的最大容量
#define MaxLineLen 500	// 书目串的最大长度
#define MaxWordNum	10	// 关键词表的最大容量
#define MaxNoIdx	10  // 常用词(仅指大写)的最大数

typedef struct 
{
	char *item[MaxWordNum];
	int length;	
}WordListType;	// 词表类型(顺序表)

// typedef int ElemType;	// 定义链表的数据元素为整型(书号类型)

typedef struct 
{
	HString key;	// 关键字
	LinkList booknolist;	// 存放书号索引的链表
}IdxTermType;	// 索引项类型

typedef struct 
{
	IdxTermType item[MaxKeyNum+1];
	int length;		// 关键词个数
}IdxListType;	// 索引表类型(有序表)

// 主要变量
char buf[MaxLineLen+1];	// 书目串缓冲区
WordListType wdlist, noidxlist;	// 词表, 常用词表

// 基本操作
void InitIdxList(IdxListType *idxlist){
	// 初始化置索引表为空表，且在idxlist.item[0]设一空串
	(*idxlist).length = 0;
	StrInit(&(*idxlist).item[0].key);	// 初始化(产生空串)
	InitList(&(*idxlist).item[0].booknolist); // 构造一个空的线性链表
}

void GetLine(FILE *f){
	// 从文件f读入一个书目信息到书目串缓冲区
	int i = 0;
	while(buf[i])						// ------------------------------------关键点：清楚上一个书目缓冲区避免长度过长加给下一个书目名
		buf[i++] = '\0';				
	fgets(buf, MaxLineLen, f);
}

void ExtractKeyWord(ElemType *bookno){
	// 从buf提取书名关键词到词表wdlist, 书号存入bookno
	int i, len, f = 1;	//  f是字符串结束标志0：结束；1：未结束
	char *s1, *s2;
	if(buf[0]<'0' || buf[0] > '9')
		exit(OVERFLOW);	 // buf的首字母不是数字
	for(i = 0; i < wdlist.length; i++){	// 释放上一个书目在词表wdlist的存储空间
		free(wdlist.item[i]);
		wdlist.item[i] = NULL;
	}
	wdlist.length = 0;
	*bookno = (buf[0]-'0')*100 + (buf[1]-'0')*10 + (buf[2]-'0');	// 前三位为书号
	s2 = &buf[2];
	do{	// 提取书名关键字到词表wdlist 
		s1 = s2 + 1;	// s1向后移动一个单词
		s2 = strchr(s1, ' ');	//s2指向s1的第一个空格
		if(!s2){	// 到串尾
			s2 = strchr(s1, '\r');	// s2指向buf的最后一个字符(回车符)
			f = 0;
		}
		len = s2 - s1;	// 单词长度
		if(s1[0]>='A' && s1[0]<='Z'){	// 单词首字母大写
			// 写入词表
			wdlist.item[wdlist.length] = (char*)malloc((1+len)*sizeof(char));
			// 生成串空间，包括'\0'
			for(i = 0; i < len; i++)	
				wdlist.item[wdlist.length][i] = s1[i];	// 写入词表
			wdlist.item[wdlist.length][len] = '\0';
			for(i = 0; i < noidxlist.length; i++)	// 查找是否为常用词
				if(!strcmp(wdlist.item[wdlist.length], noidxlist.item[i]))
					break;
			if(i != noidxlist.length){	// 是常用词
				free(wdlist.item[wdlist.length]);	// 从词表删除该词
				wdlist.item[wdlist.length] = NULL;
			}
			else
				wdlist.length++;
		}
	}while(f);
}

// ------------------------InsIdxList()函数的子函数--------------------------
void GetWord(int i, HString *wd){
	// 用wd返回词表wdlist的第i个关键词
	StrAssign(wd, wdlist.item[i]);	// 生成关键字字符串
}

int Locate(IdxListType *idxlist, HString wd, int *b){
	// 在索引表idxlist中查询是否存在与wd相等的关键字。若存在返回其在索引表中的位置，且b取值为TRUE
	// 否则返回插入位置且b取FALSE	位置的取值范围为 [0, (*idxlist).length]
	int i = 0;
	for(; i < (*idxlist).length; ++i)
		if(StrCompare((*idxlist).item[i].key, wd)==0)
			break;
	if(i == (*idxlist).length){
		*b = FALSE;
		return (*idxlist).length;
	}
	else{
		*b = TRUE;
		return i;
	}
}

void InsertNewKey(IdxListType *idxlist, int i, HString wd){
	// 在索引表idxlist的第i项上插入新关键词wd, 并初始化书号索引的链表为空表
	InitList(&(*idxlist).item[(*idxlist).length + 1].booknolist);// 新增索引项的链表
	for(int j = (*idxlist).length; j>=i; --j)
		(*idxlist).item[j+1] = (*idxlist).item[j];	// 后移索引项
	// 插入新的索引项
	StrInit(&(*idxlist).item[i].key);	// 新增索引项的串
	StrCopy(&(*idxlist).item[i].key, wd);	// 串赋值
	InitList(&(*idxlist).item[i].booknolist);	// 初始化书号索引表为空表
	(*idxlist).length++;
}

void InsertBook(IdxListType *idxlist, int i, int bookno){
	// 在索引表idxlist的第i项上插入书号问哦bookno的索引
	Link p;
	if(!MakeNode(&p, bookno))
		exit(OVERFLOW);
	p->next = NULL;
	Append(&(*idxlist).item[i].booknolist, p);
}

// ----------------------------------------------------------------------
Status InsIdxList(IdxListType *idxlist, ElemType bookno){
	// 将书号为bookno的书名关键词按词典顺序插入索引表idxlist
	int i, j, b;
	HString wd;
	StrInit(&wd);
	for (int i = 0; i < wdlist.length; ++i){
		GetWord(i, &wd);
		j = Locate(idxlist, wd, &b);
		if(!b)
			InsertNewKey(idxlist, j, wd);	// 插入新的索引项
		InsertBook(idxlist, j, bookno);	// 插入书号索引
	}
	return OK;
}

void PutText(FILE *g, IdxListType idxlist){
	// 将生成的索引表idxlist输出到文件g
	int i, j;
	Link p;
	fprintf(g, "%d\n", idxlist.length);
	for(i = 0; i < idxlist.length; ++i){
		for(j = 0; j < idxlist.item[i].key.length; j++)
			fprintf(g, "%c", idxlist.item[i].key.ch[j]);
		fprintf(g, "\n%d\n", idxlist.item[i].booknolist.len);
		p = idxlist.item[i].booknolist.head;
		for(j = 0; j < idxlist.item[i].booknolist.len; j++){
			p = p->next;
			fprintf(g, " %d", p->data);
		}
		fprintf(g, "\n");
	}
}

int main(int argc, char const *argv[])
{
	FILE *f, *g;
	int bookno, len;
	IdxListType idxlist;
	if(f = fopen("NoIdx.txt", "r")){	// 打开常用词文件
		fscanf(f, "%d", &noidxlist.length);	// 常用词个数
		for(int k = 0; k<noidxlist.length; k++){	// 把常用词文件的内容拷到noidx中
			fscanf(f, "%s", buf);
			len = strlen(buf);
			noidxlist.item[k] = (char*)malloc(len*sizeof(char));
			strcpy(noidxlist.item[k], buf);
		}
		fclose(f);
	}
	if(f = fopen("BookInfo.txt", "r")){
		InitIdxList(&idxlist); // 初始化置索引表为空表
		wdlist.length = 0;	// 词表长度初始化
		while(!feof(f)){
			GetLine(f);		// 从文件f读入一个书目信息到书目串缓冲区
			if((len = strlen(buf))<=2)		// ---------------------------------------------关键点：在windows平台上文件的结束符为\r\n
				break;
			ExtractKeyWord(&bookno);	// 从buf提取关键词到词表，书号存入bookno
			InsIdxList(&idxlist, bookno);	// 将书号为bookno的关键词插入索引表
		}
		fclose(f);
	}
	if(g = fopen("BookIdx1.txt", "w")){
		PutText(g, idxlist);	// 将生成的索引表idxlist输出到文件g
		fclose(g);
	}
	return 0;
}