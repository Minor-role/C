#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
typedef char elemtype;

//define the Stack
typedef struct SequenStack
{
	elemtype data[N];     // 存放栈中元素的数组
	elemtype *;  // 指向数组的指针
	int top; // 数组的栈顶位置
}Stack;

// create a Stack
Stack Stack_Create()
{
	Stack *Save;
	Save = (Stack*)malloc(sizeof(Stack));
	if(Save == NULL)
		printf("申请内存失败！");
	Save->top = -1;
	return Save;
}
// 判断是否栈空
int Stack_IsEmpty(Stack Save)
{
	if(Save->top == -1)
		return -1;
	return 0;
}
// 数据入栈
int Stack_Save(Stack Save,elemtype x) 
{
	Save->top++;
	Save->data[Save->top] = x;
	return Save;
}

// 数据出栈
elemtype Stack_Save(Stack Save)  
{
	if(Stack_IsEmpty == -1)
		return 0;
	else
		return Save->top--;    // 栈顶下标减一，再返回栈顶下标
}

// 判断符号是否应该入符号栈
int SubscriptStack_IsEnter(Stack Save,elemtype x)
{
	if(Save->top == -1)
	{
		Stack_Save(Stack_Save,x);
		return 1;
	}
	else if()
}

int main()
{
	elemtype x;   // 输入值
	int sign = 0; 
	Stack *S_all,*S_subscript;  //  all是总栈，sub是符号栈
	S_all = Stack_Create();
	S_subscript = Stack_Create();
	printf("请输入一个表达式：\n");
	while(x != '#')
	{
		scanf("%c",&x);
		if(x > 47 && x < 58)  // 判断是否为数字
			S_all = Stack_Save(S_all,x);
		else if(x == 40 |x == 41 |x == 42 |x == 43 |x == 45 |x == 47) // ( ) * + - /
		{
			
		} 
	}
}