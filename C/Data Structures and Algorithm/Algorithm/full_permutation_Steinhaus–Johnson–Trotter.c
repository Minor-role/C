/*  实现数字的全排列：邻位对换算法
create by Ian begin in 2017-9-27 18:02:02
				end in 2017-9-29 14:52:36
数据结构：双链表
步骤：
	1.建立双链表
	2.找到最大可移动元素k
	3.将元素k与它所指向的相邻元素交换
	4.改变所有大于k的元素的方向
	5.重复步骤2
*/


#include <stdio.h>
#include <stdlib.h>
#define Max 100

typedef struct Edge
{
	/* 全排列每个数字的结点 */
	int number; // 数字
	int direction; // 方向，-1为左，1为右
	int active; // 是否为可活动数 ，0为不活动，1为活动
	struct Edge *frontEdge; // 指针域，指向上一个结点
	struct Edge *nextEdge; // 指针域，指向下一个结点
}Edge;


Edge* create_edge(int len)
{
	/* 创建并存储全排列的数字 */

	int i = 0;
	int list[Max]; // 存放全排列的数字
	Edge *head, *s; // 存放头结点的指针
	Edge *temphead; // 为了实现尾插法，设置的一个临时头结点
	printf("Please enter the numbers:");
	for (; i < len; i++)
		scanf("%d", &list[i]);

	head = (Edge *)malloc(sizeof(Edge));
	// head结点为空节点
	head->number = 65535; // 设置一个最大值
	head->direction = 1; // 设置方向，起到边界的作用
	head->active = 2; // head的active比其他结点都高，起到边界的作用
	head->frontEdge = NULL;
	temphead = head; // 把头结点的地址给临时头
	for (i = 0; i < len; i++)
	{
		s = (Edge *)malloc(sizeof(Edge));
		s->number = list[i];
		s->direction = -1; // 设置方向，-1为左，1为右
		if (i == 0)s->active = 0;
		else if (list[i] > list[i - 1])// 设置是否为可活动数，如果当前数字比前一个数字大，则设置为可活动数
			s->active = 1; // 0为不活动，1为活动
		else
			s->active = 0;
		s->frontEdge = temphead; // 后一个结点指向前一个结点
		temphead->nextEdge = s; // 尾插法
		temphead = s; // 把自己变成头结点
	}
	temphead->nextEdge = NULL;
	return head;
}

Edge* max_active_number(Edge *head)
{
	/* 找到并返回最大可活动元素k */
	int maxnumber = 0;
	Edge *tempNode = NULL; // 临时存放最大值的结点
	Edge *p1, temp;
	p1 = head->nextEdge;
	while (p1) // 找出可移动的最大值
	{
		if (p1->direction == -1)
		{
			if (p1->number > maxnumber && p1->active == 1)
				tempNode = p1;
		}
		else
		{
			if (p1->number > maxnumber && p1->active == 1)
				tempNode = p1;
		}
		if (tempNode)
			maxnumber = tempNode->number;
		p1 = p1->nextEdge;
	}

	return tempNode;
}

void printf_number(Edge* head)
{
	/* 打印所有元素 */

	Edge* p1;
	p1 = head->nextEdge;
	while (p1)
	{
		printf("%d  ", p1->number);
		p1 = p1->nextEdge;
	}
	printf("\n");
}

void update_direction(Edge* head, Edge* maxNode)
{
	/* 改变所有大于k的元素方向 */
	Edge* p1;
	p1 = head->nextEdge;
	while (p1)
	{
		if (p1->number > maxNode->number)
			p1->direction = -p1->direction;
		p1 = p1->nextEdge;
	}
}

void updte_active(Edge* head)
{
	/* 更新所有元素的active，确定其是否是可活动元素 */
	Edge* p1;
	p1 = head->nextEdge;
	while (p1)
	{
		if (p1->direction == -1 && p1->frontEdge)
		{
			if (p1->number > p1->frontEdge->number)
				p1->active = 1;
			else
				p1->active = 0;
		}
		else if (p1->direction == 1 && p1->nextEdge)
		{
			if (p1->number > p1->nextEdge->number)
				p1->active = 1;
			else
				p1->active = 0;
		}
		else p1->active = 0;
		p1 = p1->nextEdge;
	}
}

void trans_node(Edge* first, Edge* second)
{
	/* 交换两个结点的值 */
	if (first->frontEdge)
		first->frontEdge->nextEdge = second;
	if (second->nextEdge)
		second->nextEdge->frontEdge = first;
	first->nextEdge = second->nextEdge;
	second->frontEdge = first->frontEdge;
	first->frontEdge = second;
	second->nextEdge = first;
}

int trans_number(Edge *head)
{
	/* 邻位对换算法 
	1.找到最大可移动元素k
	2.交换结点
	3.输出，同时更新方向、可活动状态
	4.重复步骤1
	*/

	int count = 1; // 计数器
	Edge* maxNode = NULL;
	Edge *frontNode, *nextNode;
	maxNode = max_active_number(head);
	printf_number(head);
	while (maxNode)
	{
		if (maxNode->direction == -1) // 如果方向向左
			trans_node(maxNode->frontEdge, maxNode);

		else
			trans_node(maxNode, maxNode->nextEdge);

		printf_number(head);
		update_direction(head, maxNode);
		updte_active(head);
		maxNode = max_active_number(head);
		count++;
	}
	return count;
}

void test(Edge *head)
{
	/* 测试程序，测试双链表是否正常工作 */
	Edge *temp;
	temp = head->nextEdge;
	printf("test file!!!!!!!!\n");
	while (temp)
	{
		printf("%d", temp->number);
		if (temp->nextEdge == NULL)break;
		temp = temp->nextEdge;
	}
	printf("\n");
	while (temp)
	{
		printf("%d", temp->number);
		temp = temp->frontEdge;
	}
}

int main(int argc, char const *argv[])
{
	/* 主函数 */
	Edge *head;
	int len = 0, count = 0;
	printf("------------permutation:recursive----------\n");
	printf("Please print the length of number(<=100):");
	scanf("%d", &len);
	while (len>100)
	{
		printf("Please enter again:");
		scanf("%d", &len);
	}
	head = create_edge(len);
	count = trans_number(head);
	//test(head);
	printf("total:%d\n", count);
	system("pause");
	getchar();
	return 0;
}