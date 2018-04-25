#include<stdio.h>
#include<stdlib.h> 
#define N 100

// ��char���Ͷ���Ϊelemtype�����ں����޸� 
typedef char elemtype;

// ����ṹ�� 
typedef struct SequenStack
{
	elemtype data[N];
	int top; 
}ST,*Stack; // �ṹ��ָ�� 

// ��ʼ��ջ 
Stack Stack_Create()
{
	Stack S;
	S = (ST *)malloc(sizeof(ST));
	if(S == NULL)
		printf("�����ڴ�ʧ�ܣ�");
	S->top = -1;
	return S;
}

// �ж�ջ�Ƿ�Ϊ�� 
int Stack_IsEmpty(Stack S)
{
	if(S->top == -1)
		return 1;
	else 
		return 0; 
}

// ������ջ
int Stack_In(Stack S,elemtype x) 
{
	S->top++;
	S->data[S->top] = x;
	return 1;
}

// ���ݳ�ջ
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

// �������ȼ����� ,����Խ�����ȼ�Խ�� 
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

// ���ַ���ת��Ϊ���Ӧ��ʮ������
int TranslateStr(Stack S, elemtype *save_number)
{
	int i = 1;
	int temp = 1; // ���浯������ջֵ 
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
	elemtype temp = 0; // ��ʱ���浯ջ�Ĳ������������ 
	int sign = 0; 
	Stack S_all, S_sub, S_num;  // ��������ջ��all����ջ��sub�Ƿ���ջ��num������ջ 
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
		if(Priority(x) == 5)  // ��������֣�ֱ��������ջ 
		{
			while(Stack_IsEmpty(S_sub) != 1)
			{
				temp = Stack_Pop(S_sub, temp); 
				Stack_In(S_all, temp);
			}
			Stack_In(S_all, x);	
		}
								
//		if(Priority(x) < 5 && Stack_IsEmpty(S_num) == 0)   // �����������ַ���������ջ��Ϊ�գ�����ջ�����ְᵽ��ջ 
//		{
//			temp = TranslateStr(S_num, temp); 
//			Stack_In(S_all, temp); 
//		} 
		else if(Priority(x) == 4) // ����������ţ���ֱ�������ջ
			Stack_In(S_sub, x);
		else if(Priority(x) == 3)  // ����������ţ��򵯷���ջ����ջֱ����������Ϊֹ 
		{
			while(Priority(S_sub->data[S_sub->top] != '('))
			{
				temp = Stack_Pop(S_sub, temp); 
				Stack_In(S_all, temp);
			} 
		}
		else if(Priority(x) == 2) // ����ǳˡ����ţ���ջ����Ϊ�ˡ�����ʱ����ջ
		{
			while(Priority(S_sub->data[S_sub->top] == 2))
			{
				temp = Stack_Pop(S_sub, temp); 
				Stack_In(S_all, temp);
			}
			Stack_In(S_sub, x);
		} 
		else if(Priority(x) == 1)  // ����Ǽӡ����ţ�������ջ����ջ��Ϊ�����ŵ�ʱ����ջ 
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
