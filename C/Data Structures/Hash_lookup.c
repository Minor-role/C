/*
	2017年6月9日13:58:07
	使用哈希函数：H（K）=3K MOD 11 并采用链地址法处理冲突。试对关键字序列（22，41，53，46，30，13，01，67）构造哈希表，设计构造哈希表的完整算法。
	链地址法（即拉链法）的基本思想是：将所有散列地址相同的记录，即所有关键 码为同义词的记录存储在一个单链表中，也称为同义词子表，
	在散列表中存储的是所 有同义词子表的头指针。设 n 个记录存储在长度为 m 的开散列表中，则同义词子表 的平均长度为 n/m。
*/
#include <stdio.h>
#include <windows.h>
#define MaxSize 3

struct linkNode 
{
	int data;//数据域 
	struct linkNode *next;//指针域
};

struct linkNode *head[MaxSize];//全局变量，头指针数组

//构造散列表，n 为数据个数，散列函数：H(K)=3*k MOD MaxSize 
void createHashTable(int a[],int n) 
{
	struct linkNode *p; 
	int i,j; 
	//初始化头指针数组
	for(i=0;i<MaxSize;i++)
		head[i] = NULL;
	for(i=0;i<n;i++) 	// 控制j,假如 j被占用了，就在数组里面找下一个 
	{
		j=3*a[i] % MaxSize; 
		/*
		倒数3个语句博大精深！
		头插法 ，它首先创建一个P指针，然后把数据和head数组的某个空间地址放到P里面，P的地址也放到head数组的j空间里面，
		然后再新建一个P重复操作，其中head数组的某个空间地址受到上面的j的影响，也就是受哈希函数的影响。
		如果两个数的j相等怎么办？答案是，首先head将旧的空间的头指针放到新空间的next里面，再将新空间的头指针放到head的j空间里面，如此往复
		由于头一直在变，因此也叫头插法
		*/
		p=(struct linkNode *)malloc(sizeof(struct linkNode)); 
		p->data=a[i]; 
		p->next=head[j]; 
		head[j]=p;
	}
}

//开散列表查找，k 为要查找的数，返回结点指针 
struct linkNode *hashSearch(int k) 
{
	struct linkNode *p; 
	int i;
	i=3*k % MaxSize; 
	p = head[i]; 
	while(p && p->data!=k) 
		p=p->next;
	return p; 
}

int main()
{
	int a[MaxSize];
	int n = 0,i = 0;
	struct linkNode *p;
	printf("请输入个数：");
	scanf("%d",&n);
	while(i<n)
	{
		printf("请输入字符：");
		scanf("%d",&a[i]);
		getchar();
		i++; 
	}
	createHashTable(a,n);
	printf("请输入你要查找的数：");
	scanf("%d",&i);
	p = hashSearch(i);
	if(p != NULL && p->data == i)
		printf("你查找的数已经找到！");
	else 
		printf("未能找到你查找的数~");
	getchar();
	return 0;
}