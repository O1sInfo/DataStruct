// 串的堆分配存储表示

typedef struct 
{
	char *ch;
	int length;
}HString;

void StrInit(HString *T);
// 初始化(产生空串)字符串T
Status StrAssign(HString *T, char *chars);
// 生成一个其值等于串常量chars的串T
int StrLength(HString S);
// 返回串S的长度
int StrCompare(HString S, HString T);
// 若S>T 则返回>0, 若S=T,则返回0, 若S<T, 则返回<0
Status StrClear(HString *S);
// 将S清为空串
Status StrConcat(HString *T, HString S1, HString S2);
// 用T返回由S1和S2连接而成的新串
Status StrSub(HString *Sub, HString S, int pos, int len);
// 用Sub返回串S的第pos个位置起长度为len的字串
// 1<=pos<=S.length && 0<=len<=S.length-pos+1
Status StrCopy(HString *T, HString S);
//	由串S复制得串T