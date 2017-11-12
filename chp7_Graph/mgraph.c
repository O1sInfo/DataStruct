#include "./myheader.h"
#include "mgraph.h"
# define MAX_INFO 100
int LocateVex(MGraph G, VertexType u){
	// 若G中存在顶点u, 则返回该顶点在图中的位置，否则返回-1
	int i;
	for (i = 0; i < G.vexnum; ++i)
		if (strcmp(u, G.vexs[i]) == 0)
			return i;
	return -1;
}

Status CreateFUDG(MGraph *G){
	// 采用数组(邻接矩阵)表示法，由文件构造没有相关信息的无向图
	int i, j, k;
	char filename[15];
	VertexType va, vb;
	FILE *graphdata;
	printf("Please input the filename of graph data\n");
	scanf("%s", filename);
	fscanf(graphdata, "%d", &(*G).vexnum);
	fscanf(graphdata, "%d", &(*G).arcnum);
	for (i = 0; i < (*G).vexnum; ++i)	// 构造顶点向量
		fscanf(graphdata, "%s", (*G).vexs[i]);	// ?
	for (i = 0; i < (*G).vexnum; ++i)	// 初始化邻接矩阵
		for (j = 0; j < (*G).vexnum; ++j){
			(*G).arcs[i][j].adj = 0;
			(*G).arcs[i][j].info = NULL;
		}
	for (k = 0; k < (*G).arcnum; ++k){
		fscanf(graphdata, "%s%s", va, vb);
		i = LocateVex(*G, va);
		j = LocateVex(*G, vb);
		(*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;	// 无向图
	}
	fclose(graphdata);
	(*G).kind = UDG;
	return OK;
}

Status CreateDG(MGraph *G){
	// 采用数组(邻接矩阵)表示法，构造有向图G
	int i, j, k, len, IncInfo;
	char s[MAX_INFO], *info;
	VertexType va, vb;
	printf("Please input the number of vertex and arc (Digraph) and whether the arc include other info (0:yes 1:no)\n");
	scanf("%d%d%d", &(*G).vexnum, &(*G).arcnum, &IncInfo);
	printf("Please input the value of %d vertexs (char)\n", (*G).vexnum);
	for (i = 0; i < (*G).vexnum; ++i)
		scanf("%s", (*G).vexs[i]);			// 构造顶点向量
	for (i = 0; i < (*G).vexnum; ++i)		// 初始化邻接矩阵
		for (j = 0; j < (*G).vexnum; ++j){
			(*G).arcs[i][j].adj = 0;
			(*G).arcs[i][j].info = NULL;
		}
	printf("Please input the tail and head of %d arcs\n", (*G).arcnum);
	for (k = 0; k < (*G).vexnum; ++k){
		scanf("%s%s%*c", va, vb);			// %*c吃掉回车符
		i = LocateVex(*G, va);
		j = LocateVex(*G, vb);
		(*G).arcs[i][j].adj = 1;			// 有向图
		if (IncInfo){
			printf("Please input the arc's info\n");
			gets(s);
			len = strlen(s);
			if (len){
				info = (char*)malloc((len+1)*sizeof(char));
				strcpy(info, s);
				(*G).arcs[i][j].info = info;
			}
		}
	}
	(*G).kind = DG;
	return OK;
}

Status CreateDN(MGraph *G){
	// 采用数组(邻接矩阵)表示法, 构造有向网
	int i, j, k, w, IncInfo;
	char s[MAX_INFO], *info;
	VertexType va, vb;
	printf("Please input the number of vertex and arc (DN) and whether the arc include other info (0:yes 1:no)\n");
	scanf("%d%d%d", &(*G).vexnum, &(*G).arcnum, &IncInfo);
	printf("Please input the value of %d vertexs (char)\n", (*G).vexnum);
	for (i = 0; i < (*G).vexnum; ++i)
		scanf("%s", (*G).vexs[i]);			// 构造顶点向量
	for (i = 0; i < (*G).vexnum; ++i)		// 初始化邻接矩阵
		for (j = 0; j < (*G).vexnum; ++j){
			(*G).arcs[i][j].adj = INFINITY;	// 网
			(*G).arcs[i][j].info = NULL;
		}
	printf("Please input the tail, head and weight of %d arcs\n", (*G).arcnum);
	for (k = 0; k < (*G).vexnum; ++k){
		scanf("%s%s%d%*c", va, vb, &w);			// %*c吃掉回车符
		i = LocateVex(*G, va);
		j = LocateVex(*G, vb);
		(*G).arcs[i][j].adj = w;			// 有向图
		if (IncInfo){
			printf("Please input the arc's info\n");
			gets(s);
			len = strlen(s);
			if (len){
				info = (char*)malloc((len+1)*sizeof(char));
				strcpy(info, s);
				(*G).arcs[i][j].info = info;
			}
		}
	}
	(*G).kind = DN;
	return OK;
}

Status CreateUDG(MGraph *G){
	// 采用数组(邻接矩阵)表示法, 构造无向网
	int i, k, j, len, IncInf;
	char s[MAS_INFO], *info;
	VertexType va, vb;
	printf("Please input the number of vertex and arc (DN) and whether the arc include other info (0:yes 1:no)\n");
	scanf("%d%d%d", &(*G).vexnum, &(*G).arcnum, &IncInfo);
	printf("Please input the value of %d vertexs (char)\n", (*G).vexnum);
	for (i = 0; i < (*G).vexnum; ++i)
		scanf("%s", (*G).vexs[i]);			// 构造顶点向量
	for (i = 0; i < (*G).vexnum; ++i)		// 初始化邻接矩阵
		for (j = 0; j < (*G).vexnum; ++j){
			(*G).arcs[i][j].adj = 0;	// 图
			(*G).arcs[i][j].info = NULL;
		}
	printf("Please input the tail, head and weight of %d arcs\n", (*G).arcnum);
	for (k = 0; k < (*G).vexnum; ++k){
		scanf("%s%s%d%*c", va, vb, &w);			// %*c吃掉回车符
		i = LocateVex(*G, va);
		j = LocateVex(*G, vb);
		(*G).arcs[i][j].adj = w;			// 有向图
		if (IncInfo){
			printf("Please input the arc's info\n");
			gets(s);
			len = strlen(s);
			if (len){
				info = (char*)malloc((len+1)*sizeof(char));
				strcpy(info, s);
				(*G).arcs[i][j].info = info;
			}
		}
	}
	(*G).kind = DN;
	return OK;
}