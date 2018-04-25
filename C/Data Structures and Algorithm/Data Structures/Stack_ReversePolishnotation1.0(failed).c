#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
typedef char elemtype;

//define the Stack
typedef struct SequenStack
{
	elemtype data[N];     // 存放栈中元素的数组
	int top; // 数组的栈顶位置
}*Stack;

// create a Stack
Stack Stack_Create()
{
	Stack Save;
	Save = (Stack *)malloc(sizeof(Stack));
	if(Save == NULL)
		printf("申请内存失败！");
	Save->top = -1;
	return Save;
}

// 判断是否栈空
int Stack_IsEmpty(Stack Save)
{
	if(Save->top == -1)
		return -1;  // 栈空为-1
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
	if(Stack_IsEmpty == -1)
		return 0;
	else
		return Save->top--;    // 栈顶下标减一，再返回栈顶下标
}

// 判断符号是否应该入符号栈
int SubscriptStack_IsEnter(Stack S_all, Stack S_subscript, elemtype *x)
{
	if(S_subscript->top == -1 && x != ')')
	{
		Stack_In(S_subscript,x);
		return 1;
	}
	if(x == '(') // 判断 左括号
	{
		Stack_In(S_subscript,x);  //  直接进栈
		return 1;
	}
	else if(x == ')')  // 判断 右括号
	{
		for(; S_subscript->data[S_subscript->top] != '('; )     // 弹出所有符号，直至遇到左括号
		{
			Stack_In(S_all, S_subscript->data[S_subscript->top]);
			Stack_Pop(S_subscript);
		}
		S_subscript->data[S_subscript->top] = 0;    // 删除左括号
		S_subscript->top--;    // 将栈顶位置top移向下一栈底位置
	}
	else if(x == '*' | x == '/')  // 判断乘除号
	{
		if(S_subscript->data[S_subscript->top] == '+' | S_subscript->data[S_subscript->top] == '-' | S_subscript->data[S_subscript->top] == '(' )  // 遇到优先级低的直接进栈
			Stack_In(S_subscript,x);
		else if(S_subscript->data[S_subscript->top] == '*' | S_subscript->data[S_subscript->top] == '/' )   // 遇到优先级高的，先把同级符号全弹栈，再进栈
		{
			for (; S_subscript->data[S_subscript->top] == '+' | S_subscript->data[S_subscript->top] == '-' | S_subscript->data[S_subscript->top] == '(';)
			{
				Stack_In(S_all, S_subscript->data[S_subscript->top]);
				Stack_Pop(S_subscript);
			}
			Stack_In(S_subscript, x);
		}
	}
	else if(x == '+' | x == '-')  // 判断加减号
	{
		if(Stack_IsEmpty(S_subscript) == -1 | S_subscript->data[S_subscript->top] == '(')   // 遇到栈底或者左括号直接进栈
			Stack_In(S_subscript, x);
		else if(S_subscript->data[S_subscript->top] == '*' | S_subscript->data[S_subscript->top] == '/' )   // 遇到优先级高的，先把同级和高级符号全弹栈，再进栈
		{
			for (; Stack_IsEmpty(S_subscript) == -1 | S_subscript->data[S_subscript->top] == '(';)
			{
				Stack_In(S_all, S_subscript->data[S_subscript->top]);
				Stack_Pop(S_subscript);
			}
			Stack_In(S_subscript, x);
		}
		else
		{
			printf("你的表达式有误，请再次输入！");
			return -1;
		}
	}
	return 0;
}

int main()
{
	elemtype x = 0;   // 输入值
	int sign = 0; 
	Stack S_all, S_subscript;  //  all是总栈，sub是符号栈
	S_all = Stack_Create();
	S_subscript = Stack_Create();
	printf("请输入一个表达式：\n");
	while(x != '#')
	{
		scanf("%c",&x);
		if(x > 47 && x < 58)  // 判断是否为数字
			S_all = Stack_In(S_all,x);
		else if(x == '(' | x == ')' | x == '*' |x == '/' |x == '+' |x == '-') 
		{
			SubscriptStack_IsEnter(S_all, S_subscript, x);
		}
		else
			printf("你的表达式有误，请再次输入！");
	}
	// 输出逆波兰式
	for(;sign != S_subscript->top+1; sign++)
		Stack_In(S_all, S_subscript->data[sign]);
	for(; sign != S_all->top+1; sign++)
		printf("%c", S_all->data[sign]);
	return 0;
}
