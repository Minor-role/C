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

int main()
{
	Stack *S_all,*S_subscript;  //  all存储表达式所有语句，sub只存储表达式的符号
	S_all = Stack_Create();
	S_subscript = Stack_Create();
	
}