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
		p =  (Node*) malloc (sizeof(Node));  //Application memory space
		p->data = x;						// put x into node's data
		p->next = head->next;				//head insert
		head->next = p;                     //link head and next
		scanf("%d",&x);
	}
	return head;
}

//search a node
LinkedList LinkedListSearch(LinkedList head,elemtype x)
{
	Node *p;
	p = head->next;
	while(p->data != x)
	{
		if(p->next == NULL)
			return 0;
		p = p->next;
	}
	return p;
} 
//delete a node
LinkedList LinkedListDelete(LinkedList head,elemtype x)
{

}

int main()
{
	
}




