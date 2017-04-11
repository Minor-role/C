// 例子： 2*3+(5-3/1)*2#
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

// 判断该进栈符号优先级是否高于栈顶符号
int Stack_XIsPrior(Stack S_all, Stack S_sub, elemtype *x)
{
	if(x == '*' | x == '/')   // 判断乘除号 
	{
		if(S_sub->data[S_sub->top] != '*' | S_sub->data[S_sub->top] != '/')	    //   遇到不是同一优先级的，返回 0 ,直接入栈 
			return 0;
		else if(S_sub->data[S_sub->top] == '*' | S_sub->data[S_sub->top] == '/')    // 遇到同一优先级的，返回 1 
			return 1;
	}
	else if (x == '+' | x == '-')   //  判断加减号 
	{
		while (Stack_IsEmpty(S_sub) == -1 | S_sub->data[S_sub->top] == '(')   //   遇到不是同一优先级的，返回 0 ,直接入栈 
		{
			Stack_In(S_all, S_sub->data[S_sub->top]);
			Stack_Pop; 
		} 
    }
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
		if (x > 47 && x < 58)
			Stack_In(S_all, x); 
		if (Stack_IsEmpty(S_sub) == -1 | x == '(') // 如果符号栈是空栈，符号是左括号，则直接入栈
			Stack_In(S_sub, x);
		else if(x == '*' | x == '/')
		{
			if (Stack_XIsPrior(S_all, S_sub, x) == 0)  // 判断为 0 则直接入栈 
			{
				Stack_In(S_sub, x);
			}
			else if (Stack_XIsPrior(S_all, S_sub, x) == 1)  // 判断为 1 ，表示有同一优先级，先弹栈再进栈 
			{ 
				Stack_In(S_all,S_sub->data[S_sub->top]);  // 符号栈 弹栈到 总栈
				Stack_Pop(S_sub);   // 符号栈 栈顶减一  
				Stack_In(S_sub, x);
			}
		}
		else if(x == '+' | x == '-') 
		{
			Stack_XIsPrior(S_all, S_sub, x);
		}
		else if(x == ')')
		{
			while(S_sub->data[S_sub->top] != '(')
			{
				Stack_In(S_all,S_sub->data[S_sub->top]);  // 符号栈 弹栈到 总栈
				Stack_Pop(S_sub);   // 符号栈 栈顶减一 
			}
			Stack_Pop(S_sub);  // 把 左括号也减掉 
		} 
	}
	while(Stack_IsEmpty(S_sub) != -1)
	{
		Stack_In(S_all,S_sub->data[S_sub->top]);  // 符号栈 弹栈到 总栈
		Stack_Pop(S_sub);   // 符号栈 栈顶减一 
	}
	for(; sign <= S_all->top; sign++)
		printf("%c",S_all->data[sign]);
	printf("\n");
	return 0;
}















