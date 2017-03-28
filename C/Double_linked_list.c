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

LinkedList LinkedListCreate(elemtype x)
{
	int i = 1;   //count the number 
	int keep;    // to save the number
	Node *head,*p,*q;
	head = (Node*) malloc (sizeof(Node));
	if(head == NULL)                       
		printf("Failed to apply memory space!\n");
	head->next  = NULL; 
//	head->prior = head;
	head->prior = NULL;
	if(x > 0)          //do not raise any memory space
	{
		scanf("%d",&keep);
		head->data = keep;
		q = head;
	}
	for(;i<x;i++)
	{
		p = (Node*) malloc (sizeof(Node));
		p->prior = NULL;
		scanf("%d",&keep);
		p->data = keep;
//		head->prior = p;       
		p->next  = q;
		head->next  = p;
//		p->prior = q;
		q = p;
	}
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
		q = p->prior;
		head->prior = p;
		q = p;
		p = p->next;
		if(p->next == NULL)
		{
			p->next = head;
			break;
		}
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
//	printf("Please enter the number what you fined:\n");
//	scanf("%d",&x);
	/*
	flag = LinkedListSearch(head,x);
	if(flag == 0)
		printf("Can't found the value.\n");
	else
		printf("The value in %d\n",flag);
	*/
	LinkedListBuild(head);
	if(head->next = head)
		printf("%d",head->data);
	printf("%d",head->data);
	p = head->next;
	while(p != head)
	{
		printf("%d\n",p->data);
		p = p->next;
	}
	return 0;
}

