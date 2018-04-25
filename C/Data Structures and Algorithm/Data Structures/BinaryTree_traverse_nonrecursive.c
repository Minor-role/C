/*二叉树的非递归先序遍历算法，以链表的存储方式存储数据
create by Ian in 2017-6-3 20:20:48
1. 先使用递归算法建立二叉树
2. 建立一个栈，用来保存结点
遍历算法：
1. 每访问一个结点，就把此结点放进栈中
2. 访问左子树，若不为空，则入栈，继续访问左子树，若左子树为空，则弹栈访问弹出结点的右子树
*/

#include <stdio.h>
#include <stdlib.h>
#define N 100

char node[N];
typedef char elemtype; // 方便之后改变类型


// 定义链表结点
typedef struct biTreeNode
{
	elemtype data; // 存放数据
	struct biTreeNode *leftChild;// 左孩子，结构体指针
	struct biTreeNode *rightChild;// 右孩子，结构体指针
}biTreeNode;

// 创建二叉树
biTreeNode * createBiTree(biTreeNode *T)
{
	char ch;
	static int i = 0;
	ch = node[i];
	i++;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = (struct biTreeNode *)malloc(sizeof(biTreeNode));
		if (!T){
			exit(0);
		}
		T->data = ch;
		T->leftChild = createBiTree(T->leftChild);
		T->rightChild = createBiTree(T->rightChild);
	}
	return T;
}

// 遍历打印树
void nPreOrder(biTreeNode *bt)
{
	int top = -1;
	biTreeNode * s[N];
	while (bt != NULL || top != -1)
	{
		while (bt != NULL)
		{
			printf("%c ", bt->data);
			s[++top] = bt;
			bt = bt->leftChild;
		}
		if (top != -1)
		{
			bt = s[top--];
			bt = bt->rightChild;
		}
	} 
}


int main()
{
	biTreeNode *bt;
	bt = (struct biTreeNode *)malloc(sizeof(struct biTreeNode));
	gets(node);
	bt = createBiTree(bt);
	nPreOrder(bt);
	system("pause");
	return 0;
}