#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100
typedef char elemtype;

//define the Stack
typedef struct SequenStack
{
	elemtype data[N];     // ���ջ��Ԫ�ص�����
	int top; // �����ջ��λ��
}*Stack;

// create a Stack
Stack Stack_Create()
{
	Stack Save;
	Save = (Stack *)malloc(sizeof(Stack));
	if(Save == NULL)
		printf("�����ڴ�ʧ�ܣ�");
	Save->top = -1;
	return Save;
}

// �ж��Ƿ�ջ��
int Stack_IsEmpty(Stack Save)
{
	if(Save->top == -1)
		return -1;  // ջ��Ϊ-1
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
	if(Stack_IsEmpty == -1)
		return 0;
	else
		return Save->top--;    // ջ���±��һ���ٷ���ջ���±�
}

// �жϷ����Ƿ�Ӧ�������ջ
int SubscriptStack_IsEnter(Stack S_all, Stack S_subscript, elemtype *x)
{
	if(S_subscript->top == -1 && x != ')')
	{
		Stack_In(S_subscript,x);
		return 1;
	}
	if(x == '(') // �ж� ������
	{
		Stack_In(S_subscript,x);  //  ֱ�ӽ�ջ
		return 1;
	}
	else if(x == ')')  // �ж� ������
	{
		for(; S_subscript->data[S_subscript->top] != '('; )     // �������з��ţ�ֱ������������
		{
			Stack_In(S_all, S_subscript->data[S_subscript->top]);
			Stack_Pop(S_subscript);
		}
		S_subscript->data[S_subscript->top] = 0;    // ɾ��������
		S_subscript->top--;    // ��ջ��λ��top������һջ��λ��
	}
	else if(x == '*' | x == '/')  // �жϳ˳���
	{
		if(S_subscript->data[S_subscript->top] == '+' | S_subscript->data[S_subscript->top] == '-' | S_subscript->data[S_subscript->top] == '(' )  // �������ȼ��͵�ֱ�ӽ�ջ
			Stack_In(S_subscript,x);
		else if(S_subscript->data[S_subscript->top] == '*' | S_subscript->data[S_subscript->top] == '/' )   // �������ȼ��ߵģ��Ȱ�ͬ������ȫ��ջ���ٽ�ջ
		{
			for (; S_subscript->data[S_subscript->top] == '+' | S_subscript->data[S_subscript->top] == '-' | S_subscript->data[S_subscript->top] == '(';)
			{
				Stack_In(S_all, S_subscript->data[S_subscript->top]);
				Stack_Pop(S_subscript);
			}
			Stack_In(S_subscript, x);
		}
	}
	else if(x == '+' | x == '-')  // �жϼӼ���
	{
		if(Stack_IsEmpty(S_subscript) == -1 | S_subscript->data[S_subscript->top] == '(')   // ����ջ�׻���������ֱ�ӽ�ջ
			Stack_In(S_subscript, x);
		else if(S_subscript->data[S_subscript->top] == '*' | S_subscript->data[S_subscript->top] == '/' )   // �������ȼ��ߵģ��Ȱ�ͬ���͸߼�����ȫ��ջ���ٽ�ջ
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
			printf("��ı��ʽ�������ٴ����룡");
			return -1;
		}
	}
	return 0;
}

int main()
{
	elemtype x = 0;   // ����ֵ
	int sign = 0; 
	Stack S_all, S_subscript;  //  all����ջ��sub�Ƿ���ջ
	S_all = Stack_Create();
	S_subscript = Stack_Create();
	printf("������һ�����ʽ��\n");
	while(x != '#')
	{
		scanf("%c",&x);
		if(x > 47 && x < 58)  // �ж��Ƿ�Ϊ����
			S_all = Stack_In(S_all,x);
		else if(x == '(' | x == ')' | x == '*' |x == '/' |x == '+' |x == '-') 
		{
			SubscriptStack_IsEnter(S_all, S_subscript, x);
		}
		else
			printf("��ı��ʽ�������ٴ����룡");
	}
	// ����沨��ʽ
	for(;sign != S_subscript->top+1; sign++)
		Stack_In(S_all, S_subscript->data[sign]);
	for(; sign != S_all->top+1; sign++)
		printf("%c", S_all->data[sign]);
	return 0;
}
