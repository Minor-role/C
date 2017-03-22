#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define int elemtype
typedef struct Node
{
	elemtype data;
	struct Node *next;
	struct Node *prior;
}Node,*LinkedList;

LinkedList LinkedListCreate(elemtype x)
{
	int i = 0;   //count the number 
	int keep;    // to save the number
	Node head,p,q;
	head = (Node*) malloc (sizeof(Node));
	if(head == NULL)                       
		printf("Failed to apply memory space!\n");
	head->next  = NULL; 
	head->prior = NULL;
	if(x > 0)          //do not raise any memory space
	{
		scanf("%d",&keep);
		head->data = keep;
	}
	for(;i<x;i++)
	{
		p = (Node*) malloc (sizeof(Node));
		scanf("%d",&keep);
		p->data = keep;
		head->next  = p;
		head->prior = p;
		p->next  = head;
		p->prior = head;
		
	}
}

int main()
{
	
	return 0;
}