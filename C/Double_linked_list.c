#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int elemtype;
typedef struct Node
{
	elemtype data;
	struct Node *next;
	struct Node *prior;
}Node,*LinkedList;

//尾插法创建循环单链表 
LinkedList LinkedListCreate(elemtype x)
{
	int i;
	int save;
	Node *head,*p,*q;
	head = (Node*) malloc (sizeof(Node));
	head->data = NULL;
	q = head;
	for(i=0;i<x;i++)
	{
		p = (Node*) malloc (sizeof(Node));
		scanf("%d",&save);
		p->data = save;
		q->next = p;
		q = p;
	}
	p->next = head;
	return head;
}
LinkedList LinkedListSearch(LinkedList head,elemtype x)
{
	Node *p;
	if(head->data == x)
		return head;
	p = head->next;
	
	while(p != head)
	{
		if(p->data == x)
			return p;
		p = p->next;
	}
	return 0;
}

//把循环单链表变成循环双链表 
LinkedList LinkedListBuild(LinkedList head)
{
	Node *p,*q;
	if(head->next == head)
	{
		head->prior = head;
		return head;
	}
	p = head->next;
	q = head;
	while(p != head)
	{
		p->prior = q;
		q = p;
		p = p->next; 
		if(p == head)
			p->prior = q;
	}
	return head;
}

int main()
{
	Node *head,*p;
	int flag;
	int x;
	printf("Please enter a len number:\n");
	scanf("%d",&x);
	head = LinkedListCreate(x);
	//搜索链表中的元素 
/*
	printf("Please enter the number what you fined:\n");
	scanf("%d",&x);
	
	flag = LinkedListSearch(head,x);
	if(flag == 0)
		printf("Can't found the value.\n");
	else
		printf("The value in %d\n",flag);
	*/
	LinkedListBuild(head);
/*
	//next输出 
	p = head->next;
	while(p != head)
	{
		printf("%d\n",p->data);
		p = p->next;
	}
*/
	//prior输出 
	p = head->prior; 
	while(p != head)
	{
		printf("%d\n",p->data);
		p = p->prior;
	}
	return 0;
}

