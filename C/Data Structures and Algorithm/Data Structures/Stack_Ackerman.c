/*
	求解Ackerman函数
	使用非递归算法，即 使用自己写的栈保存递归的过程
*/
#include <stdio.h>
#include <stdlib.h>
#define N 99999

// 由于传入函数的m值是整数，所以用int类型
typedef long elemtype;

// 定义结构体
typedef struct SequenStack
{
	elemtype data[N];
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

// 判断栈空
int Stack_IsEmpty(Stack S)
{
	if(S->top == -1)
		return 0;
	else 
		return 1;
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

// 主函数
int main()
{
	elemtype m, n;
	Stack keep_m; // 定义 keep_m 为 stack类型
	keep_m = Stack_Create(); // 创建保存m值的栈
	printf("请输入m：\n");  // 输入 m 和 n 值
	scanf("%d",&m);
	printf("请输入n：\n");
	scanf("%d",&n);
	Push(keep_m, m); // 将输入的m值都放进栈中
	while(Stack_IsEmpty(keep_m))
	{// 将 m 值保存在栈中，每次使用akm函数的时候，就从栈中弹出m，计算好的m又放回到栈中 
		m = Pop(keep_m); 
		if(m == 0)
			n = n+1;
		else if(m != 0 && n == 0)
		{
			Push(keep_m, m-1);
			n = 1;
		} 	
		else if(m != 0 && n != 0)
		{
			Push(keep_m, m-1);
			Push(keep_m, m);
			n = n-1;
		}
		else
			printf("算法有错误！\n");
	}
	printf("值为：%d\n", n);
	return 0;
}