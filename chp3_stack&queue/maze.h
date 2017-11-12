typedef struct 
{
	int x;		// 横坐标
	int y;		// 纵坐标
}PosType;

typedef struct 
{
	int ord;	// 通道块在路径上的"序号"
	PosType seat;	// 通道块在迷宫中的坐标位置
	int di;		// 从此通道块走向下一通道块的方向(0-3表示东到北)
}SElemType;

// 定义墙元素值为0 可通过路径为1 不能通过路径为-1 通过路径为足迹

Status MazePath(PosType start, PosType end);
void MazePrint(int x, int y);
Status Pass(PosType b);
void FootPrint(PosType a);
PosType NextPos(PosType c, int di);
void MarkPrint(PosType b);