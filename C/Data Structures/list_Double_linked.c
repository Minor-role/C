/*
	建立一个循环单链表，其节点有 prior，data 和 next 三个域，其中 data 为数据域，
	存放元素的有效信息，next 域为指针域，指向后继节点，prior 为指针域，它的值为NULL。
	编写一个算法将此表改为循环双链表
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
typedef int elemtype;
typedef struct Node
{
	elemtype data;
	struct Node *next;
	struct Node *prior;
}Node,*LinkedList;

//
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

//
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
	LinkedListBuild(head);
	p = head->prior; 
	while(p != head)
	{
		printf("%d\n",p->data);
		p = p->prior;
	}
	system("pause");
	return 0;
}

