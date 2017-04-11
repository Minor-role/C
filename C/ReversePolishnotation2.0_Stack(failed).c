// ���ӣ� 2*3+(5-3/1)*2#
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

// �жϸý�ջ�������ȼ��Ƿ����ջ������
int Stack_XIsPrior(Stack S_all, Stack S_sub, elemtype *x)
{
	if(x == '*' | x == '/')   // �жϳ˳��� 
	{
		if(S_sub->data[S_sub->top] != '*' | S_sub->data[S_sub->top] != '/')	    //   ��������ͬһ���ȼ��ģ����� 0 ,ֱ����ջ 
			return 0;
		else if(S_sub->data[S_sub->top] == '*' | S_sub->data[S_sub->top] == '/')    // ����ͬһ���ȼ��ģ����� 1 
			return 1;
	}
	else if (x == '+' | x == '-')   //  �жϼӼ��� 
	{
		while (Stack_IsEmpty(S_sub) == -1 | S_sub->data[S_sub->top] == '(')   //   ��������ͬһ���ȼ��ģ����� 0 ,ֱ����ջ 
		{
			Stack_In(S_all, S_sub->data[S_sub->top]);
			Stack_Pop; 
		} 
    }
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
		if (x > 47 && x < 58)
			Stack_In(S_all, x); 
		if (Stack_IsEmpty(S_sub) == -1 | x == '(') // �������ջ�ǿ�ջ�������������ţ���ֱ����ջ
			Stack_In(S_sub, x);
		else if(x == '*' | x == '/')
		{
			if (Stack_XIsPrior(S_all, S_sub, x) == 0)  // �ж�Ϊ 0 ��ֱ����ջ 
			{
				Stack_In(S_sub, x);
			}
			else if (Stack_XIsPrior(S_all, S_sub, x) == 1)  // �ж�Ϊ 1 ����ʾ��ͬһ���ȼ����ȵ�ջ�ٽ�ջ 
			{ 
				Stack_In(S_all,S_sub->data[S_sub->top]);  // ����ջ ��ջ�� ��ջ
				Stack_Pop(S_sub);   // ����ջ ջ����һ  
				Stack_In(S_sub, x);
			}
		}
		else if(x == '+' | x == '-') 
		{
			Stack_XIsPrior(S_all, S_sub, x);
		}
		else if(x == ')')
		{
			while(S_sub->data[S_sub->top] != '(')
			{
				Stack_In(S_all,S_sub->data[S_sub->top]);  // ����ջ ��ջ�� ��ջ
				Stack_Pop(S_sub);   // ����ջ ջ����һ 
			}
			Stack_Pop(S_sub);  // �� ������Ҳ���� 
		} 
	}
	while(Stack_IsEmpty(S_sub) != -1)
	{
		Stack_In(S_all,S_sub->data[S_sub->top]);  // ����ջ ��ջ�� ��ջ
		Stack_Pop(S_sub);   // ����ջ ջ����һ 
	}
	for(; sign <= S_all->top; sign++)
		printf("%c",S_all->data[sign]);
	printf("\n");
	return 0;
}















