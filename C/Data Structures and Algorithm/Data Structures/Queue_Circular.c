/*
循环队列
操作队列（增减），然后返回队尾元素的位置和元素的个数
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MaxSize 2

// 把char类型定义为elemtype，便于后期修改
typedef char elemtype;

typedef struct Queue
{
	elemtype data[MaxSize]; // 数据段
	int Front; // 队头
	int Rear; // 队尾
}QU, Queue;

// 初始化队列
Queue Create()
{
	Queue Q;
	Q = (QU *)malloc(sizeof(QU));
	if (Q == NULL)
		printf("申请内存失败！\n");
	Q->Front = 0; // 初始化
	Q->Rear = 0;
	return Q; // 返回Q所在位置的指针，告诉别人Q在哪
}

// 判断队列元素长度，它既可以用来判断队满，也可以用来判断队空
int Len(Queue keep)
{
	int temp;
	// 当队头等于队尾的时候，就意味着队空
	if (keep->Front != keep->Rear)
	{
		temp = (keep->Rear - keep->Front + MaxSize) % MaxSize; // 获取队列元素长度
		if (temp == 0)
			return MaxSize;
		else
			return temp;
	}
	else
		return 0;
}

// 入队
int Push(Queue keep, elemtype x)
{
	if (Len(keep) == MaxSize)   // 判断队满，返回0
		return 0;
	else
	{
		keep->data[keep->Rear] = x;  // 队不满，则入队
		keep->Rear++;
		return 1;
	}
}

// 出队
int Pop(Queue keep)
{
	if (Len(keep) == 0)
	{
		printf("队列为空，无法出队！\n");
		return 0;
	}
	else
	{
		keep->Front++;
		return keep->data[keep->Front - 1];
	}
}

int PushSomething(Queue keep)
{
	elemtype x = 10;
	if (Len(keep) == MaxSize)
	{
		printf("队列已满！\n");
		return 1;
	}
	printf("请输入字符（输#结束）：");
	while (x != '#')
	{
		if (x != 10 && x != 32)
			Push(keep, x);
		if (Len(keep) == MaxSize)
			break; // 如果队满就跳出 
		scanf("%c", &x);
	}
	printf("队列长度为：%d\n", Len(keep));
	return Len(keep);
}

// 显示函数
int Show(Queue keep)
{
	int temp = 0;
	while (temp != Len(keep))
	{
		printf("%d ", keep->data[keep->Front + temp]);
		temp++;
	}
	printf("\n");
	return 1;
}

// 主函数
int main()
{
	int num = 0;
	Queue keep;
	keep = Create();
	while (1)
	{
		printf("--------队列功能界面--------\n");
		printf("---------1、输入字符--------\n");
		printf("---------2、弹出字符--------\n");
		printf("---------3、显示字符--------\n");
		printf("---------4、结束程序--------\n");
		printf("\n请输入功能界面数字：");
		fflush(stdin);
		scanf("%d", &num);
		system("cls");
		switch (num)
		{
		case 1:PushSomething(keep); break;
		case 2:Pop(keep); break;
		case 3:Show(keep); break;
		default: printf("输入错误！\n"); break;
		}
	}
	return 0;
}