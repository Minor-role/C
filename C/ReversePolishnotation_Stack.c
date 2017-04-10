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


// ������ջ
int Stack_In(Stack Save,elemtype *x) 
{
	Save->top++;
	Save->data[Save->top] = x;
	return 0;
}

// ���ݳ�ջ
int Stack_Pop(Stack Save)  
{
	if(Save->top == -1)
		return 0;
	else
		Save->top--;	// ջ���±��һ
	return Save->top; 
}

// �ж�ջ�Ƿ�Ϊ�� 
int Stack_IsEmpty(Stack Save)
{
	if(Save->top == -1)
		return -1;
	return 0; 
}

// �жϷ��������ջ
int Stack_IsIn(Stack Save, elemtype *x);
{
	if(x == '(') // ��������������ţ���ֱ����ջ
	{
		Stack_In(Save, x);
		return 0; 
	}
	else if (Stack_XIsPrior(Save, x) == 0)  // �жϸý�ջ�ķ������ȼ��Ƿ����ջ�����ţ��������ֱ����ջ 
	{
		Stack_In(Save, x);
		return 0;
	}
	else if (Stack_XIsPrior(Save, x) == 1)  // �жϸý�ջ�ķ������ȼ��Ƿ����ջ�����ţ�������򵯳�һ���ٽ�ջ 
	{
		
		Stack_In(Save, x);
		return 0;
	}
}

// �жϸý�ջ�������ȼ��Ƿ����ջ������
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
		if(x == '(') // ��������������ţ���ֱ����ջ
		{
			Stack_In(S_sub, x);
			return 0; 
		}
		else if (Stack_XIsPrior(S_sub, x) == 0)  // �жϸý�ջ�ķ������ȼ��Ƿ����ջ�����ţ��������ֱ����ջ 
		{
			Stack_In(S_sub, x);
			return 0;
		}
		else if (Stack_XIsPrior(S_sub, x) == 1)  // �жϸý�ջ�ķ������ȼ��Ƿ����ջ�����ţ�������򵯳�һ���ٽ�ջ 
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
