#include "myheader.h"
#include "SqStack.h"

void conversion();

int main(int argc, char const *argv[])
{
	conversion();
	return 0;
}

void conversion(){
	// 对于输入的任意一个非负十进制整数，打印输出与其等值的八进制数
	Status st;
	SqStack S;
	int N, e;
	st = InitStack(&S);
	scanf("%d", &N);
	while(N){
		st = Push(&S, N%8);
		N = N/8;
	}
	while(!StackEmpty(S)){
		st = Pop(&S, &e);
		printf("%d", e);
	}
	printf("\n");
}

/*
void mactch(){
	SqStack S;
	InitStack(&S);
}
*/

void LineEdit(){
	// 行编辑程序
	SqStack S;
	InitStack(&S);
	ch = getchar();
	while(ch != EOF){	// EOF为全文结束符
		while(ch != '\n'){
			switch(ch){
				case '#': Pop(&S, c);	break;	// 仅当栈非空时
				case '@': ClearStack(&S);	break;	// 重置S为空栈
				default: Push(&S, ch);	break;	// 有效字符进栈，未考虑栈满情况
			}
			// 将从栈底到栈顶的栈内字符传送至调用过程的数据区
			if(ch != EOF) ch = getchar();
	}
	DestroyStack(&S);
}

