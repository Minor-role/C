/*
	求解逆波兰式
	传入中缀表达式，通过运算得出后缀表达式
*/
#include<stdio.h>
#include<stdlib.h>
#define N 100

// 把char类型定义为elemtype，便于后期修改
typedef char elemtype;

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
		return S->data[S->top]; 
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
	/* code */
	Stack S_all, S_sub, S_num;  // 定义三个栈，all是总栈，sub是符号栈
	elemtype x = 0;
	int sign = 0;
	S_sub = Stack_Create();
	S_all = Stack_Create();
	while(x != '#')
	{
		scanf("%c",&x);
		if(x >= '0' && x<= '9') // 数字直接入栈
			Push(S_all,x);
		else
		{
			switch(x)
			{
				case '#':break; 
				case '(': Push(S_sub,x);break;
				case ')': 
					while(Stack_IsEmpty(S_sub) != '(')   // 遇到的不是左括号，一直弹栈 
					{
						Push(S_all,Pop(S_sub));
					}
					Pop(S_sub);
					break;
				case '+':
				case '-':
					while(Stack_IsEmpty(S_sub) != 0 && Stack_IsEmpty(S_sub) != ('('))  //遇到高优先级的符号，一直弹栈 
					{
						Push(S_all,Pop(S_sub));
					}
					Push(S_sub,x); 
					break;
				case '*':
				case '/':
					while(Stack_IsEmpty(S_sub) != 0 && Stack_IsEmpty(S_sub) == ('*' || '/')) // 遇到栈空、高优先级或者同等优先级的就一直弹栈 
					{
						Push(S_all,Pop(S_sub));
					}
					Push(S_sub,x); 
					break; 
				default:printf("输入错误\n");break;
			}
		}
	}
	// 将符号栈弹出到总栈 
	while(Stack_IsEmpty(S_sub) != 0)  
	{
		Push(S_all,Pop(S_sub));
	}
	// 把栈当队列用，输出总栈内容 
	for(; sign <= S_all->top; sign++)
		printf("%c",S_all->data[sign]);
	return 0;
}