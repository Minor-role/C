/*
	2017年6月25日20:34:18
	编写一个实现连通图G的深度优先遍历
	算法思想：
	1. 访问第一个顶点v
	2. 访问顶点v的第一个邻接点a
	3. 从邻接点a再访问a的第一个邻接点b
	4. 如此类推，如果第一个访问完，就访问第二个(是从底层访问到表层，比如先访问b的所有邻接点，再访问a，最后再访问v)
	步骤：
	1. 建立有向图邻接表
	2. 深度优先搜索
		2.1 创建一个新的数组visited[v]; (用于标志结点是否已经被访问)
		2.2 深度优先搜索算法
			2.2.1 访问顶点v; visited[v] = 1;
			2.2.2 p =顶点v的第一个邻接点；
			2.2.3 while (p存在) 
    			2.2.3.1 if (p未被访问) 从顶点p出发递归执行该算法;
    			2.2.3.2 p = 顶点v的下一个邻接点;
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define Max 10

// 边表结点
typedef struct Edge 
{
	int adjvex;//邻接点域，边的终点在顶点表中的下标,邻接点以数字编号，如 0,1,2,...,9 
	struct Edge *nextEdge; // 指针域，指向边表中的下一个结点
}Edge;

// 顶点表结点
typedef struct VerNode 
{
	int vertex;//数据域，存放顶点信息,顶点以数字编号，如 0,1,2,...,9
	int counter; // 出度值
	struct Edge *firstEdge;// 指针域，指向边表中第一个结点
}VerNode; 


VerNode graphNode[Max];// 全局变量，申请图 顶点数组 的内存空间

// 创建有向图邻接表
int CreateVer()
{
	int i, j, k, n, e;
	Edge *s; // 存放边表结点的指针

	printf("请输入顶点数和边数(输入格式为:顶点数,边数)："); 
	scanf("%d,%d", &n, &e);  // n表示顶点，e表示边
	printf("请输入顶点信息(输入格式为:<回车>顶点号)：");

	//读入顶点表信息
	for(i=0; i<n; i++)
	{
		scanf("\n%d", &graphNode[i].vertex); 
		graphNode[i].firstEdge = NULL; // 初始化，顶点的边表头指针设为空
	}
	printf("请输入边的信息(输入格式为:i,j)：\n");

	// 输入边表信息,并将边表和顶点表结合起来
	for(k=0; k<e; k++)
	{
		scanf("%d, %d", &i, &j); // 读入边<Vi,Vj>的顶点对应序号
		s = (Edge *)malloc(sizeof(Edge));
		s->adjvex = j;
		s->nextEdge = graphNode[i].firstEdge; // 头插法，可以将firstEdge的NULL给s，所以不需要初始化
		graphNode[i].firstEdge = s;
	}
	return n;
}


void DFS(int i, int visited[]) 
{
	Edge *p; 
	printf("V%d->",graphNode[i].vertex); // 输出顶点vi的数据域信息
	visited[i] = 1; //标志顶点Vi 已访问 
	p=graphNode[i].firstEdge; // 访问顶点vi的第一个邻接点
	while(p) // 邻接点存在
	{
		if (!visited[p->adjvex]) // 邻接点没有被访问
			DFS(p->adjvex, visited); // 访问邻接点
		p=p->nextEdge; 
	} 
}

// 深度优先搜索遍历算法
void DFSTraverse(int vertexNum) 
{
	int i; 
	int visited[Max]; 
	for(i=0;i<vertexNum;i++) //重置顶点访问数组 
		visited[i]=0;
	printf("图的深度优先遍历序列为："); 
	for(i=0; i<vertexNum; i++) //从第 1 个顶点开始依次遍历 
		if(!visited[i])  // 如果没被访问
			DFS(i, visited);
}

int main(int argc, char const *argv[])
{
	int n;
	n = CreateVer();
	DFSTraverse(n);
	printf("\n");
	system("pause");
	return 0;
}
