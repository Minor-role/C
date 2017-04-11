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

// 判断栈是否为空 
int Stack_IsEmpty(Stack Save)
{
	if(Save->top == -1)
		return 1;
	return 0; 
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
		return 1;
	else
		return Save->top--;    // 栈顶下标减一，再返回栈顶下标
} 

// 符号优先级代号 
int Priority(elemtype *x)
{
    if(x == '(')
		return 1;
	else if(x == ')')
		return 2;
	else if(x == '*' || x == '/')
		return 3;
	else if(x == '+' || x == '-')
		return 4;
	return -1;
}

// 判断优先级
int IsPriority(elemtype *x1, elemtype *x2)   //  默认前者是栈中符号，后者是扫描符号 ，数字越小，优先级越高 
{
	if(Priority(x1) < Priority(x2))
		return 0;
	else if(Priority(x1) == Priority(x2))
		return 1;
	else if(Priority(x1) > Priority(x2))
		return 2;
	return 0;
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
		if(x != '#' &&(Priority(x) < 1 && Priority(x) > 4))
		{
			printf("输入的字符有误，请重新输入！\n");
		}
		if(x > 47 && x < 58)   // 如果是数字，直接进总栈 
			Stack_In(S_all, x);
		else if(x == '(' || (Stack_IsEmpty(S_sub)  && x != ')'))   // 如果是左括号或者栈为空直接进符号栈 
			Stack_In(S_sub, x);
		else if(Priority(x) >=1 && Priority(x) <=4)  
		{
			while(IsPriority(S_sub->data[S_sub->top], x) != 0)
			{
				Stack_In(S_all, S_sub->data[S_sub->top]);
				Stack_Pop(S_sub);
			}
		}
	}
	while(! Stack_IsEmpty(S_sub))
	{
		Stack_In(S_all, S_sub->data[S_sub->top]);
		Stack_Pop(S_sub);
	}
	for(; sign <= S_all->top; sign ++)
		printf("%c",S_all->data[sign]);
	printf("\n");
	return 0;
}
