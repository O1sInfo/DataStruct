// 图的数组邻接矩阵存储表示
#define INFINITY INT_MAX	// 无穷大
#define MAX_VERTEX_NUM 20	// 最大顶点个数
typedef enum {DG, DN, UDG, UDN}GraphKind;	// 有向图, 有向网, 无向图, 无向网

typedef struct ArcCell		// 弧单元
{
	VRType adj;				// VRType是顶点关系类型, 对无权图, 用0，1表示相邻与否，对有向图，则为权值类型
	InfoType *info;			// 该弧相关的信息
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct 
{
	VertexType vexs[MAX_VERTEX_NUM];	// 顶点向量
	AdjMatrix arcs;						// 邻接矩阵
	int vexnum, arcnum;					// 图的当前顶点数和弧数
	GraphKind kind;						// 图的种类标志	
}MGraph;
