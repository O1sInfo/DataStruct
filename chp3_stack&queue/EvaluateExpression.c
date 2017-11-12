// 表达式求值
#include "myheader.h"
#include "SqStack.h"
#define MAXSIZE 20

SElemType Precede(SElemType t1, SElemType t2){
	// 根据教科书表3.1 判断两符号的优先关系
	SElemType f;
	switch(t2){
		case '+':
		case '-':	if(t1=='(' || t1=='#')	f = '<';
					else f = '>';
					break;
		case '*':
		case '/':	if(t1=='*' || t1=='/' || t1==')')	f = '>';
					else f = '<';
					break;
		case '(':	if(t1==')'){
						printf("括号不匹配%s\n", t1);
						exit(ERROR);
					}
					else f = '<';
					break;
		case ')':	switch(t1){
						case '(': f = '=';	break;
						case '#': printf("括号不匹配%s\n", t1);
								exit(ERROR);
								break;
						default: f = '>';
					}
					break;
		case '#':	switch(t1){
						case '#': f = '=';
						case '(': printf("括号不匹配%s\n", t1);
						default: f = '>';
					}
	}
	return f;
}

Status IsOperator(SElemType c){
	// 判断c是否为运算符
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '#': return TRUE;
		default: return FALSE;
	}
}

SElemType Operate(SElemType a, SElemType theta, SElemType b){
	//
	SElemType c;
	a = a-48;	// char -> int
	b = b-48;
	switch(theta){
		case '+': c = a+b+48;	break;
		case '-': c = a-b+48;	break;
		case '*': c = a*b+48;	break;
		case '/': c = a/b+48;	break;
	}
	return c;
}

SElemType EvaluateExpression(char op[]){	// op[]为算术表达式
	// 算术表达式求值的算符优先算符。设Operator和Operand分别为运算符栈和运算数栈
	int i=0;
	SqStack Operator, Operand;
	SElemType a,b,c,x,theta;
	InitStack(&Operator);
	Push(&Operator, '#');
	InitStack(&Operand);
	c = op[i];
	GetTop(Operator, &x);
	while(c!='#' || x!='#'){
		if(IsOperator(c)){	// c是运算符
			switch(Precede(x, c)){	// x->t1, c->t2
				case '<':	Push(&Operator, c);
							c = op[++i];
							break;
				case '=': 	Pop(&Operator, &x);
							c = op[++i];
							break;
				case '>': 	Pop(&Operator, &theta);
							Pop(&Operand, &b);
							Pop(&Operand, &a);
							Push(&Operand, Operate(a, theta, b));
							break;
			}
		}
		else if(c>='0' && c<='9'){	// c是操作数
			Push(&Operand, c);
			c = op[++i];
		}
		else{	// c是非法字符
			printf("非法字符%s\n", c);
			exit(ERROR);	
		}
		GetTop(Operator, &x);
	}
	GetTop(Operand, &x);
	return x;
}

int main(int argc, char const *argv[])
{
	char op[MAXSIZE];
	char ch;
	int i=0;
	printf("请输入算术表达式（中间值及最终结果要在0～9之间），并以#结束\n");
	while((ch=getchar()) != '\n' )
		op[i++] = ch;
	printf("%c\n", EvaluateExpression(op));
	return 0;
}