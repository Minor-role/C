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
	head->next  = head; 
	head->prior = head;
	if(x > 0)          //do not raise any memory space
	{
		scanf("%d",&keep);
		head->data = keep;
		q = head;
	}
	for(;i<x;i++)
	{
		p = (Node*) malloc (sizeof(Node));
		scanf("%d",&keep);
		p->data = keep;
		head->prior = p;
		p->next  = head;
		q->next  = p;
		p->prior = q;
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

int main()
{
	Node *head;
	int flag;
	int x;
	printf("Please enter a len number:\n");
	scanf("%d",&x);
	head = LinkedListCreate(x);
	printf("Please enter the number what you fined:\n");
	scanf("%d",&x);
	flag = LinkedListSearch(head,x);
	if(flag == 0)
		printf("Can't found the value.\n");
	else
		printf("The value in %d\n",flag);
	return 0;
}

