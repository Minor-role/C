/*
	循环队列，操作队列（增减），然后返回队尾元素的位置和元素的个数
*/
#include <stdio.h>
#define N 10

// 把char类型定义为elemtype，便于后期修改
typedef char elemtype;

typedef struct Queue
{
	elemtype data[N]; // 数据段
	int First; // 队头
	int Rear; // 队尾
}QU,*Queue;

// 初始化队列
Queue Create()
{
	Queue Q;
	Q = (QU *)malloc(sizeof(QU));
	if(Q == NULL)
		printf("申请内存失败！\n");
	Q->
}
