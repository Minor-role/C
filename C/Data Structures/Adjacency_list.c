/*
	2017年6月25日11:00:00
	用邻接表存储一个有向图G
	算法思想：
	1. 确定图的顶点个数和边的个数
	2. 输入顶点信息，初始化该顶点的顶点表
	3. 依次输入边的信息并存储在边表中
		3.1 输入边所依附的两个顶点的序号i和j
		3.2 生成邻接点序号为j的边表结点s
		3.3 将结点s插入到第i个边表的头部(头插法，因此不需要对边表进行初始化)
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

// 计算每个顶点的出度
void CountOutDegree(int n)
{
	int i;
	int counter; // 计数器
	Edge *s;
	s = (Edge *)malloc(sizeof(Edge));
	for(i=0; i<n; i++)
	{	
		counter = 0; // 计数器置零
		s = graphNode[i].firstEdge;
		while(s != NULL)
		{
			s = s-> nextEdge; // 指向下一个边表结点
			counter++;
		}
		graphNode[i].counter = counter;
		printf("结点%d的出度为：%d\n", i, graphNode[i].counter);
	}

}

int main()
{
	int n;
	n = CreateVer();
	CountOutDegree(n);
	system("pause");
	return 0;
}