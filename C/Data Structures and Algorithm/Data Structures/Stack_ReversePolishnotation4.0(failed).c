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

// 判断栈是否为空 
int Stack_IsEmpty(Stack S)
{
	if(S->top == -1)
		return 1;
	else 
		return 0; 
}

// 数据入栈
int Stack_In(Stack S,elemtype x) 
{
	S->top++;
	S->data[S->top] = x;
	return 1;
}

// 数据出栈
int Stack_Pop(Stack S, elemtype x)  
{
	if(S->top == -1)
		return 0;
	else
	{
		S->top--;
		x = S->data[S->top+1];
		return 1; 
	} 
} 

// 符号优先级代号 ,数字越大，优先级越高 
int Priority(elemtype x)
{
	if(x >= '0' && x <= '9')
		return 5;
    else if(x == '(')
		return 4;
	else if(x == ')')
		return 3;
	else if(x == '*' || x == '/')
		return 2;
	else if(x == '+' || x == '-')
		return 1;
	return 0;
}

// 将字符串转换为相对应的十进制数
int TranslateStr(Stack S, elemtype *save_number)
{
	int i = 1;
	int temp = 1; // 保存弹出来的栈值 
	*save_number = 0;
	for(; S->top != -1; i*10)
	{
		 Stack_Pop(S, temp);
		 *save_number = *save_number + temp*i;
	}
	return 1;
}

int main()
{
	elemtype temp = 0; // 临时保存弹栈的操作符或操作数 
	int sign = 0; 
	Stack S_all, S_sub, S_num;  // 定义三个栈，all是总栈，sub是符号栈，num是数字栈 
	elemtype x = 0;
	S_all = Stack_Create();
	S_sub = Stack_Create();
	S_num = Stack_Create();
	while(x != '#')
	{
		scanf("%c",&x);
		if (x == 32)
			continue;
		printf("%c\n",x);
		if(Priority(x) == 5)  // 如果是数字，直接入数字栈 
		{
			while(Stack_IsEmpty(S_sub) != 1)
			{
				temp = Stack_Pop(S_sub, temp); 
				Stack_In(S_all, temp);
			}
			Stack_In(S_all, x);	
		}
								
//		if(Priority(x) < 5 && Stack_IsEmpty(S_num) == 0)   // 遇到非数字字符，且数字栈不为空，数字栈的数字搬到总栈 
//		{
//			temp = TranslateStr(S_num, temp); 
//			Stack_In(S_all, temp); 
//		} 
		else if(Priority(x) == 4) // 如果是左括号，则直接入符号栈
			Stack_In(S_sub, x);
		else if(Priority(x) == 3)  // 如果是右括号，则弹符号栈到总栈直至到左括号为止 
		{
			while(Priority(S_sub->data[S_sub->top] != '('))
			{
				temp = Stack_Pop(S_sub, temp); 
				Stack_In(S_all, temp);
			} 
		}
		else if(Priority(x) == 2) // 如果是乘、除号，当栈顶不为乘、除号时，进栈
		{
			while(Priority(S_sub->data[S_sub->top] == 2))
			{
				temp = Stack_Pop(S_sub, temp); 
				Stack_In(S_all, temp);
			}
			Stack_In(S_sub, x);
		} 
		else if(Priority(x) == 1)  // 如果是加、减号，遇到空栈或者栈顶为左括号的时候入栈 
		{
			while(Stack_IsEmpty(S_sub) != 1 || S_sub->data[S_sub->top] != '(')
			{
				temp = Stack_Pop(S_sub, temp); 
				Stack_In(S_all, temp);
			}
			Stack_In(S_sub, x);
		}
	}
	while(Stack_IsEmpty(S_sub) != 1)
	{
		temp = Stack_Pop(S_sub, temp); 
		Stack_In(S_all, temp);
	}
	for(; sign <= S_all->top; sign++)
		printf("%c",S_all->data[sign]);
	printf("\n");
	return 0;
}
