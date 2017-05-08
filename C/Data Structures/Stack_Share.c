/*
	共享栈，就是两个栈的栈顶拼接到一起，使用同一段存储空间
*/
#include <stdio.h>
#define MaxLen 10

// 把char类型定义为elemtype，便于后期修改
typedef char elemtype;

// 定义结构体
typedef struct SequenStack
{
	elemtype data[MaxLen/2];
	int top; 
}ST,*Stack; // 结构体指针

// 初始化栈 
Stack Stack_Create()
{
	Stack S;
	S = (ST *)malloc(sizeof(ST));
	if(S == NULL)
		printf("申请内存失败！");
	S->top = -1;
	return S;
}

// 数据入栈
int Push(Stack S,elemtype x) 
{

	S->top++;
	S->data[S->top] = x;
	return 1;
}

// 数据出栈
elemtype Pop(Stack S)  
{
	if(S->top == -1)
		return 0;
	else
	{
		S->top--;
		return S->data[S->top+1]; 
	} 
} 

// 判断是否栈满
int Full(Stack S1,Stack S2)
{
	if(S1->top + S2->top == MaxLen - 2)
		return 0;
	else 
		return 1;
}

