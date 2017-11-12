#include "myheader.h"
#include "SqStack.h"
#define MAXSIZE 15		// 迷宫大小
typedef int MazeType;

MazeType maze[MAXSIZE][MAXSIZE];			// 全局变量，迷宫数组
int curstep = 1;	// 当前足迹，初值为1

Status MazePath(PosType start, PosType end){
	//	若迷宫maze中存在从入口start到出口end的通道，则求得一条
	//	存放在栈中(从栈底到栈顶)，并返回TRUE；否则返回FALSE
	SqStack S;
	SElemType e;
	InitStack(&S);
	PosType curpos = start;
	do{
		if(Pass(curpos)){	// 当前路径可通过
			FootPrint(curpos);	// 留下足迹
			e.ord = curstep;
			e.seat = curpos;
			e.di = 0;
			Push(&S, e);		// 加入路径
			curstep++;		// 足迹加一
			if(curpos.x == end.x && curpos.y == end.y) return TRUE;	//	到达终点
			curpos = NextPos(curpos, e.di);
		}
		else{	// 当前位置不能通过
			if (!StackEmpty(S)){
				Pop(&S, &e);	// 退栈到前一位置
				curstep--;
				while(e.di==3 && !StackEmpty(S)){	// 前一位置处于最后一个方向
					MarkPrint(e.seat);	// 留下不能通过的标记（-1）
					Pop(&S, &e);
					curstep--;
				}
				if (e.di<3){	// 没到最后一个方向
					e.di++;
					Push(&S, e);
					curstep++;
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	}while(!StackEmpty(S));
	return FALSE;
}

void MazePrint(int x, int y){	// 输出迷宫的解
	int i,j;
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++)
			printf("%3d", maze[i][j]);
		printf("\n");
	}
}

Status Pass(PosType b){
	// 当迷宫maze 的b点的序号为1(可通过路径) return OK
	return (maze[b.x][b.y]==1)?OK:ERROR;
}

void FootPrint(PosType a){
	// 使迷宫maze的a点变为足迹
	maze[a.x][a.y] = curstep;
}

PosType NextPos(PosType c, int di){
	// 根据当前位置及移动方向返回下一位置
	PosType direct[4]={{0,1},{1,0},{0,-1},{-1,0}};		// {行增量，列增量}
	// 移动方向依次为东南西北
	c.x += direct[di].x;
	c.y += direct[di].y;
	return c;
}

void MarkPrint(PosType b){	// 使迷宫b点的序号变为-1(不能通过的路径)
	maze[b.x][b.y] = -1;
}

int main(int argc, char const *argv[])
{
	PosType begin,end;
	int i,j,x,y,x1,y1;
	printf("输入迷宫的行列数，包括外墙:\n");
	scanf("%d,%d", &x,&y);
	for(i=0; i<x; i++){	// 定义周边值为0(墙)
		maze[0][i] = 0;	// 行周边
		maze[x-1][i] = 0;
	}
	for(j=0; j<y; j++){
		maze[j][0] = 0;	// 列周边
		maze[j][y-1] = 0;
	}
	for(i=1; i<x-1; i++)
		for(j=1; j<y-1; j++)
			maze[i][j] = 1;	// 定义通道初值为1
	printf("请输入迷宫内墙单元数：");
	scanf("%d",&j);
	printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
	for(i=1; i<=j; i++){
		scanf("%d,%d",&x1,&y1);
		maze[x1][y1] = 0;	// 定义墙的值为0
	}
	printf("迷宫结构如下:\n");
	MazePrint(x,y);
	printf("请输入起点的行数,列数：");
	scanf("%d,%d",&begin.x,&begin.y);
	printf("请输入终点的行数,列数：");
	scanf("%d,%d",&end.x,&end.y);
	if(MazePath(begin,end)){	 // 求得一条通路
	printf("此迷宫从入口到出口的一条路径如下:\n");
	MazePrint(x,y);		// 输出此通路
	}
	else
	printf("此迷宫没有从入口到出口的路径\n");
	return 0;
}