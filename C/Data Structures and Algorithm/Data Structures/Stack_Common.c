#include<stdio.h>
#define N 100

typedef char elemtype;

typedef struct SequenStack
{
	elemtype data[N];
	int top; 
}*Stack;

Stack Stack_Create()
{
	Stack Save;
	Save = (Stack *)malloc(sizeof(Stack));
	if(Save == NULL)
		printf("申请内存失败！");
	Save->top = -1;
	return Save;
}


// 数据入栈
int Stack_In(Stack Save,elemtype *x) 
{
	Save->top++;
	Save->data[Save->top] = x;
	return 0;
}

// 数据出栈
elemtype Stack_Pop(Stack Save)  
{
	if(Save->top == -1)
		return 0;
	else
		return Save->top--;    // 栈顶下标减一，再返回栈顶下标
}


int main()
{
	int sign = 0;
	Stack S_all,S_sub;
	elemtype x = 0;
	S_all = Stack_Create();
	S_sub = Stack_Create();
	while(x != '#')
	{
		scanf("%c",&x);
		Stack_In(S_all,x); 
	}
	for(; S_all->top > -1; Stack_Pop(S_all))
		printf("%c",S_all->data[S_all->top]);
	printf("\n");
	printf("%d",S_sub->top);
	return 0;
}
