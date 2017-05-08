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
		printf("�����ڴ�ʧ�ܣ�");
	Save->top = -1;
	return Save;
}

// �ж�ջ�Ƿ�Ϊ�� 
int Stack_IsEmpty(Stack Save)
{
	if(Save->top == -1)
		return 1;
	return 0; 
}

// ������ջ
int Stack_In(Stack Save,elemtype *x) 
{
	Save->top++;
	Save->data[Save->top] = x;
	return 0;
}

// ���ݳ�ջ
elemtype Stack_Pop(Stack Save)  
{
	if(Save->top == -1)
		return 1;
	else
		return Save->top--;    // ջ���±��һ���ٷ���ջ���±�
} 

// �������ȼ����� 
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

// �ж����ȼ�
int IsPriority(elemtype *x1, elemtype *x2)   //  Ĭ��ǰ����ջ�з��ţ�������ɨ����� ������ԽС�����ȼ�Խ�� 
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
			printf("������ַ��������������룡\n");
		}
		if(x > 47 && x < 58)   // ��������֣�ֱ�ӽ���ջ 
			Stack_In(S_all, x);
		else if(x == '(' || (Stack_IsEmpty(S_sub)  && x != ')'))   // ����������Ż���ջΪ��ֱ�ӽ�����ջ 
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
