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
int Stack_Pop(Stack Save)  
{
	if(Save->top == -1)
		return 0;
	else
		Save->top--;	// 栈顶下标减一
	return Save->top; 
}

// 判断栈是否为空 
int Stack_IsEmpty(Stack Save)
{
	if(Save->top == -1)
		return -1;
	return 0; 
}

// 判断符号入符号栈
int Stack_IsIn(Stack Save, elemtype *x);
{
	if(x == '(') // 如果符号是左括号，则直接入栈
	{
		Stack_In(Save, x);
		return 0; 
	}
	else if (Stack_XIsPrior(Save, x) == 0)  // 判断该进栈的符号优先级是否高于栈顶符号，如果是则直接入栈 
	{
		Stack_In(Save, x);
		return 0;
	}
	else if (Stack_XIsPrior(Save, x) == 1)  // 判断该进栈的符号优先级是否等于栈顶符号，如果是则弹出一个再进栈 
	{
		
		Stack_In(Save, x);
		return 0;
	}
}

// 判断该进栈符号优先级是否高于栈顶符号
int Stack_XIsPrior(Stack Save, elemtype *x)
{
	if(x == '*' | x == '/')
	{
		if(Save->data[Save->top] != '*' | Save->data[Save->top] != '/')	
			return 0;
		else if(Save->data[Save->top] == '*' | Save->data[Save->top] == '/')
			return 1;
	}
		
		
	return -1;
}

//  

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
		if(x == '(') // 如果符号是左括号，则直接入栈
		{
			Stack_In(S_sub, x);
			return 0; 
		}
		else if (Stack_XIsPrior(S_sub, x) == 0)  // 判断该进栈的符号优先级是否高于栈顶符号，如果是则直接入栈 
		{
			Stack_In(S_sub, x);
			return 0;
		}
		else if (Stack_XIsPrior(S_sub, x) == 1)  // 判断该进栈的符号优先级是否等于栈顶符号，如果是则弹出一个再进栈 
		{
		
			Stack_In(S_sub, x);
			return 0;
		}
	}
	
	for(; S_all->top > -1; Stack_Pop(S_all))
		printf("%c",S_all->data[S_all->top]);
	printf("\n");
	printf("%d",S_sub->top);
	return 0;
}
