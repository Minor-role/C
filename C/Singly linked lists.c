#include<stdio.h>
typedef int elemtype;          //Convenient after modifying the type of data
typedef struct Node
{
	elemtype data;         	//Defines the data fields in a single linked list	
	struct Node *next;		// Pointer field
}Node,*LinkedList;

// Single linked list initialization
LinkedList LinkedListInit()
{
	Node *head;
	head = (Node*) malloc (sizeof(Node));
	if(head == NULL)
		print("Failed to apply memory space!\n");
	head->next = NULL; 
}

//Head insertion to build a single linked list
LinkedList LinkedListCreate()
{
	Node *head,*p;
	head = (Node*) malloc (sizeof(Node));
	if(head == NULL)
		print("Failed to apply memory space!\n");
	head->next = NULL; 
	
	elemtype x;
	scanf("%d",&x);
	while( x != 0)
	{
		p =  (Node*) malloc (sizeof(Node));
		p->data = x;
		p->next = head->next;
		head->next = p; 
		scanf("%d",&x);
	}
	return head;
}

int main()
{
	
	printf("good job");
}


void  reverse( LinkList *head )
{	LinkList  *p, *q;
	p = head->next;	     /*p指向第一个结点*/
	q = p->next; 
	while (p->data > q->data)
	{	q = p;   	    /*取下原链表的当前结点*/
		p = p->next;	    /*p指针下移*/
		q->next = head->next;		
 		head->next = q;  /*修改头结点指针*/
	}
}





